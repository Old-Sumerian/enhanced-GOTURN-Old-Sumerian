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
  Tracker(const