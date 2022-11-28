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
c