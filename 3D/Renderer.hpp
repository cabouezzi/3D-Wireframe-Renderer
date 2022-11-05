//
//  Renderer.hpp
//  3D
//
//  Created by Chaniel Ezzi on 10/31/22.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "SDL2/SDL.h"
#include "Scene.hpp"
#include "Matrix3.hpp"
#include "Node.hpp"

class Renderer {
    
private:
    
    int width, height;
    
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event event;
    
    bool quit = false;
    bool pressed = false;
    bool dragging = false;
    
    SDL_Point mouseStateCache = {0,0};
    
    void draw (Node *node);
    
public:
    
    Renderer(int w, int h);
    ~Renderer();
    
    void draw (Scene* scene);
    
};

#endif /* Renderer_hpp */
