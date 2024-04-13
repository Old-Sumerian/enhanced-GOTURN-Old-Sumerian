#ifndef TRACKER_H
#define TRACKER_H

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "helper/bounding_box.h"
#include "network/regressor.h"

class Tracker
{
public:
  Tracker(const bool show_tracking);

  // Estimate the location of the target object in the current image.
  virtual void Track(const cv::Mat& image_curr, RegressorBase* regressor,
             BoundingBox* bbox_estimate_uncentered);



  // Initialize the tracker with the ground-truth bounding box of the first frame.
  void Init(const cv::Mat& image_curr, const BoundingBox& bbox_gt,
            RegressorBase* regressor);

  // Initialize the tracker with the ground-truth bounding box of 