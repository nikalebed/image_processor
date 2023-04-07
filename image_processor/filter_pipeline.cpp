#include "filter_pipeline.h"

void FilterPipeline::Apply(Bitmap& bmp) {
    for (std::shared_ptr<BaseFilter> filter : filters_) {
        filter->Apply(bmp);
    }
}
void FilterPipeline::AddFilter(BaseFilter* filter) {
    filters_.push_back(std::shared_ptr<BaseFilter>(filter));
}


