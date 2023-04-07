#pragma once
#include <memory>
#include "base_filter.h"

class FilterPipeline {
public:
    FilterPipeline(){};
    FilterPipeline(const std::vector<std::shared_ptr<BaseFilter>>& filters) : filters_(filters){};

public:
    void Apply(Bitmap& bmp);
    void AddFilter(BaseFilter* filter);
    std::vector<std::shared_ptr<BaseFilter>>& GetFilters() {
        return filters_;
    }
    const std::vector<std::shared_ptr<BaseFilter>>& GetFilters() const {
        return filters_;
    }

protected:
    std::vector<std::shared_ptr<BaseFilter>> filters_;
};