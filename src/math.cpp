//
// Created by JinTian on 02/01/2018.
//

#include "include/math.h"

namespace thor {
namespace math {

// !---------------- Simply math part
double CrossProd(const thor::datum::Vec2d &start_point, const thor::datum::Vec2d &end_point_1,
				 const thor::datum::Vec2d &end_point_2) {
  return (end_point_1 - start_point).CrossProd(end_point_2 - start_point);
}

double InnerProd(const thor::datum::Vec2d &start_point, const thor::datum::Vec2d &end_point_1,
				 const thor::datum::Vec2d &end_point_2) {
  return (end_point_1 - start_point).InnerProd(end_point_2 - start_point);
}

double CrossProd(const double x0, const double y0, const double x1,
				 const double y1) {
  return x0 * y1 - x1 * y0;
}

double InnerProd(const double x0, const double y0, const double x1,
				 const double y1) {
  return x0 * x1 + y0 * y1;
}

double WrapAngle(const double angle) {
  const double new_angle = std::fmod(angle, M_PI * 2.0);
  return new_angle < 0 ? new_angle + M_PI * 2.0 : new_angle;
}

double NormalizeAngle(const double angle) {
  double a = std::fmod(angle + M_PI, 2.0 * M_PI);
  if (a < 0.0) {
	a += (2.0 * M_PI);
  }
  return a - M_PI;
}

// double NormalizeAngle(double angle) {
//   double a = std::fmod(angle + M_PI, 2.0 * M_PI);
//   if (a < 0.0) {
//     a += (2.0 * M_PI);
//   }
//   return a - M_PI;
// }

double AngleDiff(const double from, const double to) {
  return NormalizeAngle(to - from);
}

int RandomInt(const int s, const int t, unsigned int rand_seed) {
  if (s >= t) {
	return s;
  }
  return s + rand_r(&rand_seed) % (t - s + 1);
}

double RandomDouble(const double s, const double t, unsigned int rand_seed) {
  return s + (t - s) / 16383.0 * (rand_r(&rand_seed) & 16383);
}

// Gaussian
double Gaussian(const double u, const double std, const double x) {
  return (1.0 / std::sqrt(2 * M_PI * std * std)) *
	  std::exp(-(x - u) * (x - u) / (2 * std * std));
}

// Sigmoid
double Sigmoid(const double x) { return 1.0 / (1.0 + std::exp(-x)); }

void RotateAxis(const double theta, const double x0, const double y0,
				double *x1, double *y1) {
  CHECK_NOTNULL(x1);
  CHECK_NOTNULL(y1);
  const double cos_theta = std::cos(theta);
  const double sin_theta = std::sin(theta);
  *x1 = x0 * cos_theta + y0 * sin_theta;
  *y1 = -x0 * sin_theta + y0 * cos_theta;
}

/**
 * n indicates how many terms in curve, more n, more accurate
 * @param key_point
 * @param n
 * @param A
 * @return
 */
bool polynomial_curve_fit(std::vector<cv::Point> &key_point, int n,
						  cv::Mat &A) {
  int N = key_point.size();
  cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
  for (int i = 0; i < n + 1; i++) {
	for (int j = 0; j < n + 1; j++) {
	  for (int k = 0; k < N; k++) {
		X.at<double>(i, j) =
			X.at<double>(i, j) + std::pow(key_point[k].x, i + j);
	  }
	}
  }

  cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
  for (int i = 0; i < n + 1; i++) {
	for (int k = 0; k < N; k++) {
	  Y.at<double>(i, 0) =
		  Y.at<double>(i, 0) + std::pow(key_point[k].x, i) * key_point[k].y;
	}
  }

  A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
  cv::solve(X, Y, A, cv::DECOMP_LU);
  return true;
}

bool ContinuousToDiscrete(
	const Eigen::MatrixXd &m_a, const Eigen::MatrixXd &m_b,
	const Eigen::MatrixXd &m_c, const Eigen::MatrixXd &m_d, const double ts,
	Eigen::MatrixXd *ptr_a_d, Eigen::MatrixXd *ptr_b_d,
	Eigen::MatrixXd *ptr_c_d, Eigen::MatrixXd *ptr_d_d) {
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

  if (m_a.cols() != m_b.rows() || m_b.cols() != m_d.cols() ||
	  m_c.rows() != m_d.rows() || m_a.cols() != m_c.cols()) {
	LOG(ERROR) << "ContinuousToDiscrete: matrix dimensions mismatch";
	return false;
  }
  Eigen::MatrixXd m_identity =
	  Eigen::MatrixXd::Identity(m_a.cols(), m_a.rows());
  *ptr_a_d =
	  (m_identity - ts * 0.5 * m_a).inverse() * (m_identity + ts * 0.5 * m_a);
  *ptr_b_d = (m_identity - ts * 0.5 * m_a).inverse() * m_b * std::sqrt(ts);
  // *ptr_b_d = std::sqrt(ts) * (m_identity - ts * 0.5 * m_a).inverse() * m_b;
  *ptr_c_d = std::sqrt(ts) * m_c * (m_identity - ts * 0.5 * m_a).inverse();
  *ptr_d_d = 0.5 * m_c * (m_identity - ts * 0.5 * m_a).inverse() * m_b + m_d;
  return true;
}
}
}
