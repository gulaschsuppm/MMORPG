cmake_minimum_required(VERSION 3.10)

add_subdirectory(visual)
add_subdirectory(physics)

add_library(OLC
            "visual/olcPixelGameEngine.cpp")

target_include_directories(OLC PUBLIC
                           "${PROJECT_SOURCE_DIR}/src/lib/olcPixelGameEngine")

#target_compile_definitions(OLC PUBLIC
#    -DOLC_IGNORE_VEC2D)