#include "matrix_filter.h"
void MatrixFilter::Apply(Bitmap& bmp) {
    Bitmap initial_bmp = bmp;
    std::vector<Pixel> adjacent_pixels;
    Color color;
    for (int i = 0; i < bmp.GetHeight(); ++i) {
        for (int j = 0; j < bmp.GetWidth(); ++j) {
            color = Color();
            for (int y = 0; y < matrix_.size(); ++y) {
                for (int x = 0; x < matrix_.size(); ++x) {
                    color += Color(initial_bmp.GetClosestPixel(i + y - matrix_.size()/2, j + x - matrix_.size()/2)) * matrix_[y][x];
                }
            }
            bmp.GetPixel(i, j) = color.CreatePixel();
        }
    }
}
