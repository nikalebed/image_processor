#pragma once

#include "base_filter.h"
class GrayScaleFilter : public BaseFilter {
public:
    void Apply(Bitmap& bmp) override;
};