
#include "tracker.h"

#include <opencv2/videostab/inpainting.hpp>

#include "helper/helper.h"
#include "helper/bounding_box.h"
#include "network/regressor.h"
#include "helper/high_res_timer.h"
#include "helper/image_proc.h"

Tracker::Tracker(const bool show_tracking) :
  show_tracking_(show_tracking)
{
}


void Tracker::Init(const cv::Mat& image, const BoundingBox& bbox_gt,
                   RegressorBase* regressor) {
  image_prev_ = image;
  bbox_prev_tight_ = bbox_gt;

  // Predict in the current frame that the location will be approximately the same
  // as in the previous frame.
  // TODO - use a motion model?
  bbox_curr_prior_tight_ = bbox_gt;

  // Initialize the neural network.