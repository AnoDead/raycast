#pragma once

#include "imagebuffer.h"

class Camera
{
public:
    float x, y;
    float angle;
    float fov;

    Camera(float x, float y, float a, float pov): x(x), y(y), angle(a), fov(pov)
    {
    }

    void draw(ImageBuffer& buffer) const;
};


void Camera::draw(ImageBuffer& buffer) const
{
    buffer.draw_rect(x, y, 10, 10, COLOR::RED);

//    for (float step=0; step<20; step+=0.5){
//
//        size_t cx = x + step*cos(angle);
//        size_t cy = y + step*sin(angle);
//        buffer.set_pixel(cx, cy, GREEN);
//    }
}
