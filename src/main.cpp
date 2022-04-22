#include <vector>

#include <memory.h>
#include <sstream>

//#include "./include/graphics_utils.h"
//#include "./include/math_utils.h"
//#include "./include/imagebuffer.h"
//#include "./include/map.h"
//#include "./include/camera.h"
//#include "./include/raycaster.h"

#include "raycasting.h"

int main(){


    const size_t width(512), height(512);
    const size_t sector_count = 16;


    ImageBuffer cast_buffer(width, height, pack_color(255,255,255));
    cast_buffer.clear();

    Map map(width, height, sector_count);

    map.load_from("Map.mpb");

    Camera camera(90, 90, 0.5+deg_to_rad(48), deg_to_rad(90)); //broke angle

    Raycaster reycaster(&map, &camera, width);

    std::vector<float> distances = reycaster.raycast();

    reycaster.draw_raycast(cast_buffer, distances);
    for (int i=0; i< 90; i++){
        std::ostringstream  oss;
        cast_buffer.clear();

        oss << i;
        camera.angle += deg_to_rad(4);
//        camera.x+= 2;
        auto dist = reycaster.raycast();

        reycaster.draw_raycast(cast_buffer, dist);

        cast_buffer.drop_to_ppm("./renders/cast" + oss.str() + ".ppm");
    }

    cast_buffer.drop_to_ppm("./renders/broke_angle_cast.ppm");


    return 0;
}
