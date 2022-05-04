#pragma once

#include <cinttypes>
#include <vector>
#include <functional>
#include <random>
#include <fstream>
#include <iostream>
#include <cassert>

using grid_pos_t = size_t; //cell position in grid by row column

struct _Map_header{
    size_t width = 0;
    size_t height = 0;
    size_t subdiv = 0;
};



class Map{
public:

    Map();
    Map(size_t w, size_t h, size_t subdiv);

    bool load(const std::string& filename);
    void save_on_disk(const std::string& filename) const;

    size_t size() const;
    bool empty() const;

    grid_pos_t mapping_column(size_t x) const;
    grid_pos_t mapping_row(size_t y) const;

    bool get_cell(size_t x, size_t y) const;
    void set_cell(size_t x, size_t y, bool cell);

    bool get_cell_by_grid(grid_pos_t column, grid_pos_t row) const;

public:

    std::vector<bool> map_data;
    size_t width;
    size_t height;
    size_t subdivision;

    float cell_width;
    float cell_height;
};




Map::Map():width(0), height(0), subdivision(0), cell_width(0), cell_height(0), map_data(){}


Map::Map(size_t w, size_t h, size_t subdiv):
    map_data(subdiv*subdiv, false),
    width(w), height(h),
    subdivision(subdiv)
    {
        cell_width = width / subdivision;
        cell_height = height / subdivision;
    }



bool Map::load(const std::string& filename){
    std::fstream input_file;
    input_file.open(filename, std::ios::binary|std::ios::in);
    if (!input_file.is_open()){
        std::cerr << "Error: can't open (" << filename << ")" << std::endl;
        return false;
    }
    _Map_header header;
    input_file.read((char*)&header, sizeof(header));
    width = header.width;
    height = header.height;
    subdivision = header.subdiv;
    cell_width = width / subdivision;
    cell_height = height / subdivision;
    map_data.clear();
    map_data.reserve(subdivision*subdivision);
    for (size_t i=0; i < subdivision*subdivision; i++){
        char t = 0;
        input_file.read((char*)&t, sizeof(t));
        map_data.push_back(bool(t));

    }
    return true;
}


void Map::save_on_disk(const std::string& filename) const{
    _Map_header header{width, height, subdivision};
    std::fstream file;
    file.open(filename, std::ios::out|std::ios::binary);
    file.write((char*)&header, sizeof(header));

    for (int i=0; i< subdivision*subdivision; i++){
        char t = map_data[i];
        file.write(&t, sizeof(t));
    }
}



bool Map::get_cell(size_t x , size_t y) const{
    if (!(x < width && y < height)){
        return true;
    }

    grid_pos_t column = mapping_column(x);
    grid_pos_t row = mapping_row(y);
    return map_data[column + row * subdivision];
}


void Map::set_cell(size_t x, size_t y, bool cell){
    assert(x < width && y < height);
    size_t cx = x / cell_width;
    size_t cy = y / cell_height;
    map_data[cx + cy * subdivision] = cell;
}


grid_pos_t Map::mapping_column(size_t x) const{
    return x / cell_width;
}


grid_pos_t Map::mapping_row(size_t y) const{
    return y / cell_width;
}


bool Map::get_cell_by_grid(grid_pos_t column, grid_pos_t row) const{
    if ((row < subdivision && column < subdivision)){
        return true;
    }
    return map_data[column + row * subdivision];
}


size_t Map::size() const{
    return subdivision*subdivision;
}


bool Map::empty() const{
    return map_data.empty();
}