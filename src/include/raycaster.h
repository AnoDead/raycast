#pragma once 

#include <cmath>
#include <vector>

#include "map.h"
#include "imagebuffer.h"
#include "graphics_utils.h"

#include "camera.h"


  /**
   *  @brief Raycaster class.
   *
   *
   *  @tparam map  Map object.
   *  @tparam fov viewport angle in radians.
   *  @tparam ray count
  */

class Raycaster
{
    const Map* map;
    const Camera* camera;
    size_t ray_count;

public:
    Raycaster(const Map* map, const Camera* camera, size_t ray_count):
        map(map), camera(camera), ray_count(ray_count){}


    float ray(size_t x, size_t y, float angle, float dt){

        float cos_a = cos(angle);
        float sin_a = sin(angle);
        float length = 0;                  //Ray length

        while(true){
            
            float cx = x + length * cos_a;
            float cy = y + length * sin_a;

            if (map->get_section(cx, cy)){
                break;
            }
            std::cout << length << std::endl;
            length += dt;
        }

        return length * cos_a;
    }
    std::vector<float> raycast(){
        return raycast(camera->x, camera->y, camera->angle);
    }

    std::vector<float> raycast(size_t x, size_t y, float angle){
        float fov = camera->fov;
        float half_fov = fov / 2;
        float dt = fov / ray_count;

        std::vector<float> distances;

        for (float ang =  -half_fov; ang<fov; ang += dt){


            float distance = ray(x, y, angle + ang, 0.05);
//            std::cout << "Ray:" << "(" << angle << ")" << "  -  ang (" << ang << ") - " << distance << std::endl;

            distances.push_back(distance);
        }
        return std::move(distances);
    }

    void draw_raycast(ImageBuffer& buffer, std::vector<float> dist){


        buffer.draw_rect(0, buffer.height / 2, buffer.width, buffer.height / 2, pack_color(100,100,100));

        for ( size_t i=0; i<dist.size(); i++){

            float d = dist[i];

            d = (buffer.height * buffer.height) / (d * d); 

            buffer.draw_rect(i, (buffer.height/2)-d/2, 1, d, pack_color(0, 0, 255) );
        }
    }

};
