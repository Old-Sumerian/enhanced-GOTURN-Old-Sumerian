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

* Install O