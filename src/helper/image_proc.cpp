
#include "image_proc.h"

void ComputeCropPadImageLocation(const BoundingBox& bbox_tight, const cv::Mat& image, BoundingBox* pad_image_location) {
  // Get the bounding box center.
  const double bbox_center_x = bbox_tight.get_center_x();
  const double bbox_center_y = bbox_tight.get_center_y();

  // Get the image size.
  const double image_width = image.cols;
  const double image_height = image.rows;

  // Get size of output image, which is given by the bounding box + some padding.
  const double output_width = bbox_tight.compute_output_width();
  const double output_height = bbox_tight.compute_output_height();

  // The output image is centered on the bounding box center but has a size given by (output_width, output_height)
  // to account for additional padding.
  // The output image location is also limited by the edge of the image.
  // Get the output image corner.