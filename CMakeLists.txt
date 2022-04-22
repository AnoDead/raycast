cmake_minimum_required(VERSION 3.22)
project(RayCaster)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/include)

add_executable(RayCaster
        src/include/graphics_utils.h
        src/include/imagebuffer.h
        src/include/map.h
        src/include/math_utils.h
        src/include/camera.h
        src/include/raycaster.h
        src/main.cpp src/include/raycasting.h)
