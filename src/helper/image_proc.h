#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

#include "bounding_box.h"

// Functions to process images for tracking.

// Crop the image at the bounding box location, plus some additional padding.
// To account for edge effects, we use a black background fo