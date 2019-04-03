//
// Created by JinTian on 02/01/2018.
//

#ifndef CAO_MATH_H
#define CAO_MATH_H

#include "opencv2/opencv.hpp"

using namespace cv;


/**
 *  A math module do higher calculate
 */

namespace thor {
namespace math {
int add(int a, int b);

bool polynomial_curve_fit(std::vector<cv::Point> &key_point, int n, cv::Mat &A);

}
}

#endif //CAO_MATH_H
