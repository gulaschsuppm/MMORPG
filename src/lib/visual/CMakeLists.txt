cmake_minimum_required(VERSION 3.10)

add_library(Visuals
            "olcPixelGameEngine.cpp"
            "Renderer.cpp"
            )

target_include_directories(Visuals PUBLIC
                           "${PROJECT_SOURCE_DIR}/src/lib/olcPixelGameEngine"
                           "${PROJECT_SOURCE_DIR}/src/lib/visual"
                           "${PROJECT_SOURCE_DIR}/src/lib/physics")
