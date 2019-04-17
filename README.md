# thor [![Travis Status](https://travis-ci.org/davisking/dlib.svg?branch=master)](https://travis-ci.org/davisking/dlib)

**thor** is a C++ helper library which contains many *system*, *string*, *deep learning visualize*, etc. Many helper modules allows you integrate into your project.



## Installation

*thor* is now expanded into a deep learning util library, so there are som prerequirements is needed:

```
# for computer vision
opencv
# for show Chinese fonts
libfreetype6-dev

PCL (optinal)
Eigen (optional)
```
In case you are not formiliar with any above libs, you can still buid thor, but you need them when calling some apis.


```
git clone https://github.com/jinfagang/thor
cd thor
mkdir build
cd build
cmake ..
make all -j8
sudo make install
```

so you can have **Thor** library in your system. Or, simply:

```shell
./build_all.sh
```



*updates*:

- **2050.01.01**: to be continue..
- **2019.04.17**: We add a simple Chinese font support now.
- **2019.01.15**: Now, slam module has been integrated into thor, you can access slam by those functions:

  ```
  // to get good matches of 2 images
  slam::getGoodMatchesColor(img1, img2, good_matches);
  ```




## Usage

**Thor** has a very clean and easy-to-use API, it consist of many parts. All parts can be listed as follow:

- *vis*: For computer vision, draw boxes or segmentation results on image, should worked with opencv;
- *files*;
- *random*;
- *color*;
- *logging*;
- *slam*;



**dependencies** of thor:

thor only relies on some normal library such as opencv (for compute vision purpose), you can install opencv by build from source, but install another module:

```
sudo add-apt-repository --yes ppa:xqms/opencv-nonfree
sudo apt-get update
sudo apt-get install libopencv-nonfree-dev
```

if you are not using *slam* module, then just ignore this.

Find **thor**:

```cmake
find_library(thor_LIBRARY
        NAME thor
        HINTS "${CMAKE_INSTALL_PREFIX}/lib"
        )
if (NOT thor_FOUND)
    message(ERROR "Thor lib not found, you can clone from https://github.com/jinfagang/Thor to build and install.")
endif ()

# then link it
target_link_libraries(main ${thor_LIBRARY})

# if you install thor to system path, simply using is also OK
target_link_libraries(main -lthor)
```



to build with Makefile, using:

```shell
g++ -o a a.cpp `pkg-config thor --cflags --libs`
```

add above output to your makefile and you can build with thor



In case you want integrate but with trouble, find me via wechat: `jintianiloveu`

## Features
We list module **thor** currently finished here:

- [x] os
- [x] color
- [x] random
- [x] log
- [x] string utils




## Copyright

**thor** was build by *Lucas Jin* with ❤️. Under MIT license.
