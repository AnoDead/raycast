#pragma once 

#include <cinttypes>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a=255) {
    return (a<<24) + (b<<16) + (g<<8) + r;
}

void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
    r = (color >>  0) & 255;
    g = (color >>  8) & 255;
    b = (color >> 16) & 255;
    a = (color >> 24) & 255;
}

void drop_ppm_image(const std::string& filename, const std::vector<uint32_t> &image, const size_t w, const size_t h) {
    assert(image.size() == w*h);
    std::ofstream ofs(filename);
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for (size_t i = 0; i < h*w; ++i) {
        uint8_t r, g, b, a;
        unpack_color(image[i], r, g, b, a);
        ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
    ofs.close();
}

void draw_rectangle(std::vector<uint32_t> &img, const size_t img_w, const size_t img_h, const size_t x, const size_t y, const size_t w, const size_t h, const uint32_t color) {
    assert(img.size()==img_w*img_h);
    for (size_t i=0; i<w; i++) {
        for (size_t j=0; j<h; j++) {
            size_t cx = x+i;
            size_t cy = y+j;
            if (cx>=img_w || cy>=img_h) continue; // no need to check for negative values (unsigned variables)
            img[cx + cy*img_w] = color;
        }
    }
}

uint32_t darkenn(uint32_t color, float percent=0.9){
    uint8_t r, g, b, a;
    unpack_color(color, r, g, b, a);
    return pack_color(r*percent, g*percent, b*percent);    
}

namespace COLOR{

    struct RGBA_DATA{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    uint32_t pack(const RGBA_DATA& data){
        auto * data_pack = (uint32_t*)&data;
        return *data_pack;
    }

    RGBA_DATA unpack(const uint32_t color){
        auto* data = (RGBA_DATA*)&color;
        return *data;
    }

    RGBA_DATA rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255){
        return RGBA_DATA{r, g, b, a};
    }

    uint32_t rgba_r(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255){
        return (a<<24) + (b<<16) + (g<<8) + r;
    }


    const uint32_t WHITE = rgba_r(255, 255, 255);
    const uint32_t BLACK = rgba_r(0, 0, 0);
    const uint32_t RED   = rgba_r(255, 0, 0);
    const uint32_t GREEN = rgba_r(0, 255, 0);
    const uint32_t BLUE  = rgba_r(0, 0, 255);
}

