//
// Created by ise on 16-10-23.
//
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <helper/helper.h>
#include <opencv2/opencv.hpp>


#include "loader_base.h"

namespace bfs = boost::filesystem;

bool getBox = false;
bool drawing_box = false;

Loader::Loader(const string& _videos_folder)
        :videos_folder_(_videos_folder) {
    loadervideos(_videos_folder);
}

void Loader::loadervideos(const string _videos_folder){
    if(!