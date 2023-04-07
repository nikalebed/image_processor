#include <fstream>
#include <algorithm>
#include "bitmap.h"
Bitmap::LoadStatus Bitmap::Load(std::istream& stream) {
    stream.read(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    if (!IsValid(bmp_header_)) {
        return LoadStatus::UNRECOGNIZED_FILE_TYPE;
    }
    stream.read(reinterpret_cast<char*>(&dib_header_), sizeof(dib_header_));
    if (!IsValid(dib_header_)) {
        return LoadStatus::UNRECOGNIZED_FILE_TYPE;
    }
    pixel_table_.Resize(dib_header_.width, dib_header_.height);
    for (size_t i = 0; i < pixel_table_.GetHeight(); ++i) {
        for (size_t j = 0; j < pixel_table_.GetWidth(); ++j) {
            try {
                stream.read(reinterpret_cast<char*>(&pixel_table_.GetPixel(i, j)), 3);
            } catch (...) {
                return LoadStatus::READING_FAILED;
            }
        }
        stream.ignore(PaddingBytes());
    }
    return LoadStatus::LOADED;
}
Bitmap::LoadStatus Bitmap::Load(const std::string_view file_name) {
    std::fstream file;
    file.open(file_name, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        return LoadStatus::COULD_NOT_OPEN_FILE;
    }
    return Load(file);
}
bool Bitmap::Write(const std::string_view file_name) {
    std::ofstream file;
    file.open(file_name, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    return Write(file);
}
bool Bitmap::Write(std::ostream& stream) {
    try {
        stream.write(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
        stream.write(reinterpret_cast<char*>(&dib_header_), sizeof(dib_header_));
        for (size_t i = 0; i < pixel_table_.GetHeight(); ++i) {
            for (size_t j = 0; j < pixel_table_.GetWidth(); ++j) {
                stream.write(reinterpret_cast<char*>(&pixel_table_.GetPixel(i, j)), 3);
            }
            int64_t tmp;
            stream.write(reinterpret_cast<const char*>(tmp), PaddingBytes());
        }
    } catch (...) {
        return false;
    }
    return true;
}
int Bitmap::PaddingBytes() const {
    return (4 - (pixel_table_.GetWidth() * dib_header_.bits_per_pixel / 8) % 4) % 4;
}

void Bitmap::Crop(int width, int height) {
    pixel_table_.Resize(width, height);
    FitBMPHeader();
    FitDIBHeader();
}

void Bitmap::FitBMPHeader() {
    bmp_header_.file_size =
        bmp_header_.offset + (pixel_table_.GetWidth() + PaddingBytes()) * pixel_table_.GetHeight() * 3;
}

void Bitmap::FitDIBHeader() {
    dib_header_.height = pixel_table_.GetHeight();
    dib_header_.width = pixel_table_.GetWidth();
}

bool Bitmap::IsValid(const Bitmap::BMPHeader& bmp_header) {
    return bmp_header.signature == 0x4D42;
}

bool Bitmap::IsValid(const Bitmap::DIBHeader& dib_header) {
    return dib_header.bits_per_pixel == 24;
}

void PixelTable::Resize(int width, int height, const Pixel& default_pixel) {
    if (width == width_ && height == height_) {
        return;
    }
    if (width == 0 || height == 0) {
        FreeStorage();
        return;
    }
    Pixel* new_storage = AllocateStorage(width, height);
    CopyStorage(new_storage, height, width, default_pixel);
    FreeStorage();
    storage_ = new_storage;
    width_ = width;
    height_ = height;
}

void PixelTable::FreeStorage() {
    delete[] storage_;
    storage_ = nullptr;
    height_ = 0;
    width_ = 0;
}
Pixel* PixelTable::AllocateStorage(int width, int height) {
    return new Pixel[width * height];
}

void PixelTable::CopyStorage(Pixel* new_storage, int new_height, int new_width, Pixel default_pixel) const {
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            if (i < height_ && j < width_) {
                GetPixel(new_storage, new_width, new_height - 1 - i, j) =
                    GetPixel(storage_, width_, height_ - 1 - i, j);
            } else {
                GetPixel(new_storage, new_width, i, j) = default_pixel;
            }
        }
    }
}

Pixel& PixelTable::GetPixel(Pixel* storage, int width, int i, int j) {
    return storage[width * i + j];
}

Pixel PixelTable::GetClosestPixel(int i, int j) const {
    return GetPixel(std::max(0, std::min(height_ - 1, i)), std::max(0, std::min(width_ - 1, j)));
}

PixelTable::PixelTable(const PixelTable& other) : PixelTable() {
    if (!other.storage_) {
        return;
    }
    storage_ = AllocateStorage(other.width_, other.height_);
    height_ = other.height_;
    width_ = other.width_;
    other.CopyStorage(storage_, height_, width_, Pixel());
}
