#include "crop_filter.h"
void CropFilter::Apply(Bitmap& bmp) {
    new_width_ = std::min(new_width_, bmp.GetWidth());
    new_height_ = std::min(new_height_, bmp.GetHeight());
    bmp.Crop(new_width_, new_height_);
}
