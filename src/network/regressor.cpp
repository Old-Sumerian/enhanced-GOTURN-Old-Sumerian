#include "regressor.h"

#include "helper/high_res_timer.h"

// Credits:
// This file was mostly taken from:
// https://github.com/BVLC/caffe/tree/master/examples/cpp_classification

using caffe::Blob;
using caffe::Net;
using std::string;

// We need 2 inputs: one for the current frame and one for the previous frame.
const in