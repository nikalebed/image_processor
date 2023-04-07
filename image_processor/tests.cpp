#include <catch.hpp>
#include "bitmap.h"
#include "cmd_line_parser.h"
#include "application.h"
#include "crop_filter.h"
#include "negative_filter.h"
#include "gs_filter.h"

namespace {
std::unique_ptr<char> program_name(new char[]{"name"});
std::unique_ptr<char> input_file_name(new char[]{"../projects/image_processor/examples/test_example.bmp"});
std::unique_ptr<char> output_file_name(new char[]{"../projects/image_processor/examples/changed.bmp"});
std::unique_ptr<char> arg1(new char[]{"-neg"});
std::unique_ptr<char> arg2(new char[]{"-crop"});
std::unique_ptr<char> arg3(new char[]{"1"});
std::unique_ptr<char> arg4(new char[]{"223423"});

std::string_view test_file_name = "../projects/image_processor/examples/test_example.bmp";
std::string_view changed_file_name = "../projects/image_processor/examples/changed.bmp";

char* argv[] = {program_name.get(), input_file_name.get(), output_file_name.get(), arg1.get(), arg2.get(), arg3.get(),
                arg4.get()};
size_t argc = 7;

}  // namespace

TEST_CASE("Parser") {
    CmdLineParser parser;
    parser.Parse(argc, argv);
    REQUIRE(parser.GetInputFileName() == input_file_name.get());
    REQUIRE(parser.GetOutputFileName() == output_file_name.get());
    REQUIRE(parser.GetFilterDescriptors()[0].filter_name == "neg");
}
TEST_CASE("Pixels and Colors") {
    Pixel p1;
    REQUIRE(p1 == Color::BLACK_PIXEL);
    Pixel p2 = Color::WHITE_PIXEL;
    REQUIRE(p1 != p2);
    REQUIRE(p1 == Pixel::Negative(p2));
    Color c(p1);
    c += p2;
    REQUIRE(c.CreatePixel() == Color::WHITE_PIXEL);
    c = Color(Pixel{1, 2, 3}) * 123.3453;
    REQUIRE(c.CreatePixel() == Pixel{123, 246, 255});
    c = c * (-1);
    REQUIRE(c.CreatePixel() == Color::BLACK_PIXEL);
}

TEST_CASE("Pixel Table") {
    PixelTable pt;
    pt.Resize(20, 30, {1, 2, 3});
    REQUIRE(pt.GetWidth() == 20);
    REQUIRE(pt.GetHeight() == 30);
    REQUIRE(pt.GetPixel(25, 3) == Pixel{1, 2, 3});
    pt.GetPixel(10, 25) = Color::WHITE_PIXEL;
    PixelTable pt2 = pt;
    REQUIRE(pt.GetPixel(25, 3) == Pixel{1, 2, 3});
    REQUIRE(pt.GetPixel(10, 25) == Color::WHITE_PIXEL);
}

TEST_CASE("Bitmap") {
    Bitmap bmp("../projects/image_processor/examples/example.bmp");
    REQUIRE(bmp.GetHeight() == 2048);
    bmp.Load(test_file_name);
    bmp.Write(changed_file_name);
    bmp.Load(changed_file_name);
    REQUIRE(bmp.GetHeight() == 2);
    REQUIRE(bmp.GetPixel(1, 0) == Pixel());
}

TEST_CASE("CropFilter") {
    Bitmap bmp;
    bmp.Load(test_file_name);
    CropFilter crop_filter(1, 45645456);
    crop_filter.Apply(bmp);
    REQUIRE(bmp.GetWidth() == 1);
    REQUIRE(bmp.GetHeight() == 2);
}

TEST_CASE("NegativeFilter") {
    Bitmap bmp;
    bmp.Load(test_file_name);
    REQUIRE(bmp.GetPixel(1, 0) == Color::BLACK_PIXEL);
    bmp.Load(test_file_name);
    NegativeFilter neg_filter;
    neg_filter.Apply(bmp);
    REQUIRE(bmp.GetPixel(1, 0) == Color::WHITE_PIXEL);
    REQUIRE(bmp.GetPixel(1, 1) == Pixel{255, 255, 0});
    REQUIRE(bmp.GetPixel(0, 0) == Pixel{255, 0, 255});
    REQUIRE(bmp.GetPixel(0, 1) == Pixel{0, 255, 255});
}

TEST_CASE("GrayscaleFilter") {
    Bitmap bmp;
    bmp.Load(test_file_name);
    GrayScaleFilter gs_filter;
    gs_filter.Apply(bmp);
    REQUIRE(bmp.GetPixel(1, 0) == Pixel{0, 0, 0});
    REQUIRE(bmp.GetPixel(1, 1) == Pixel{76, 76, 76});     // 255 * 0.114 = 29.07 формула для синего
    REQUIRE(bmp.GetPixel(0, 0) == Pixel{149, 149, 149});  // 255 * 0.587 = 149.685 формула для зеленого
    REQUIRE(bmp.GetPixel(0, 1) == Pixel{29, 29, 29});     // 255 * 0.299 = 16.245 формула для красного
}

TEST_CASE("FilterPipeline") {
    Bitmap bmp(test_file_name);
    std::vector<std::shared_ptr<BaseFilter>> filters;
    filters.push_back(std::shared_ptr<BaseFilter>(new CropFilter(1, 2)));
    FilterPipeline fp(filters);
    fp.Apply(bmp);
    REQUIRE(bmp.GetWidth() == 1);
    fp.AddFilter(new NegativeFilter());
    bmp.Load(test_file_name);
    fp.Apply(bmp);
    bmp.Write(changed_file_name);
    REQUIRE(bmp.GetWidth() == 1);
    REQUIRE(bmp.GetPixel(1, 0) == Pixel{Color::WHITE_PIXEL});
}

TEST_CASE("FilterPipelineFactory") {
    FilterPipelineFactory fpf;
    fpf.AddFilterMaker("neg", &FilterMakers::MakeNegativeFilter);
    FilterDescriptor fd = {"neg", {}};
    BaseFilter* filter = fpf.CreateFilter(fd);
    Bitmap bmp(test_file_name);
    filter->Apply(bmp);
    REQUIRE(bmp.GetPixel(1, 0) == Color::WHITE_PIXEL);
    REQUIRE(bmp.GetPixel(1, 1) == Pixel{255, 255, 0});
    REQUIRE(bmp.GetPixel(0, 0) == Pixel{255, 0, 255});
    REQUIRE(bmp.GetPixel(0, 1) == Pixel{0, 255, 255});
    delete filter;
}

TEST_CASE("Application") {
    Application app;
    app.Run(argc, argv);
    Bitmap bmp(output_file_name.get());
    REQUIRE(bmp.GetWidth() == 1);
    REQUIRE(bmp.GetHeight() == 2);
    REQUIRE(bmp.GetPixel(1, 0) == Pixel{Color::WHITE_PIXEL});
}
