#pragma once

#include <cmath>

inline float to_degress(float rad){
    return (float)((rad * 180) / M_PI);
}

inline float to_radians(float deg){
    return (float)((deg * M_PI) / 180);
}