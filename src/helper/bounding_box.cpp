#include "bounding_box.h"

#include <cstdio>
#include "helper/image_proc.h"


// Uncomment line below if you want to use rectangles

#include "helper.h"

// How much context to pad the image and target with (relative to the
// bounding box size).
const double kContextFactor = 2;

// Factor by which to scale the bounding box coordinates, based on the
// neural network default output range.
const double kScaleFactor = 10;

// If true, the neural network will estimate the bounding box corners: (x1, y1, x2, y2)
// If false, the neural network will estimate the bounding box center location and size: (center_x, center_y, width, height)
const bool use_coordinates_output = true;

using namespace std;
BoundingBox::BoundingBox() :
  scale_factor_(kScaleFactor)
{
}


BoundingBox::BoundingBox(const std::vector<float>& bounding_box)
  : scale_factor_(kScaleFactor)
{
  if (bounding_box.size() != 4) {
    printf("Error - bounding box vector