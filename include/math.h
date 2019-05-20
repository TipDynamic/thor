//
// Created by JinTian on 02/01/2018.
//

#ifndef CAO_MATH_H
#define CAO_MATH_H

#include <cmath>
#include <vector>

#include "assert.h"
#include "glog/logging.h"
#include "opencv2/opencv.hpp"

#include "Eigen/Core"
#include "Eigen/Eigen"
#include "datum.h"

using namespace google;
using namespace cv;
using namespace std;

/**
 *  A math module do higher calculate
 */

namespace thor {
namespace math {

using namespace thor::datum;

// !------------------- defines for normalise usage purpose
template <typename T>
inline T euclidean(vector<T> const &v_a, vector<T> const &v_b) {
  assert(v_a.size() == v_b.size());
  T sum = 0.;
  for (size_t i = 0; i < v_a.size(); i++) {
    sum += pow(v_a[i] - v_b[i], 2);
  }
  sum = sqrt(sum);
  return sum;
}
bool polynomial_curve_fit(std::vector<cv::Point> &key_point, int n, cv::Mat &A);

inline double Sqr(const double x) { return x * x; };

double CrossProd(const thor::datum::Vec2d &start_point, const thor::datum::Vec2d &end_point_1,
                 const thor::datum::Vec2d &end_point_2);
double InnerProd(const thor::datum::Vec2d &start_point, const thor::datum::Vec2d &end_point_1,
                 const thor::datum::Vec2d &end_point_2);
double CrossProd(const double x0, const double y0, const double x1,
                 const double y1);
double InnerProd(const double x0, const double y0, const double x1,
                 const double y1);
double WrapAngle(const double angle);

double NormalizeAngle(const double angle);
// double NormalizeAngle(double angle);
double AngleDiff(const double from, const double to);

// generates random values
int RandomInt(const int s, const int t, unsigned int rand_seed = 1);
double RandomDouble(const double s, const double t, unsigned int rand_seed = 1);

template <typename T>
inline T Square(const T value) {
  return value * value;
}

template <typename T>
T Clamp(const T value, T bound1, T bound2) {
  if (bound1 > bound2) {
    std::swap(bound1, bound2);
  }

  if (value < bound1) {
    return bound1;
  } else if (value > bound2) {
    return bound2;
  }
  return value;
}

// for Generate a distribution
double Gaussian(const double u, const double std, const double x);
double Sigmoid(const double x);

void RotateAxis(const double theta, const double x0, const double y0,
                double *x1, double *y1);

inline std::pair<double, double> RFUToFLU(const double x, const double y) {
  return std::make_pair(y, -x);
}

inline std::pair<double, double> FLUToRFU(const double x, const double y) {
  return std::make_pair(-y, x);
}

inline void L2Norm(int feat_dim, float *feat_data) {
  if (feat_dim == 0) {
    return;
  }
  // feature normalization
  float l2norm = 0.0;
  for (int i = 0; i < feat_dim; ++i) {
    l2norm += feat_data[i] * feat_data[i];
  }
  if (l2norm == 0) {
    float val = 1.0 / std::sqrt(feat_dim);
    for (int i = 0; i < feat_dim; ++i) {
      feat_data[i] = val;
    }
  } else {
    l2norm = std::sqrt(l2norm);
    for (int i = 0; i < feat_dim; ++i) {
      feat_data[i] /= l2norm;
    }
  }
}

// !---------------- define using for Matrix calculation
template <typename T, unsigned int N>
Eigen::Matrix<T, N, N> PseudoInverse(const Eigen::Matrix<T, N, N> &m,
                                     const double epsilon = 1.0e-6) {
  Eigen::JacobiSVD<Eigen::Matrix<T, N, N>> svd(
      m, Eigen::ComputeFullU | Eigen::ComputeFullV);
  return svd.matrixV() *
         (svd.singularValues().array().abs() > epsilon)
             .select(svd.singularValues().array().inverse(), 0)
             .matrix()
             .asDiagonal() *
         svd.matrixU().adjoint();
}

/**
 * @brief Computes the Moore-Penrose pseudo-inverse of a given matrix,
 * rounding all eigenvalues with absolute value bounded by epsilon to zero.
 *
 * @param m The matrix to be pseudo-inverted
 * @param epsilon A small positive real number (optional; default is 1.0e-6).
 *
 * @return Moore-Penrose pseudo-inverse of the given matrix.
 */
template <typename T, unsigned int M, unsigned int N>
Eigen::Matrix<T, N, M> PseudoInverse(const Eigen::Matrix<T, M, N> &m,
                                     const double epsilon = 1.0e-6) {
  Eigen::Matrix<T, M, M> t = m * m.transpose();
  return m.transpose() * PseudoInverse<T, M>(t);
}

/**
* @brief Computes bilinear transformation of the continuous to discrete form
for state space representation
* This assumes equation format of
*
*           dot_x = Ax + Bu
*           y = Cx + Du
*
*
*
* @param m_a, m_b, m_c, m_d are the state space matrix control matrix
*
* @return true or false.

 */
template <typename T, unsigned int L, unsigned int N, unsigned int O>
bool ContinuousToDiscrete(const Eigen::Matrix<T, L, L> &m_a,
                          const Eigen::Matrix<T, L, N> &m_b,
                          const Eigen::Matrix<T, O, L> &m_c,
                          const Eigen::Matrix<T, O, N> &m_d, const double ts,
                          Eigen::Matrix<T, L, L> *ptr_a_d,
                          Eigen::Matrix<T, L, N> *ptr_b_d,
                          Eigen::Matrix<T, O, L> *ptr_c_d,
                          Eigen::Matrix<T, O, N> *ptr_d_d) {
  if (ts <= 0.0) {
    LOG(ERROR) << "ContinuousToDiscrete : ts is less than or equal to zero";
    return false;
  }

  // Only matrix_a is mandatory to be non-zeros in matrix
  // conversion.
  if (m_a.rows() == 0) {
    LOG(ERROR) << "ContinuousToDiscrete: matrix_a size 0 ";
    return false;
  }

  Eigen::Matrix<T, L, L> m_identity = Eigen::Matrix<T, L, L>::Identity();
  *ptr_a_d = PseudoInverse<T, L>(m_identity - ts * 0.5 * m_a) *
             (m_identity + ts * 0.5 * m_a);

  *ptr_b_d =
      std::sqrt(ts) * PseudoInverse<T, L>(m_identity - ts * 0.5 * m_a) * m_b;

  *ptr_c_d =
      std::sqrt(ts) * m_c * PseudoInverse<T, L>(m_identity - ts * 0.5 * m_a);

  *ptr_d_d =
      0.5 * m_c * PseudoInverse<T, L>(m_identity - ts * 0.5 * m_a) * m_b + m_d;
  return true;
}

bool ContinuousToDiscrete(const Eigen::MatrixXd &m_a,
                          const Eigen::MatrixXd &m_b,
                          const Eigen::MatrixXd &m_c,
                          const Eigen::MatrixXd &m_d, const double ts,
                          Eigen::MatrixXd *ptr_a_d, Eigen::MatrixXd *ptr_b_d,
                          Eigen::MatrixXd *ptr_c_d, Eigen::MatrixXd *ptr_d_d);

}  // namespace math
}  // namespace thor

#endif  // CAO_MATH_H
