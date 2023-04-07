#include "edge_detection_filter.h"
void EdgeDetectionFilter::Apply(Bitmap& bmp) {
    gray_scale_filter_.Apply(bmp);
    MatrixFilter::Apply(bmp);
    for (int i = 0; i < bmp.GetHeight(); ++i) {
        for (int j = 0; j < bmp.GetWidth(); ++j) {
            if (bmp.GetPixel(i, j).blue > threshold_) {
                bmp.GetPixel(i, j) = Color::WHITE_PIXEL;
            } else {
                bmp.GetPixel(i, j) = Color::BLACK_PIXEL;
            }
        }
    }
}
