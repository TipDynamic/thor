//
// Created by jintian on 18-1-12.
//

#include "include/vis.h"

thor::vis::RGBA thor::vis::gen_unique_color(int idx, double hue_step, float alpha)
{
    auto h = int(idx * (360 * hue_step));
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

void thor::vis::hsv2rgb(float &r, float &g, float &b, int h, float s, double v)
{
    double hh, p, q, t, ff;
    long i;
    if (s <= 0.0)
    { // < is bogus, just shuts up warnings
        r = float(v);
        g = float(v);
        b = float(v);
    }
    hh = h;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));
    switch (i)
    {
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

cv::Mat thor::vis::createAlpha(cv::Mat &src)
{
    cv::Mat alpha = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    cv::Mat gray = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            alpha.at<uchar>(i, j) = 255 - gray.at<uchar>(i, j);
        }
    }
    return alpha;
}

int thor::vis::addAlpha(cv::Mat &src, cv::Mat &dst, cv::Mat &alpha)
{
    if (src.channels() == 4)
    {
        return -1;
    }
    else if (src.channels() == 1)
    {
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

// ----------------------- implementation of CvxText in opencv ------------------
thor::vis::CvxText::CvxText(const char *freeType)
{
    assert(freeType != NULL);

    // 打开字库文件, 创建一个字体
    if (FT_Init_FreeType(&m_library))
        throw;
    if (FT_New_Face(m_library, freeType, 0, &m_face))
        throw;

    // 设置字体输出参数
    restoreFont();

    // 设置C语言的字符集环境
    setlocale(LC_ALL, "");
}

// 释放FreeType资源
thor::vis::CvxText::~CvxText()
{
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_library);
}

// 设置字体参数:
//
// font         - 字体类型, 目前不支持
// size         - 字体大小/空白比例/间隔比例/旋转角度
// underline   - 下画线
// diaphaneity   - 透明度
void thor::vis::CvxText::getFont(int *type, cv::Scalar *size, bool *underline, float *diaphaneity)
{
    if (type)
        *type = m_fontType;
    if (size)
        *size = m_fontSize;
    if (underline)
        *underline = m_fontUnderline;
    if (diaphaneity)
        *diaphaneity = m_fontDiaphaneity;
}

void thor::vis::CvxText::setFont(int *type, cv::Scalar *size, bool *underline, float *diaphaneity)
{
    // 参数合法性检查
    if (type)
    {
        if (type >= 0)
            m_fontType = *type;
    }
    if (size)
    {
        m_fontSize.val[0] = std::fabs(size->val[0]);
        m_fontSize.val[1] = std::fabs(size->val[1]);
        m_fontSize.val[2] = std::fabs(size->val[2]);
        m_fontSize.val[3] = std::fabs(size->val[3]);
    }
    if (underline)
    {
        m_fontUnderline = *underline;
    }
    if (diaphaneity)
    {
        m_fontDiaphaneity = *diaphaneity;
    }

    FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}

// 恢复原始的字体设置
void thor::vis::CvxText::restoreFont()
{
    m_fontType = 0; // 字体类型(不支持)

    m_fontSize.val[0] = 20;  // 字体大小
    m_fontSize.val[1] = 0.5; // 空白字符大小比例
    m_fontSize.val[2] = 0.1; // 间隔大小比例
    m_fontSize.val[3] = 0;   // 旋转角度(不支持)

    m_fontUnderline = false; // 下画线(不支持)

    m_fontDiaphaneity = 1.0; // 色彩比例(可产生透明效果)

    // 设置字符大小
    FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}

// 输出函数(颜色默认为白色)
int thor::vis::CvxText::putText(cv::Mat &img, char *text, cv::Point pos)
{
    return putText(img, text, pos, CV_RGB(255, 255, 255));
}

int thor::vis::CvxText::putText(cv::Mat &img, const wchar_t *text, cv::Point pos)
{
    return putText(img, text, pos, CV_RGB(255, 255, 255));
}

int thor::vis::CvxText::putText(cv::Mat &img, const char *text, cv::Point pos, cv::Scalar color)
{
    if (img.data == nullptr)
        return -1;
    if (text == nullptr)
        return -1;

    int i;
    for (i = 0; text[i] != '\0'; ++i)
    {
        wchar_t wc = text[i];

        // 解析双字节符号
        if (!isascii(wc))
            mbtowc(&wc, &text[i++], 2);

        // 输出当前的字符
        putWChar(img, wc, pos, color);
    }

    return i;
}

int thor::vis::CvxText::putText(cv::Mat &img, const wchar_t *text, cv::Point pos, cv::Scalar color)
{
    if (img.data == nullptr)
        return -1;
    if (text == nullptr)
        return -1;

    int i;
    for (i = 0; text[i] != '\0'; ++i)
    {
        // 输出当前的字符
        putWChar(img, text[i], pos, color);
    }

    return i;
}

// 输出当前字符, 更新m_pos位置
void thor::vis::CvxText::putWChar(cv::Mat &img, wchar_t wc, cv::Point &pos, cv::Scalar color)
{
    // 根据unicode生成字体的二值位图
    FT_UInt glyph_index = FT_Get_Char_Index(m_face, wc);
    FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);

    FT_GlyphSlot slot = m_face->glyph;

    // 行列数
    int rows = slot->bitmap.rows;
    int cols = slot->bitmap.width;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int off = i * slot->bitmap.pitch + j / 8;

            if (slot->bitmap.buffer[off] & (0xC0 >> (j % 8)))
            {
                int r = pos.y - (rows - 1 - i);
                int c = pos.x + j;

                if (r >= 0 && r < img.rows && c >= 0 && c < img.cols)
                {
                    cv::Vec3b pixel = img.at<cv::Vec3b>(cv::Point(c, r));
                    cv::Scalar scalar = cv::Scalar(pixel.val[0], pixel.val[1], pixel.val[2]);

                    // 进行色彩融合
                    float p = m_fontDiaphaneity;
                    for (int k = 0; k < 4; ++k)
                    {
                        scalar.val[k] = scalar.val[k] * (1 - p) + color.val[k] * p;
                    }

                    img.at<cv::Vec3b>(cv::Point(c, r))[0] = (unsigned char)(scalar.val[0]);
                    img.at<cv::Vec3b>(cv::Point(c, r))[1] = (unsigned char)(scalar.val[1]);
                    img.at<cv::Vec3b>(cv::Point(c, r))[2] = (unsigned char)(scalar.val[2]);
                }
            }
        }
    }

    // 修改下一个字的输出位置
    double space = m_fontSize.val[0] * m_fontSize.val[1];
    double sep = m_fontSize.val[0] * m_fontSize.val[2];

    pos.x += (int)((cols ? cols : space) + sep);
}
