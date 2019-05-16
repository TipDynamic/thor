//
// Created by jintian on 18-1-12.
//

#include "include/vis.h"

cv::Scalar thor::vis::gen_unique_color_cv(int idx, bool is_track, double hue_step, float alpha) {
  RGBA cr = gen_unique_color(idx, is_track, hue_step, alpha);
  cv::Scalar c(cr.r, cr.g, cr.b, cr.a);
  return c;
}

thor::vis::RGBA thor::vis::gen_unique_color(int idx, bool is_track, double hue_step,
                                            float alpha) {

  // if idx is track id, the color should be 
  if (is_track) {
    // we may have 1000+ track ids
    hue_step = 1./9.;
    idx = idx%9;
  }
  auto h = int(idx * (360 * hue_step));
  // 1/5 values we will not use
  double v = 1.0 - ((idx * 1.0) * hue_step) / 5.;
  float s = 1;
  float r, g, b;
  thor::vis::hsv2rgb(r, g, b, h, s, v);

  thor::vis::RGBA rgba;
  rgba.r = int(255 * r);
  rgba.g = int(255 * g);
  rgba.b = int(255 * b);
  rgba.a = int(alpha * 255);
  return rgba;
}

void thor::vis::hsv2rgb(float &r, float &g, float &b, int h, float s,
                        double v) {
  double hh, p, q, t, ff;
  long i;
  if (s <= 0.0) {  // < is bogus, just shuts up warnings
    r = float(v);
    g = float(v);
    b = float(v);
  }
  hh = h;
  if (hh >= 360.0) hh = 0.0;
  hh /= 60.0;
  i = (long)hh;
  ff = hh - i;
  p = v * (1.0 - s);
  q = v * (1.0 - (s * ff));
  t = v * (1.0 - (s * (1.0 - ff)));
  switch (i) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;

    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    case 5:
    default:
      r = v;
      g = p;
      b = q;
      break;
  }
}

cv::Mat thor::vis::createAlpha(cv::Mat &src) {
  cv::Mat alpha = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
  cv::Mat gray = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
  cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
      alpha.at<uchar>(i, j) = 255 - gray.at<uchar>(i, j);
    }
  }
  return alpha;
}

int thor::vis::addAlpha(cv::Mat &src, cv::Mat &dst, cv::Mat &alpha) {
  if (src.channels() == 4) {
    return -1;
  } else if (src.channels() == 1) {
    cv::cvtColor(src, src, cv::COLOR_GRAY2RGB);
  }

  dst = cv::Mat(src.rows, src.cols, CV_8UC4);

  std::vector<cv::Mat> srcChannels;
  std::vector<cv::Mat> dstChannels;
  cv::split(src, srcChannels);

  dstChannels.push_back(srcChannels[0]);
  dstChannels.push_back(srcChannels[1]);
  dstChannels.push_back(srcChannels[2]);
  dstChannels.push_back(alpha);
  cv::merge(dstChannels, dst);
  return 0;
}
