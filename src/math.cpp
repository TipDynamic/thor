//
// Created by JinTian on 02/01/2018.
//

#include "include/math.h"


/**
 * n indicates how many terms in curve, more n, more accurate
 * @param key_point
 * @param n
 * @param A
 * @return
 */
bool thor::math::polynomial_curve_fit(std::vector<cv::Point> &key_point, int n, cv::Mat &A){
    int N = key_point.size();
    cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            for (int k = 0; k < N; k++) {
                X.at<double>(i, j) = X.at<double>(i, j) +
                    std::pow(key_point[k].x, i + j);
            }
        }
    }

    cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
    for (int i = 0; i < n + 1; i++) {
        for (int k = 0; k < N; k++) {
            Y.at<double>(i, 0) = Y.at<double>(i, 0) +
                std::pow(key_point[k].x, i) * key_point[k].y;
        }
    }

    A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
    cv::solve(X, Y, A, cv::DECOMP_LU);
    return true;
}

