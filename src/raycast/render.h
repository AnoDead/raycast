//
// Created by kadzikage on 22.04.22.
//

#ifndef RAYCASTER_RENDER_H
#define RAYCASTER_RENDER_H

#include "graphics/imagebuffer.h"
#include "graphics/graphics_utils.h"

void render_scene(ImageBuffer& buffer, std::vector<float> dist){


    buffer.draw_rect(0, buffer.height / 2, buffer.width, buffer.height / 2, pack_color(100,100,100));

    for ( size_t i=0; i<dist.size(); i++){
        float d = dist[i];
        float rvd = (buffer.height * buffer.height) / (d * d);

        rvd = min((float)buffer.height, rvd);
        uint8_t g = (int)rvd % 255 ; 

       buffer.draw_rect(i, (buffer.height/2)-rvd/2, 1, rvd, pack_color(g/3, g, g/3) );
    }
}

void render_map(ImageBuffer& buffer, Map& map){
    for (size_t y=0; y<map.subdivsion; y++){
        for(size_t x=0; x<map.subdivsion; x++){

            size_t tx = x * map.sect_width;
            size_t ty = y * map.sect_height;
            uint32_t color = COLOR::WHITE;
            if (map.map_data[x + y * map.subdivsion])
                color = COLOR::BLUE;
            buffer.draw_rect(tx, ty, map.sect_width, map.sect_height, color);
        }
    }
}

#endif //RAYCASTER_RENDER_H
