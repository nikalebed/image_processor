#pragma once
#include "matrix_filter.h"
class SharpFilter : public MatrixFilter {
public:
    SharpFilter() {
        matrix_ = {{0, -1, 0},
                   {-1, 5, -1},
                   {0, -1, 0}};
    }
};