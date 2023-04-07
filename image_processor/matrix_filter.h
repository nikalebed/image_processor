#pragma once

#include <vector>
#include "base_filter.h"

class MatrixFilter : public BaseFilter {
public:
    void Apply(Bitmap& bmp) override;
protected:
    std::vector<std::vector<double>> matrix_;
};