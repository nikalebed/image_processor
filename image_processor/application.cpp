#include "application.h"

Application::Application() {
    fpf_.AddFilterMaker("gs", &FilterMakers::MakeGrayscaleFilter);
    fpf_.AddFilterMaker("neg", &FilterMakers::MakeNegativeFilter);
    fpf_.AddFilterMaker("sharp", &FilterMakers::MakeSharpFilter);
    fpf_.AddFilterMaker("edge", &FilterMakers::MakeEdgeDetectionFilter);
    fpf_.AddFilterMaker("crop", &FilterMakers::MakeCropFilter);
    fpf_.AddFilterMaker("blur", &FilterMakers::MakeBlurFilter);
}

void Application::Run(int argc, char* argv[]) {
    if (!Parse(argc, argv)) {
        return;
    }
    try {
        fp_ = fpf_.CreateFilterPipeline(parser_);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what();
        return;
    }
    if (!LoadBMP()) {
        return;
    }
    fp_.Apply(bmp_);
    WriteBMP();
}

bool Application::Parse(int argc, char* argv[]) {
    ParseStatus ps = parser_.Parse(argc, argv);
    if (ps == ParseStatus::NOT_ENOUGH_PARAMS) {
        std::cerr << NOT_ENOUGH_PARAMS_WARNING;
        return false;
    }
    if (ps == ParseStatus::WRONG_PARAMS) {
        std::cerr << WRONG_PARAMS_WARNING;
        return false;
    }
    return true;
}

bool Application::LoadBMP() {
    if (Bitmap::LoadStatus::LOADED != bmp_.Load(parser_.GetInputFileName())) {
        std::cerr << LOADING_FILE_WARNING_BEG << parser_.GetInputFileName() << LOADING_FILE_WARNING_END;
        return false;
    }
    return true;
}
void Application::WriteBMP() {
    if (!bmp_.Write(parser_.GetOutputFileName())) {
        std::cerr << WRITING_FILE_WARNING_BEG << parser_.GetOutputFileName() << WRITING_FILE_WARNING_END;
    }
}