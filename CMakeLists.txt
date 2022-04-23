cmake_minimum_required(VERSION 3.18)
project(RayCaster)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/raycast)
include_directories(src/raycast/graphics)

add_executable(RayCaster
        src/raycast/graphics/graphics_utils.h
        src/raycast/graphics/imagebuffer.h
        src/raycast/map.h
        src/raycast/math_utils.h
        src/raycast/camera.h
        src/raycast/raycaster.h
        src/main.cpp src/raycast/raycasting.h)
