cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}" "-pthread")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

find_package(SDL2ttf REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIR} src)

find_package(SDL_image REQUIRED)
include_directories(${SDL_IMAGE_INCLUDE_DIR} src)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame  ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} -lSDL_image ${SDL_IMAGE_LIBRARY})