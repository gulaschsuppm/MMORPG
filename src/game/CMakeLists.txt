cmake_minimum_required(VERSION 3.10)

add_library(GameEngine
            "GameEngine.cpp"
            "Ball.cpp"
            "Player.cpp"
             "Square.cpp")

target_include_directories(GameEngine PUBLIC
                          "${PROJECT_SOURCE_DIR}/src/game"
                          "${PROJECT_SOURCE_DIR}/src/lib/physics"
                          "${PROJECT_SOURCE_DIR}/src/lib/visual"
                          )

target_link_libraries(GameEngine PUBLIC
                      OLC
                      Visuals
                      PhysicsEngine)

add_executable(Game
               "main.cpp"
               )

target_link_libraries(Game
                      GameEngine)