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
#include <freetype2/freetype/config/ftheader.h>
#include FT_FREETYPE_H
#include <opencv2/opencv.hpp>
#include <wchar.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>
#include <cmath>

using namespace cv;

namespace thor
{

namespace vis
{

class CvxText
{
  public:
    CvxText(const char *freeType);
    virtual ~CvxText();
    void getFont(int *type, cv::Scalar *size = nullptr, bool *underline = nullptr, float *diaphaneity = nullptr);
    void setFont(int *type, cv::Scalar *size = nullptr, bool *underline = nullptr, float *diaphaneity = nullptr);

    void restoreFont();

    int putText(cv::Mat &img, char *text, cv::Point pos);
    int putText(cv::Mat &img, const wchar_t *text, cv::Point pos);
    int putText(cv::Mat &img, const char *text, cv::Point pos, cv::Scalar color);
    int putText(cv::Mat &img, const wchar_t *text, cv::Point pos, cv::Scalar color);

    inline static int ToWchar(char *&src, wchar_t *&dest, const char *locale = "zh_CN.utf8")
    {
        if (src == NULL)
        {
            dest = NULL;
            return 0;
        }
        setlocale(LC_CTYPE, locale);
        int w_size = mbstowcs(NULL, src, 0) + 1;
        if (w_size == 0)
        {
            dest = NULL;
            return -1;
        }
        dest = new wchar_t[w_size];
        if (!dest)
        {
            return -1;
        }
        int ret = mbstowcs(dest, src, strlen(src) + 1);
        if (ret <= 0)
        {
            return -1;
        }
        return 0;
    }

  private:
    CvxText &operator=(const CvxText &);
    void putWChar(cv::Mat &img, wchar_t wc, cv::Point &pos, cv::Scalar color);

    FT_Library m_library; // 字库
    FT_Face m_face;       // 字体
    int m_fontType;
    cv::Scalar m_fontSize;
    bool m_fontUnderline;
    float m_fontDiaphaneity;
};

struct RGB
{
    double r, g, b;
};

struct RGBA
{
    int r, g, b, a;
};

thor::vis::RGBA gen_unique_color(int idx, double hue_step, float alpha);

void hsv2rgb(float &r, float &g, float &b, int h, float s, double v);

cv::Mat createAlpha(cv::Mat &src);
int addAlpha(cv::Mat &src, cv::Mat &dst, cv::Mat &alpha);
} // namespace vis
} // namespace thor

#endif //CAO_VIS_H
