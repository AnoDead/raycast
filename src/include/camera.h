#pragma once

class Camera
{
public:
    float x, y;
    float angle;
    float fov;

    Camera(float x, float y, float a, float pov): x(x), y(y), angle(a), fov(pov)
    {
    }

    float rotate(float a);

    void move(float tx, float ty);


};

float Camera::rotate(float a) {
    return angle = (angle + a);
}

void Camera::move(float tx, float ty) {
    x += tx;
    y += ty;
}


//void Camera::draw(ImageBuffer& buffer) const
//{
//    buffer.draw_rect(x, y, 10, 10, COLOR::RED);
//
////    for (float step=0; step<20; step+=0.5){
////
////        size_t cx = x + step*cos(angle);
////        size_t cy = y + step*sin(angle);
////        buffer.set_pixel(cx, cy, GREEN);
////    }
//}
