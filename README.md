# thor [![Travis Status](https://travis-ci.org/davisking/dlib.svg?branch=master)](https://travis-ci.org/davisking/dlib)

**thor** is a C++ helper library which contains many *system*, *string*, *deep learning visualize*, etc. Many helper modules allows you integrate into your project.



## Install

*thor* is now expanded into a deep learning util library, so there are som prerequirements is needed:

```
sudo apt install libopencv-dev
sudo apt install libfreetype6-dev

PCL (optinal)
Eigen (optional)
```
In case you are not formiliar with any above libs, you can still build thor, but you need them when calling some apis.


```
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
