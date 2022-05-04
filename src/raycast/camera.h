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
    
    Camera():Camera(0, 0, 0, 0){}

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
