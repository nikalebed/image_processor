cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        cmd_line_parser.cpp
        cmd_line_parser.h
        filter_pipeline_factory.cpp
        filter_pipeline_factory.h
        base_filter.cpp
        base_filter.h
        negative_filter.cpp
        negative_filter.h
        bitmap.cpp
        bitmap.h
        gs_filter.cpp
        gs_filter.h
        matrix_filter.cpp
        matrix_filter.h
        color.cpp
        color.h
        filter_pipeline.cpp
        filter_pipeline.h
        sharp_filter.h
        edge_detection_filter.cpp
        edge_detection_filter.h
        crop_filter.cpp
        crop_filter.h
        application.cpp
        application.h
        blur_filter.cpp
        blur_filter.h)

add_catch(test_image_processor
        tests.cpp
        cmd_line_parser.cpp
        cmd_line_parser.h
        filter_pipeline_factory.cpp
        filter_pipeline_factory.h
        base_filter.cpp
        base_filter.h
        negative_filter.cpp
        negative_filter.h
        bitmap.cpp
        bitmap.h
        gs_filter.cpp
        gs_filter.h
        matrix_filter.cpp
        matrix_filter.h
        color.cpp
        color.h
        filter_pipeline.cpp
        filter_pipeline.h
        sharp_filter.h
        edge_detection_filter.cpp
        edge_detection_filter.h
        crop_filter.cpp
        crop_filter.h
        application.cpp
        application.h
        blur_filter.cpp
        blur_filter.h)