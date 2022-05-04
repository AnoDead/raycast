cmake_minimum_required(VERSION 3.22)
project(RayCaster)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O3)


include_directories(src)
include_directories(src/raycast)

find_package(SDL2 REQUIRED)

include_directories(${SDL_INCLUDE_DIR})


add_executable(
        ${PROJECT_NAME}
        src/main.cpp 
        src/raycast/map.h
        src/raycast/math_utils.h
        src/raycast/camera.h
        src/raycast/raycaster.h
        src/raycast/raycasting.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
