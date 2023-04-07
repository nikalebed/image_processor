#pragma once

#include <map>
#include <vector>

#include "cmd_line_parser.h"
#include "filter_pipeline.h"
#include "base_filter.h"

namespace FilterMakers {
// Тут мы хардкодим список фильтров, доступных нашей программе.
BaseFilter* MakeNegativeFilter(const FilterDescriptor& fd);
BaseFilter* MakeGrayscaleFilter(const FilterDescriptor& fd);
BaseFilter* MakeSharpFilter(const FilterDescriptor& fd);
BaseFilter* MakeEdgeDetectionFilter(const FilterDescriptor& fd);
BaseFilter* MakeCropFilter(const FilterDescriptor& fd);
BaseFilter* MakeBlurFilter(const FilterDescriptor& fd);
}

class FilterPipelineFactory {
public:
    using FilterMaker = BaseFilter* (*)(const FilterDescriptor&);
    using NameToMakerMap = std::map<std::string_view, FilterMaker>;
protected:
    NameToMakerMap names_to_makers_;
    std::vector<BaseFilter*> created_filters_;
public:
    FilterPipeline CreateFilterPipeline(const CmdLineParser& parser) const;

    void AddFilterMaker(std::string_view name, FilterMaker maker);

    FilterMaker GetFilterMaker(std::string_view name) const;

    BaseFilter* CreateFilter(const FilterDescriptor& descriptor) const;

};


