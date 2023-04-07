#pragma once

#include "matrix_filter.h"
#include "gs_filter.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    explicit EdgeDetectionFilter(uint8_t threshold = 0) : threshold_(threshold) {
        matrix_ = {{0, -1, 0},
                   {-1, 4, -1},
                   {0, -1, 0}};
    }
    void Apply(Bitmap& bmp) override;
protected:
    GrayScaleFilter gray_scale_filter_;
    uint8_t threshold_;
};
