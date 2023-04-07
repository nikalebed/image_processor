#pragma once
#import "base_filter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(int width, int height) : new_height_(height), new_width_(width) {}
    void Apply(Bitmap& bmp) override;
protected:
    int new_height_;
    int new_width_;
};