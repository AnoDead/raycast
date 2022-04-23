#include <vector>

#include <memory.h>
#include <sstream>

#include "raycast/graphics/imagebuffer.h"
#include "raycast/graphics/graphics_utils.h"

#include "raycast/raycasting.h"
#include "raycast/render.h"

#include "raycast/timer.h"

int main(){


    const size_t width(512), height(512);
    const size_t sector_count = 16;

    const int framecount = 20;

    Timer timer;

    std::vector<ImageBuffer*> buffers;
    for (int i=0; i< framecount; i++){
        buffers.push_back(new ImageBuffer(width, height, COLOR::WHITE));
    }

    Map map(width, height, sector_count);

    map.load_from("Map.mpb");

    Camera camera(200, 125, 0, deg_to_rad(80));
    if (map.get_section(camera.x, camera.y)){
        std::cout << "Camera in wall" << std::endl;
    }

    Raycast reycaster(&map, &camera, width);

    ImageBuffer map_buffer(width, height, COLOR::WHITE);
    render_map(map_buffer, map);
    map_buffer.draw_rect(camera.x - 5, camera.y-5, 10, 10, COLOR::RED);
    map_buffer.drop_to_ppm("renders/map.ppm");

    for (int i=0; i< framecount; i++){
        buffers[i]->clear();
        camera.rotate(deg_to_rad(10));

        timer.reset();
        auto dist = reycaster.cast();

       std::cout << "Time: " << to_string(timer.elapsed()) << std::endl;
        render_scene(*buffers[i], dist);
    }

    int index = 0;
    for (auto& buffer: buffers) {
        buffer->drop_to_ppm("./renders/drop" + to_string(index++) + ".ppm");
        delete buffer;
    }
    return 0;
}
