#pragma once

#include <cinttypes>
#include <vector>
#include <functional>
#include <random>
#include <fstream>
#include <iostream>

#include "imagebuffer.h"
#include "graphics_utils.h"

void load_map_from(const std::string& filename, std::vector<bool> &buf){
    std::fstream input_file(filename, std::ios::binary|std::ios::in);
    if (!input_file.is_open()){
        std::cout << "Error: can't open (" << filename << ")" << std::endl;
        exit(1);
    }
    size_t width=0;
    size_t height=0;

    input_file.read((char*)&width, sizeof(width));
    input_file.read((char*)&height, sizeof(height));

    for (size_t i=0; i < width*height; i++){
        char t = 0;
        input_file.read((char*)&t, sizeof(t));
        buf[i] = bool(t);
    }
    input_file.close();
}

class Map

{
public:
    std::vector<bool> map_data;
    size_t width;
    size_t height;
    size_t subdivsion;

    float sect_width;
    float sect_height;

    Map(size_t w, size_t h, size_t subdiv):
        map_data(subdiv*subdiv, false), width(w), height(h), subdivsion(subdiv){
            sect_width = width / subdivsion;
            sect_height = height / subdivsion;
        }
    
    void load_from(const std::string& filename){
        load_map_from(filename, map_data);
    }

    void random_fill(){

        static auto get = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());

        for (auto && i : map_data){
            i = bool( get() );
        }
    }

    bool get_section(size_t x , size_t y) const{
        // assert(x < width && y < height);
        if (!(x < width && y < height)){
            return true;
        }
            
        size_t cx = x / sect_width;
        size_t cy = y / sect_height;
        return map_data[cx + cy * subdivsion];
    }
    
    void draw(ImageBuffer& buffer){
        for (size_t y=0; y<subdivsion; y++){
            for(size_t x=0; x<subdivsion; x++){

                size_t tx = x * sect_width;
                size_t ty = y * sect_height;
                uint32_t color = COLOR::WHITE;
                if (map_data[x + y * subdivsion])
                    color = COLOR::BLUE;
                buffer.draw_rect(tx, ty, sect_width, sect_height, color);
            }
        }
    }

};