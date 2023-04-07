#pragma once
#include "bitmap.h"
class BaseFilter{
public:
    virtual void Apply(Bitmap& bmp) = 0;
    virtual ~BaseFilter()=default;
};