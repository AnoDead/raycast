#pragma once

#include <utility>
#include <vector>
#include <cinttypes>
#include <cassert>
#include <memory.h>
#include "graphics_utils.h"


//class RawImageData{
//private:
//    uint32_t* buffer = nullptr;
//    size_t width{};
//    size_t height{};
//public:
//    RawImageData(size_t w, size_t h):width(w), height(h){
//        buffer = new uint32_t[w*h];
//    }
//
////    Copy Constructor
////    RawImageData(RawImageData& copy){
////        delete [] buffer;
////        RawImageData(copy.width, copy.height);
////        memcpy((void*)&buffer, (void*)&copy.buffer, sizeof(uint32_t)*width*height);
////    }
//
//    RawImageData(RawImageData&& rvalue) noexcept :buffer(rvalue.buffer), width(rvalue.width), height(rvalue.height){
//        rvalue.buffer = nullptr;
//
//    }
//
//    ~RawImageData(){
//        delete [] buffer;
//    }
//
//    uint32_t& operator[] (const size_t index){
//        return buffer[index];
//    }
//};

class ImageBuffer
{
    std::vector<uint32_t> buffer;
public:
    const size_t width;
    const size_t height;
    uint32_t fill_color;

    ImageBuffer(size_t w, size_t h, uint32_t fillcolor=pack_color(255, 255, 255));

    bool is_inside(size_t x,size_t y) const;

    uint32_t get_pixel(size_t x, size_t y);
    void set_pixel(size_t x, size_t y, uint32_t color);
    void clear();
    void draw_rect(size_t x, size_t y, size_t w, size_t h, uint32_t color);

    void drop_to_ppm(std::string filename);
};

ImageBuffer::ImageBuffer(size_t w, size_t h, uint32_t fillcolor):
    buffer(w*h, 0), width(w), height(h), fill_color(fillcolor)
{
}


bool ImageBuffer::is_inside(size_t x,size_t y) const
{
    return (x >= 0 && x < width) && (y >= 0 && y < height);
}


uint32_t ImageBuffer::get_pixel(size_t x, size_t y)
{
    assert(is_inside(x, y));
    return buffer[x + y * width];
}

void ImageBuffer::set_pixel(size_t x, size_t y, uint32_t color)
{
    assert(is_inside(x, y));
    buffer[x + y * width] = color;
}


void ImageBuffer::clear()
{
    for (unsigned int & i : buffer)
        i = fill_color;
}

void ImageBuffer::draw_rect(size_t x, size_t y, size_t w, size_t h, uint32_t color)
{
    draw_rectangle(buffer, width, height, x, y, w, h, color);
}


void ImageBuffer::drop_to_ppm(std::string filename)
{
    drop_ppm_image(std::move(filename), buffer, width, height);
}
