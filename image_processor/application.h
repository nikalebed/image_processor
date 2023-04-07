#pragma once
#include "filter_pipeline_factory.h"
#include "cmd_line_parser.h"

class Application {
public:
    constexpr static const std::string_view
        NOT_ENOUGH_PARAMS_WARNING = "not enough params given, at least 2 required\n";
    constexpr static const std::string_view
        WRONG_PARAMS_WARNING = "required arguments format: {program name} input_file_name output_file_name"
                               " -filter_name1 param1 parm2..."
                               " -filter_name2 param1 parm2 ...\n";
    constexpr static const std::string_view LOADING_FILE_WARNING_BEG = "failed to load file \"";
    constexpr static const std::string_view LOADING_FILE_WARNING_END = "\", bmp file with 24 pits per pixel expected";
    constexpr static const std::string_view WRITING_FILE_WARNING_BEG = "unable to write to file \"";
    constexpr static const std::string_view WRITING_FILE_WARNING_END = "\"";

public:
    Application();
    void Run(int argc, char* argv[]);
protected:
    FilterPipelineFactory fpf_;
    FilterPipeline fp_;
    Bitmap bmp_;
    CmdLineParser parser_;
protected:
    bool Parse(int argc, char* argv[]);
    bool LoadBMP();
    void WriteBMP();
};
