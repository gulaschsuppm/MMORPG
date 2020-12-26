cmake_minimum_required(VERSION 3.10)

add_library(GameEngine
            "GameEngine.cpp"
            "Ball.cpp"
            )

target_include_directories(GameEngine PUBLIC
                          "${PROJECT_SOURCE_DIR}/src/game"
                          )

target_link_libraries(GameEngine PUBLIC
                      OLC)

add_executable(Game
               "main.cpp"
               )

target_link_libraries(Game
                      GameEngine)