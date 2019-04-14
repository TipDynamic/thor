# Install script for directory: /media/jintian/netac/weapons/cc/thor

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/media/jintian/netac/weapons/cc/thor/buil/libthor.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libthor.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/thor" TYPE FILE FILES
    "/media/jintian/netac/weapons/cc/thor/include/app_license.h"
    "/media/jintian/netac/weapons/cc/thor/include/colors.h"
    "/media/jintian/netac/weapons/cc/thor/include/common_structure.h"
    "/media/jintian/netac/weapons/cc/thor/include/core.h"
    "/media/jintian/netac/weapons/cc/thor/include/dl.h"
    "/media/jintian/netac/weapons/cc/thor/include/json.h"
    "/media/jintian/netac/weapons/cc/thor/include/logging.h"
    "/media/jintian/netac/weapons/cc/thor/include/math.h"
    "/media/jintian/netac/weapons/cc/thor/include/os.h"
    "/media/jintian/netac/weapons/cc/thor/include/random.h"
    "/media/jintian/netac/weapons/cc/thor/include/slam.h"
    "/media/jintian/netac/weapons/cc/thor/include/str_util.h"
    "/media/jintian/netac/weapons/cc/thor/include/vis.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/media/jintian/netac/weapons/cc/thor/buil/libthor_static.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/thor" TYPE FILE FILES
    "/media/jintian/netac/weapons/cc/thor/include/app_license.h"
    "/media/jintian/netac/weapons/cc/thor/include/colors.h"
    "/media/jintian/netac/weapons/cc/thor/include/common_structure.h"
    "/media/jintian/netac/weapons/cc/thor/include/core.h"
    "/media/jintian/netac/weapons/cc/thor/include/dl.h"
    "/media/jintian/netac/weapons/cc/thor/include/json.h"
    "/media/jintian/netac/weapons/cc/thor/include/logging.h"
    "/media/jintian/netac/weapons/cc/thor/include/math.h"
    "/media/jintian/netac/weapons/cc/thor/include/os.h"
    "/media/jintian/netac/weapons/cc/thor/include/random.h"
    "/media/jintian/netac/weapons/cc/thor/include/slam.h"
    "/media/jintian/netac/weapons/cc/thor/include/str_util.h"
    "/media/jintian/netac/weapons/cc/thor/include/vis.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" TYPE FILE FILES "/media/jintian/netac/weapons/cc/thor/include/thor.pc")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/media/jintian/netac/weapons/cc/thor/buil/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
