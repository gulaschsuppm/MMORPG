cmake_minimum_required(VERSION 3.10)

add_library(PhysicsEngine
            "PhysicsEngine.cpp" "Collider.hpp" "Circle.hpp" "RigidBody.hpp" "AABB.hpp" "Box.hpp" "IntersectionDetector.hpp" "Line.hpp" "Utils.hpp")

target_include_directories(PhysicsEngine PUBLIC
                           "${PROJECT_SOURCE_DIR}/src/lib/physics")
