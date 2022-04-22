#pragma once

#include <cmath>

inline float rad_to_deg(float rad){
    return (float)((rad * 180) / M_PI);
}

inline float deg_to_rad(float deg){
    return (float)((deg * M_PI) / 180);
}