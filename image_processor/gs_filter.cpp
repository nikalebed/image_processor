#include "gs_filter.h"
void GrayScaleFilter::Apply(Bitmap& bmp) {
    for (size_t i = 0; i < bmp.GetHeight(); ++i) {
        for (size_t j = 0; j < bmp.GetWidth(); ++j) {
            uint8_t value = bmp.GetPixel(i, j).blue * 0.114+
                bmp.GetPixel(i, j).green * 0.587 +
                bmp.GetPixel(i, j).red * 0.299;
            bmp.GetPixel(i, j).blue = value;
            bmp.GetPixel(i, j).green = value;
            bmp.GetPixel(i, j).red = value;
        }
    }
}
