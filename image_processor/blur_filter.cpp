#include "blur_filter.h"
#include <cmath>
void BlurFilter::FillGaussianMatrix() {
    double matrix_sum = 0;
    matrix_.resize(sigma_ * 2 + 1);
    for (int i = 0; i < matrix_.size(); ++i) {
        matrix_[i].resize(sigma_ * 2 + 1);
        for (int j = 0; j < matrix_[i].size(); ++j) {
            matrix_[i][j] = Gaussian(i - sigma_, j - sigma_);
            matrix_sum += matrix_[i][j];
        }
    }
    for (int i = 0; i < matrix_.size(); ++i) {
        for (int j = 0; j < matrix_[i].size(); ++j) {
            matrix_[i][j] /= matrix_sum;
        }
    }
}
double BlurFilter::Gaussian(double x, double y) {
    return std::pow(M_E, (-x * x - y * y) / (2 * sigma_ * sigma_)) * M_1_PI / (2 * sigma_ * sigma_);
}
