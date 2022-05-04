#include "raycast/raycasting.h"


#include <SDL2/SDL.h>

class App{
public:

    App(size_t width, size_t height, std::string title)
    :width(width), height(height),
     title(title), map(),
      camera(250, 200, 0, to_radians(80)),
      cast(&map, &camera, 512){
        
    }
    ~App(){
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }

    bool Init(){
        if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == -1){
            return false;
        }
        SDL_SetWindowTitle(window, title.c_str());

        return loadMap();
    }

    bool loadMap(){
        if(map.load("map.mpb")){
            width = map.width;
            height = map.height;

            floor_rect.x = 0;
            floor_rect.y = height/2;
            floor_rect.w = width;
            floor_rect.h = height/2;
            //minimap
            minimap_rect = {0, 0, 150, 150};
            minimap_cell = {0, 0, minimap_rect.w / map.subdivision, minimap_rect.h / map.subdivision};
            minimap_player = {0, 0, 5, 5};

            close = false;
            return true;
        }
        return false;
    }

    void rename_title(std::string& t){
        SDL_SetWindowTitle(window, t.c_str());
        title = t ;
    }

    void event_handle(){
        SDL_PollEvent(&event);

        const uint8_t* keystate = SDL_GetKeyboardState(NULL);

        if(keystate[SDL_SCANCODE_X]){
            close = true;
        }
        if (keystate[SDL_SCANCODE_S]){
            auto cx = cos(camera.angle) * 0.1;
            auto cy = sin(camera.angle) * 0.1;
            camera.move(-cx, -cy);
        }
        if (keystate[SDL_SCANCODE_W]){
            auto cx = cos(camera.angle) * 0.1;
            auto cy = sin(camera.angle) * 0.1;
            camera.move(cx, cy);
        }
        if (keystate[SDL_SCANCODE_D]){
            camera.rotate(to_radians(0.2));
        }
        if (keystate[SDL_SCANCODE_A]){
            camera.rotate(to_radians(-0.2));
        }
        if (keystate[SDL_SCANCODE_E]){
            auto cx = cos(camera.angle +to_radians(90)) * 0.2;
            auto cy = sin(camera.angle +to_radians(90)) * 0.2;
            camera.move(cx, cy);
        }        
        if (keystate[SDL_SCANCODE_Q]){
            auto cx = cos(camera.angle -to_radians(90)) * 0.2;
            auto cy = sin(camera.angle -to_radians(90)) * 0.2;
            camera.move(cx, cy);
        }
        if(keystate[SDL_SCANCODE_M]){
                minimap = !minimap;
        }
        switch (event.type)
        {
        case SDL_QUIT:
            close = true;
            break;
        default:
            break;
        }
    }

    void update(){
        event_handle();
        cast.cast_dda();
    }

    void draw_map(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
        SDL_RenderFillRectF(renderer, &minimap_rect);
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        for (int y=0; y<map.subdivision; y++)
            for (int x=0; x<map.subdivision; x++){
                if (map.map_data[x + y * map.subdivision]){
                    minimap_cell.x = x * minimap_cell.w;
                    minimap_cell.y = y * minimap_cell.h;
                    SDL_RenderFillRectF(renderer, &minimap_cell);
                }
            }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        auto tx = (camera.x / width) * minimap_rect.w;
        auto ty = (camera.y / height) * minimap_rect.h;
        minimap_player.x = tx - minimap_player.w / 2 ;
        minimap_player.y = ty - minimap_player.h / 2;
        SDL_RenderFillRectF(renderer, &minimap_player);
        
        SDL_RenderDrawLineF(renderer, tx, ty, tx + cos(camera.angle) * 15, ty + sin(camera.angle) * 15);
    }

    void draw(){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White clear
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 10,10,10, 255);//Draw floor
        SDL_RenderFillRectF(renderer, &floor_rect);

        SDL_SetRenderDrawColor(renderer, 0, 200, 55, 255);
        int i (0);
        for (auto& dist :cast.distances){
            auto l = ((height*height) / (dist*dist)) / 2;

            SDL_RenderDrawLineF(renderer, i, (height/2) + l, i, (height/2) - l);
            i++;
        }
        if(minimap)
             draw_map();

        SDL_RenderPresent(renderer);
    }

    void run(){

        while(!close){
            update();
            draw();
            SDL_Delay(1);

        }
    }

private:
    Map map;
    Camera camera;
    Raycast cast;

    bool minimap = false;

    bool close = true;
    SDL_Event event;
    size_t width;
    size_t height;
    std::string title;

private:
    SDL_FRect minimap_player;
    SDL_FRect minimap_cell;
    SDL_FRect minimap_rect;
    SDL_FRect cell;
    SDL_FRect floor_rect;

    SDL_Window* window = nullptr;
    SDL_Renderer * renderer = nullptr;    
};





int main(){
    App app(512, 512, "SDL Raycast 2.5D");
    if (app.Init())
        app.run();
    return 0;
}