#pragma once 

#include <cmath>
#include <vector>

#include "map.h"

#include "camera.h"


  /**
   *  @brief Raycast class.
   *
   *
   *  @tparam map  Map object.
   *  @tparam fov viewport angle in radians.
   *  @tparam ray count
  */

class Raycast
{
    const Map* map;
    const Camera* camera;
    size_t ray_count;

public:
    Raycast(const Map* map, const Camera* camera, size_t ray_count):
        map(map), camera(camera), ray_count(ray_count){}

    /**
 *  @brief Ray function, cast one ray. Return ray length
 *
 *
 *  @tparam x  x coord start point.
 *  @tparam y   y coord start point.
 *  @tparam angle angle of ray in radians
 *  @tparam step  step of ray
*/
    float ray(size_t x, size_t y, float angle, float step=5){
        float cos_a = cos(angle);
        float sin_a = sin(angle);
        float length = 0;                  //Ray length
        bool done = false;
        while(true){
            
            float cx = x + length * cos_a;
            float cy = y + length * sin_a;

            if (map->get_section(cx, cy)){
                if (done)
                    break;
                length =- step;
                step = 0.05;
                done = true;
            }
            length += step;
        }

        return abs(length);
    }

    std::vector<float> cast(){
        float fov = camera->fov;
        float half_fov = fov / 2;
        float da = fov / ray_count;

        std::vector<float> distances;

        float angle = - -half_fov;
        for (int i = 0; i < ray_count; i++){
            float ray_angle = camera->angle + angle;
            angle += da;
            distances.push_back(ray(camera->x, camera->y, ray_angle));
        }

        return distances;
    }
};
