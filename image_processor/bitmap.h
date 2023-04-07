#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include "color.h"

class PixelTable {
public:
    PixelTable() : storage_(nullptr), width_(0), height_(0) {
    }
    PixelTable(int width, int height, Pixel default_pixel = Pixel()) : PixelTable() {
        Resize(width, height, default_pixel);
    }
    PixelTable(const PixelTable& other);
    ~PixelTable() {
        FreeStorage();
    }

public:
    void Resize(int width, int height, const Pixel& default_pixel = Pixel());
    void CopyStorage(Pixel* new_storage, int new_height, int new_width,
                     Pixel default_pixel) const;  //заполняет new storage содержимым из storage
    Pixel GetClosestPixel(int i, int j) const;
    Pixel& GetPixel(int i, int j) {
        return storage_[i * width_ + j];
    }
    const Pixel& GetPixel(int i, int j) const {
        return storage_[i * width_ + j];
    }
    static Pixel& GetPixel(Pixel* storage, int width, int i, int j);
    int GetHeight() const {
        return height_;
    }
    int GetWidth() const {
        return width_;
    }

protected:
    Pixel* storage_;
    int width_;
    int height_;

protected:
    void FreeStorage();
    Pixel* AllocateStorage(int width, int height);  //закрытый - height, width !=0
};

class Bitmap {
public:
    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint32_t dummy;
        uint32_t offset;
    } __attribute__((__packed__));

    struct DIBHeader {
        uint32_t dib_header_size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t raw_bitmap_data_size;
        uint64_t dummy2;
        uint64_t dummy3;
    } __attribute__((__packed__));

    enum class LoadStatus { LOADED, UNRECOGNIZED_FILE_TYPE, COULD_NOT_OPEN_FILE, READING_FAILED};

protected:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    PixelTable pixel_table_;

public:
    Bitmap(){};
    Bitmap(std::string_view file_name) {
        Load(file_name);
    }

    LoadStatus Load(std::istream& stream);

    LoadStatus Load(const std::string_view file_name);

    bool Write(const std::string_view file_name);

    bool Write(std::ostream& stream);

    void Crop(int width, int height);

    int GetHeight() const {
        return pixel_table_.GetHeight();
    }
    int GetWidth() const {
        return pixel_table_.GetWidth();
    }
    Pixel& GetPixel(int i, int j) {
        return pixel_table_.GetPixel(i, j);
    }
    const Pixel& GetPixel(int i, int j) const {
        return pixel_table_.GetPixel(i, j);
    }
    Pixel GetClosestPixel(int i, int j) {
        return pixel_table_.GetClosestPixel(i, j);
    }

protected:
    bool IsValid(const BMPHeader& bmp_header);
    bool IsValid(const DIBHeader& dib_header);
    void FitBMPHeader();
    void FitDIBHeader();
    int PaddingBytes() const;
};
