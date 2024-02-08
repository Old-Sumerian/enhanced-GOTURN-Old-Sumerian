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

  Blob<float>* input_layer = net_