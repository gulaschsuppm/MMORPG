cmake_minimum_required(VERSION 3.10)

add_library(OLC
            "olcPixelGameEngine/olcPixelGameEngine.cpp")

target_include_directories(OLC PUBLIC
                           "${PROJECT_SOURCE_DIR}/src/lib/olcPixelGameEngine")
