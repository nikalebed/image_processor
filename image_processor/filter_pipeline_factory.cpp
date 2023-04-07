#include "filter_pipeline_factory.h"
#include "negative_filter.h"
#include "gs_filter.h"
#include "sharp_filter.h"
#include "edge_detection_filter.h"
#include "crop_filter.h"
#include "blur_filter.h"

namespace FilterMakers {

int SVtoInt(const std::string_view& sv) {
    return std::stoi(static_cast<std::string>(sv));
}

BaseFilter* MakeNegativeFilter(const FilterDescriptor& fd) {
    if (fd.filter_name != "neg") {
        throw std::invalid_argument("wrong negative filter descriptor\n");
    }
    if (!fd.filter_params.empty()) {
        throw std::invalid_argument("wrong negative filter arguments, no arguments expected\n");
    }
    return new NegativeFilter;
}

BaseFilter* MakeGrayscaleFilter(const FilterDescriptor& fd) {
    if (fd.filter_name != "gs") {
        throw std::invalid_argument("wrong grayscale filter descriptor\n");
    }
    if (!fd.filter_params.empty()) {
        throw std::invalid_argument("wrong grayscale filter arguments, no arguments expected\n");
    }
    return new GrayScaleFilter;
}

BaseFilter* MakeSharpFilter(const FilterDescriptor& fd) {
    if (fd.filter_name != "sharp") {
        throw std::invalid_argument("wrong sharp filter descriptor\n");
    }
    if (!fd.filter_params.empty()) {
        throw std::invalid_argument("wrong sharp filter arguments, no arguments expected\n");
    }
    return new SharpFilter;
}

BaseFilter* MakeBlurFilter(const FilterDescriptor& fd) {
    if (fd.filter_name != "blur") {
        throw std::invalid_argument("wrong blur filter descriptor\n");
    }
    if (fd.filter_params.size() != 1) {
        throw std::invalid_argument("wrong blur filter arguments, one integer expected\n");
    }
    try {
        return new BlurFilter(SVtoInt(fd.filter_params[0]));
    }
    catch (std::exception& e) {
        throw std::invalid_argument("wrong blur filter argument type, integer expected\n");
    }
}

BaseFilter* MakeEdgeDetectionFilter(const FilterDescriptor& fd) {
    if (fd.filter_name != "edge") {
        throw std::invalid_argument("wrong edge filter descriptor\n");
    }
    if (fd.filter_params.size() != 1) {
        throw std::invalid_argument("wrong edge filter arguments, one integer [0, 255] expected\n");
    }
    try {
        return new EdgeDetectionFilter(SVtoInt(fd.filter_params[0]));
    }
    catch (std::exception& e) {
        throw std::invalid_argument("wrong edge filter argument type, integer [0, 255] expected\n");
    }
}

BaseFilter* MakeCropFilter(const FilterDescriptor& fd) {
    if (fd.filter_name != "crop") {
        throw std::invalid_argument("wrong crop filter descriptor\n");
    }
    if (fd.filter_params.size() != 2) {
        throw std::invalid_argument("wrong crop filter arguments, two integers expected\n");
    }
    try {
        int width = SVtoInt(fd.filter_params[0]);
        int height = SVtoInt(fd.filter_params[1]);

        return new CropFilter(width, height);
    }
    catch (std::exception& e) {
        throw std::invalid_argument("wrong crop filter argument type, integers expected\n");
    }
}
}

void FilterPipelineFactory::AddFilterMaker(std::string_view name, FilterMaker maker) {
    names_to_makers_.insert({name, maker});
}
FilterPipelineFactory::FilterMaker FilterPipelineFactory::GetFilterMaker(std::string_view name) const {
    NameToMakerMap::const_iterator it = names_to_makers_.find(name);
    if (it != names_to_makers_.end()) {
        return it->second;
    }
    return nullptr;
}

BaseFilter* FilterPipelineFactory::CreateFilter(const FilterDescriptor& descriptor) const {
    FilterMaker gear = GetFilterMaker(descriptor.filter_name);
    if (!gear) {
        return nullptr;
    }
    BaseFilter* filter = gear(descriptor);
    return filter;
}
FilterPipeline FilterPipelineFactory::CreateFilterPipeline(const CmdLineParser& parser) const {
    FilterPipeline fp;
    for (const FilterDescriptor& fd : parser.GetFilterDescriptors()) {
        fp.AddFilter(CreateFilter(fd));
        if (!fp.GetFilters().back()) {
            throw std::invalid_argument("unrecognised filter_name\n");
        }
    }
    return fp;
}

