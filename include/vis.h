//
// Created by jintian on 18-1-12.
//

#ifndef CAO_VIS_H
#define CAO_VIS_H

/**
 *  Vision module in cao
 *  the module provide some utility methods to draw bboxes
 */
#include <iostream>
#include <vector>
#include <string>

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <sys/stat.h>
#include <map>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"


using namespace cv;

namespace thor {
namespace vis {

struct RGB {
  double r, g, b;
};

struct RGBA {
  int r, g, b, a;
};

thor::vis::RGBA gen_unique_color(int idx, double hue_step, float alpha);

void hsv2rgb(float &r, float &g, float &b, int h, float s, double v);

cv::Mat createAlpha(cv::Mat &src);
int addAlpha(cv::Mat &src, cv::Mat &dst, cv::Mat &alpha);
} // namespace vis
} // namespace thor

#endif //CAO_VIS_H
