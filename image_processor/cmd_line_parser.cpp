#include "cmd_line_parser.h"

ParseStatus CmdLineParser::Parse(int argc, char* argv[]) {
    if (argc < MIN_PARAM_NUM) {
        return ParseStatus::NOT_ENOUGH_PARAMS;
    }
    input_file_name_ = argv[INPUT_FILE_NAME_POS];
    output_file_name_ = argv[OUTPUT_FILE_NAME_POS];

    for (int i = MIN_PARAM_NUM; i < argc; ++i) {
        std::string_view param = argv[i];
        if (param[0] == FILTER_NAME_INDICATOR) {
            param.remove_prefix(1);
            filter_descriptors_.push_back({param, {}});
        } else {
            if (filter_descriptors_.empty()) {
                return ParseStatus::WRONG_PARAMS;
            }
            filter_descriptors_.back().filter_params.push_back(param);
        }
    }
    return ParseStatus::PARSED;
}