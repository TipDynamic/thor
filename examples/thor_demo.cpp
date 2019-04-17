//
// Created by JinTian on 02/01/2018.
//

/**
 * A simple example of using Thor library
 */

#include <iostream>
#include "thor/colors.h"
#include "thor/os.h"
#include "thor/math.h"
#include "thor/logging.h"
#include "thor/slam.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "./include/dog.h"
#include "thor/app_license.h"
#include "thor/vis.h"

using namespace std;
using namespace thor;
using namespace cv;


static int ToWchar(char* &src, wchar_t* &dest, const char *locale = "zh_CN.utf8")
{
  if (src == NULL) {
    dest = NULL;
    return 0;
  }

  // 根据环境变量设置locale
  setlocale(LC_CTYPE, locale);

  // 得到转化为需要的宽字符大小
  int w_size = mbstowcs(NULL, src, 0) + 1;

  // w_size = 0 说明mbstowcs返回值为-1。即在运行过程中遇到了非法字符(很有可能使locale
  // 没有设置正确)
  if (w_size == 0) {
    dest = NULL;
    return -1;
  }

  //wcout << "w_size" << w_size << endl;
  dest = new wchar_t[w_size];
  if (!dest) {
    return -1;
  }

  int ret = mbstowcs(dest, src, strlen(src)+1);
  if (ret <= 0) {
    return -1;
  }
  return 0;
}

int main(int argc, char **argv) {

  cout << "Welcome!\n";
  cout << colors::bold << colors::yellow << "thor library\n"
       << colors::reset;

  if (thor::os::isdir("../")) {
    cout << colors::green << "and this is a " << colors::bold << colors::yellow << "dir.\n";
    vector<string> allFiles;
    allFiles = thor::os::list_files("../", true);
    cout << "list all files under it:\n";
    for (auto f : allFiles) {
      cout << f << endl;
    }
  }
  cout << colors::reset;

  string p = "/media/netac/a.mp4";
  string suffix = thor::os::suffix(p);
  cout << "suffix: " << suffix << endl;

  thor::Log(kInfo, "this a log test.");

  vector<float> a = {4.5, 6.5, 6, 7, 9};
  vector<float> b = {4.1, 3.5, 4, 7, 9};

  float res = thor::math::euclidean(a, b);
  cout << "euclidean res: " << to_string(res) << endl;

  cv::Mat img = cv::imread("../1.png");
  if (!img.data || img.channels() != 3) {
    fprintf(stderr, "read image fail\n");
    return -1;
  }

  thor::vis::CvxText cvText("../FZSSJW.TTF"); //指定字体
  cv::Scalar size1{38, 0.5, 0.1, 0}; // (字体大小, 无效的, 字符间距, 无效的 }
  cvText.setFont(nullptr, &size1, nullptr, 0);
  char* str = (char *)"你好，世界!";
  wchar_t *w_str;
  ToWchar(str,w_str);
  cvText.putText(img, w_str, cv::Point(50, 100), cv::Scalar(255, 0, 255));
  cv::imshow("demo", img);
  cv::waitKey(0);
  return 0;
}
