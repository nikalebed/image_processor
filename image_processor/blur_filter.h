#pragma once
#include "matrix_filter.h"

class BlurFilter : public MatrixFilter {
public:
    BlurFilter(int sigma) : sigma_(sigma){
        FillGaussianMatrix();
    }

protected:
    int sigma_;

protected:
    void FillGaussianMatrix();
    double Gaussian(double x, double y);
};