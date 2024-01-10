#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

#include "bounding_box.h"

// Functions to process images for tracking.

// Crop the image at the bounding box location, plus some additional padding.
// To account for edge effects, we use a black background for space beyond the border
// of the image.
void CropPadImage(const BoundingBox& bbox_tight, const cv::Mat& image, cv::Mat* pad_image);
void CropPadImage(const BoundingBo