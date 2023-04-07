#pragma once
#include <cstdint>

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
    bool operator==(const Pixel& other) const;
    bool operator!=(const Pixel& other) const;
    static Pixel Negative(const Pixel& p) {
        return {static_cast<uint8_t>(255 - p.blue),
                static_cast<uint8_t>(255 - p.green),
                static_cast<uint8_t>(255 - p.red)};
    }
}__attribute__((__packed__));

class Color {
public:
    constexpr static const Pixel WHITE_PIXEL = {255, 255, 255};
    constexpr static const Pixel BLACK_PIXEL = {0, 0, 0};
public:
    Color(double red = 0, double green = 0, double blue = 0) :
        red_(red), green_(green), blue_(blue) {}
    Color(const Pixel& p) : Color(static_cast<double>(p.red),
                                  static_cast<double>(p.green),
                                  static_cast<double>(p.blue)) {}
public:
    Pixel CreatePixel();
public:
    Color& operator+=(const Color& other) {
        red_ += other.red_;
        green_ += other.green_;
        blue_ += other.blue_;
        return *this;
    }
    Color operator*(double value) const {
        return {red_ * value, green_ * value, blue_ * value};
    }
protected:
    double red_;
    double green_;
    double blue_;
};