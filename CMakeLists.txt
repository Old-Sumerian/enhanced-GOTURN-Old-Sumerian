cmake_minimum_required(VERSION 3.6)
project(mygoturn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Boost COMPONENTS system filesystem regex REQUIRED)

# avoid "can not find -lopencv_dep_cudart"
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

find_package( OpenCV REQUIRED )
message("Open CV version is ${OpenCV_VERSION}")

set(Caffe_DIR ~/tracking/GOTURN/caffe)
find_package(Caffe REQUIRED)
include_directories(${Caffe_INCLUDE_DIRS})
add_definitions(${Caffe_DEFINITIONS