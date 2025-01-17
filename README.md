# Enhanced GOTURN

**This project offers an enhanced and concise version of GOTURN: Generic Object Tracking Using Regression Networks.**

**Originally based on the GOTURN project (http://davheld.github.io/GOTURN/GOTURN.html), this implementation simplifies the setup and testing process by eliminating some redundant files. The intent is to make it easier to test the algorithm with your own videos.**

The original work, GOTURN, was presented in the following paper:

**[Learning to Track at 100 FPS with Deep Regression Networks](http://davheld.github.io/GOTURN/GOTURN.html)**,
<br>
[David Held](http://davheld.github.io/),
[Sebastian Thrun](http://robots.stanford.edu/),
[Silvio Savarese](http://cvgl.stanford.edu/silvio/),
<br>
European Conference on Computer Vision (ECCV), 2016 (In press)


## Installation

### Install dependencies:

* Install CMake:
```
sudo apt-get install cmake
```

* Install Caffe and compile using the CMake build instructions:
http://caffe.berkeleyvision.org/installation.html
It is necessary to compile caffe using cmake, as without it, this project cannot locate the required caffe.

* Install OpenCV
```
sudo apt-get install libopencv-dev
```
If you have already installed opencv, avoid executing this step.


### Compile

From the main directory, follow these steps:

Open CMakeLists.txt, and change `set(Caffe_DIR your_caffe_folder)`, for example, mine is `set(Caffe_DIR ~/tracking/GOTURN/caffe)`

then run the following commands:
```
mkdir build
cd build
cmake ..
make
```

## Pretrained model

To download a pretrained tracker model (434 MB), run the following script from the main directory:

```
bash scripts/download_trained_model.sh
```

## Test your own video

To test on your own video, run the following script:

```
bash scripts/runTracker.sh
```