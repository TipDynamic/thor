# thor [![Travis Status](https://travis-ci.org/davisking/dlib.svg?branch=master)](https://travis-ci.org/davisking/dlib)

**thor** is a C++ helper library which provide huge utilities, algorithms, and visualization functions for deep learning. We recommend install thor from github source since we update thor new APIs a lot. But *thor* will always compatible with older versions, it safe and reliable integrate into your projects and providing useful utilities.


## Install

*thor* is now expanded into a deep learning util library, so there are som prerequirements is needed:

```shell
sudo apt install libopencv-dev
sudo apt install libfreetype6-dev
sudo apt install libcurl4-openssl-dev

# for PCL, if you already installed, skip this
sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get update
sudo apt-get install libpcl-all

# for protobuf 3.6.x (DONOT install 2.7.x, it's deprecated)
sudo apt-get install libprotobuf-dev
sudo apt install protobuf-compiler
# make sure `protoc --version` is 3.6.x, 3.0+ also OK.

# for Eigen
sudo apt install libeigen3-dev
# if you got Eigen/Eigen include issue, link eigen3/Eigen to Eigen
```

Since **thor** is target at *deep learning* purpose, those dependencies is must and enssential. If you are an newbie and got some trouble in install thor, feel free to open an issue about your problem. We will solve that as quickly as possiable.
After dependencies installation, you can built thor now.

```shell
git clone https://github.com/jinfagang/thor
cd thor
mkdir build
cd build
cmake ..
make all -j8
sudo make install
```

We will automatically locate your system installed Eigen, once found, you can using all interfaces with Eigen. If you not install Eigen, just will ignore it.



*updates*:

- **2050.01.01**: to be continue..
- **2019.05.19**:  There would be a huge updates on **thor** in recent days. We are trying to integrate all math library in Apollo into thor. So that it can do lots of math calculations.  If you got any undefined inference error just open an issue about that. Currently if you want using thor, you gonna need **link protobuf** in your c++ project.   
- **2019.05.01**: Add some geometry utils such as conversion between quaternion and euler angels for robots and autocar:
    ```c++
    Eigen::Matrix3d Quaternion2RotationMatrix(const double x, const double y, const double z, const double w);
    Eigen::Quaterniond EulerAngle2Quaternion(const double yaw, const double pitch, const double roll);                             
    ```
    **note**: this is only available when you have Eigen installed.
- **2019.01.15**: Now, slam module has been integrated into thor, you can access slam by those functions;



## Usage

**thor** has a very clean and easy-to-use API, it consist of many parts. All parts can be listed as follow:

- *vis*: For computer vision, draw boxes or segmentation results on image, should worked with opencv;
- *files*;
- *random*;
- *color*;
- *logging*;
- *slam*;

You only need add this line to CMakeLists.txt when you have thor installed in your system path.

```cmake
target_link_libraries(main -lthor)
```

to build with Makefile, using:

```shell
g++ -o a a.cpp `pkg-config thor --cflags --libs`
```
In case you want integrate but with trouble, find me via wechat: `jintianiloveu`


## Features
We list module **thor** currently finished here:

- [x] os
- [x] color
- [x] random
- [x] log
- [x] string utils
- [x] geometry (quaternion and euler angle conversion)


## Copyright

**thor** was build by *Lucas Jin* with ❤️. Under MIT license.
