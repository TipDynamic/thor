#ifndef COMMON_STRUCTURE_H
#define COMMON_STRUCTURE_H


#include "iostream"
#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
// define some common structures that we need

namespace thor{
    struct Box
    {
        // left, top, right, bottom
        // left top is the origin
        int x;
        int y;
        int w;
        int h;

        // box score, only for prediction
        float score;
        // label index
        int idx;
    };

    struct CameraIntrinsicParams{
        double fx, fy, cx, cy, scale;
        inline void print(){
          std::cout << "fx: " << fx << " fy: " << fy << " cx: " << cx
          << " cy:" << cy << " scale: " << scale << endl;
        };
        inline cv::Mat toCameraMatrix() {
          // convert to a cv::Mat matrix
          double camera_matrix_data[3][4] = {
                  {fx, 0, cx},
                  {0, fy, cy},
                  {0, 0, 1}
          };
          cv::Mat camera_mat(3, 3, CV_64F, camera_matrix_data);
          return camera_mat;
        }
    };
}

#endif // COMMON_STRUCTURE_H
