#include "negative_filter.h"
void NegativeFilter::Apply(Bitmap& bmp) {
    for (size_t i = 0; i < bmp.GetHeight(); ++i) {
        for (size_t j = 0; j < bmp.GetWidth(); ++j) {
            bmp.GetPixel(i, j) = Pixel::Negative(bmp.GetPixel(i, j));
        }
    }
}