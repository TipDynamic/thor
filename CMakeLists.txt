cmake_minimum_required(VERSION 3.5)
project(thor VERSION 1.3.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)


# -------- Add definitions
option(USE_OPENCV "Build with OpenCV enable for vis module" ON)
option(USE_EIGEN "Build with Eigen enable for geometry module" ON)
option(DEBUG "Enable debug mode, for develop" ON)


file(GLOB_RECURSE thor_SRCS "src/*.cpp" "src/*.cc")
file(GLOB_RECURSE thor_HEADERS "include/*.h" "include/*.hpp")

include(GNUInstallDirs)
# !------------ include freetype2
include_directories(/usr/include/freetype2/)
    

if (USE_OPENCV)
    find_package(OpenCV REQUIRED)
endif ()

find_package(CURL REQUIRED)
if(NOT CURL_FOUND)
    message(FATAL 'curl is needed to build thor static library')
endif()

# add shared and static library
# PUBLIC_HEADER sometimes not all installed, reference to
# https://stackoverflow.com/questions/10487256/cmake-how-to-properly-copy-static-librarys-header-file-into-usr-include
if (USE_OPENCV)
    add_library(thor SHARED ${thor_SRCS})
    target_link_libraries(thor ${OpenCV_LIBS} ${CURL_LIBRARIES} glog freetype)

    add_library(thor_static STATIC ${thor_SRCS})
    target_link_libraries(thor_static ${OpenCV_LIBS} ${CURL_LIBRARIES} glog freetype)
else ()
    add_library(thor SHARED ${thor_SRCS} ${CURL_LIBS} glog freetype include/algorithm.h src/algorithm.cpp src/cv_ex.cpp include/cv_ex.h include/geometry.h src/geometry.cpp)
    add_library(thor_static STATIC ${thor_SRCS} ${CURL_LIBS} glog freetype)
endif ()


set_target_properties(
        thor
        PROPERTIES
        PUBLIC_HEADER "${thor_HEADERS}")
set_target_properties(
        thor_static
        PROPERTIES
        PUBLIC_HEADER "${thor_HEADERS}")


configure_file(thor.pc thor.pc @ONLY)
target_include_directories(thor PRIVATE .)
# static should also add include directories, otherwise will miss found .h file
target_include_directories(thor_static PRIVATE .)

install(TARGETS thor thor_static
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/thor)

# install pc for pkg-config configuration
install(FILES include/thor.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
