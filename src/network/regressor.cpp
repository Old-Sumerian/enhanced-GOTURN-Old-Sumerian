#include "regressor.h"

#include "helper/high_res_timer.h"

// Credits:
// This file was mostly taken from:
// https://github.com/BVLC/caffe/tree/master/examples/cpp_classification

using caffe::Blob;
using caffe::Net;
using std::string;

// We need 2 inputs: one for the current frame and one for the previous frame.
const int kNumInputs = 2;

Regressor::Regressor(const string& deploy_proto,
                     const string& caffe_model,
                     const int gpu_id,
                     const int num_inputs,
                     const bool do_train)
  : num_inputs_(num_inputs),
    caffe_model_(caffe_model),
    modified_params_(false)

{
  SetupNetwork(deploy_proto, caffe_model, gpu_id, do_train);
}

Regressor::Regressor(const string& deploy_proto,
                     const string& caffe_model,
                     const int gpu_id,
                     const bool do_train)
  : num_inputs_(kNumInputs),
    caffe_model_(caffe_model),
    modified_params_(false)
{
  SetupNetwork(deploy_proto, caffe_model, gpu_id, do_train);
}

//#define  CPU_ONLY
void Regressor::SetupNetwork(const string& deploy_proto,
                             const string& caffe_model,
                             const int gpu_id,
                             const bool do_train) {
#ifdef CPU_ONLY
  printf("Setting up Caffe in CPU mode\n");
  caffe::Caffe::set_mode(caffe::Caffe::CPU);
#else
  printf("Setting up Caffe in GPU mode with ID: %d\n", gpu_id);
  caffe::Caffe::SetDevice(gpu_id);
  caffe::Caffe::set_mode(caffe::Caffe::GPU);
#endif

  if (do_train) {
    printf("Setting phase to train\n");
    net_.reset(new Net<float>(deploy_proto, caffe::TRAIN));
  } else {
    printf("Setting phase to test\n");
    net_.reset(new Net<float>(deploy_proto, caffe::TEST));
  }

  if (caffe_model != "NONE") {
    net_->CopyTrainedLayersFrom(caffe_model_);
  } else {
    printf("Not initializing network from pre-trained model\n");
  }

  //CHECK_EQ(net_->num_inputs(), num_inputs_) << "Network should have exactly " << num_inputs_ << " inputs.";
  CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

  Blob<float>* input_layer = net_->input_blobs()[0];

  printf("Network image size: %d, %d\n", input_layer->width(), input_layer->height());

  num_channels_ = input_layer->channels();
  CHECK(num_channels_ == 3 || num_channels_ == 1)
    << "Input layer should have 1 or 3 channels.";
  input_geometry_ = cv::Size(input_layer->width(), input_layer->height());

  // Load the binaryproto mean file.
  SetMean();
}

void Regressor::SetMean() {
  // Set the mean image.
  mean_ = cv::Mat(input_geometry_, CV_32FC3, cv::Scalar(104, 117, 123));
}

void Regressor::Init() {
  if (modified_params_ ) {
    printf("Reloading new params\n");
    net_->CopyTrainedLayersFrom(caffe_model_);
    modified_params_ = false;
  }
}

void Regressor::Regress(const cv::Mat& image_curr,
                        const cv::Mat& image, const cv::Mat& target,
                        BoundingBox* bbox) {
  assert(net_->phase() == caffe::TEST);

  // Estimate the bounding box location of the target object in the current image.
  std::vector<float> estimation;
  Estimate(image, target, &estimation);

  // Wrap the estimation in a bounding box object.
  *bbox = BoundingBox(estimation);
}

void Regressor::Estimate(const cv::Mat& image, const cv::Mat& target, std::vector<float>* output) {
  assert(net_->phase() == caffe::TEST);

  // Reshape the input blobs to be the appropriate size.
  Blob<float>* input_target = net_->input_blobs()[0];
  input_target->Reshape(1, num_channels_,
                       input_geometry_.height, input_geometry_.width);

  Blob<float>* input_image = net_->input_blobs()[1];
  input_image->Reshape(1, num_channels_,
                       input_geometry_.height, input_geometry_.width);

  Blob<float>* input_bbox = net_->input_blobs()[2];
  input_bbox->Reshape(1, 4, 1, 1);

  // Forward dimension change to all layers.
  net_->Reshape();

  // Process the inputs so we can set them.
  std::vector<cv::Mat> target_channels;
  std::vector<cv::Mat> image_channels;
  WrapInputLayer(&target_channels, &image_channels);

  // Set the inputs to the network.
  Preprocess(image, &image_channels);
  Preprocess(target, &target_channels);

  // Perform a forward-pass in the network.
  net_->ForwardPrefilled();

  // Get the network output.
  GetOutput(output);
}

void Regressor::ReshapeImageInputs(const size_t num_images) {
  // Reshape the input blobs to match the given size and geometry.
  Blob<float>* input_target = net_->input_blobs()[0];
  input_target->Reshape(num_images, num_channels_,
                       input_geometry_.height, input_geometry_.width);

  Blob<float>* input_image = net_->input_blobs()[1];
  input_image->Reshape(num_images, num_channels_,
                       input_geometry_.height, input_geometry_.width);
}

void Regressor::GetFeatures(const string& feature_name, std::vector<float>* output) const {
  //printf("Getting %s features\n", feature_name.c_str());

  // Get a pointer to the requested layer.
  const