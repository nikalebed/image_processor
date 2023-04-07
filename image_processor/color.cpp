#include <algorithm>
#include "color.h"
Pixel Color::CreatePixel() {
    return Pixel{static_cast<uint8_t>(std::min(255., std::max(0., blue_))),
                 static_cast<uint8_t>(std::min(255., std::max(0., green_))),
                 static_cast<uint8_t>(std::min(255., std::max(0., red_)))
    };
}
bool Pixel::operator==(const Pixel& other) const {
    return std::tie(blue, green, red) == std::tie(other.blue, other.green, other.red);
}
bool Pixel::operator!=(const Pixel& other) const {
    return !(*this == other);
}
