cmake_minimum_required(VERSION 3.10)

add_library(PhysicsEngine
            "PhysicsEngine.cpp"
            "Utils.hpp"
            "Body.cpp"
            "Manifold.cpp"
            "Collision.cpp"
            )

target_include_directories(PhysicsEngine PUBLIC
                           "${PROJECT_SOURCE_DIR}/src/lib/physics"
                           "${PROJECT_SOURCE_DIR}/src/lib/olcPixelGameEngine")
