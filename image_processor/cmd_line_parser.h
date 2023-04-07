#pragma once
#include <string_view>
#include <vector>

struct FilterDescriptor {
    std::string_view filter_name;
    std::vector<std::string_view> filter_params;
};
enum class ParseStatus {
    PARSED,
    NOT_ENOUGH_PARAMS,
    WRONG_PARAMS
};

class CmdLineParser {
public:
    static const int MIN_PARAM_NUM = 3;
    static const int INPUT_FILE_NAME_POS = 1;
    static const int OUTPUT_FILE_NAME_POS = 2;
    static const char FILTER_NAME_INDICATOR = '-';
public:
    ParseStatus Parse(int argc, char* argv[]);  // enum для разных случаев пользовательского ввода
    std::string_view GetInputFileName() const { return input_file_name_; }
    std::string_view GetOutputFileName() const { return output_file_name_; }
    std::vector<FilterDescriptor> GetFilterDescriptors() const { return filter_descriptors_; }
protected:
    std::vector<FilterDescriptor> filter_descriptors_;
    std::string_view input_file_name_;
    std::string_view output_file_name_;
};
