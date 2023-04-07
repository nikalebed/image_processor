#pragma once
#include "base_filter.h"
#include "bitmap.h"

class NegativeFilter:public BaseFilter{
public:
    void Apply(Bitmap& bmp) override;
};