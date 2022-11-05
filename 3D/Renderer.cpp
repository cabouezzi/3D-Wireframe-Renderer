//
//  Renderer.cpp
//  3D
//
//  Created by Chaniel Ezzi on 10/31/22.
//

#include "Renderer.hpp"
#include <iostream>

static Vector3 project (Vector3 point, float distance) {
    float fov = distance + point.z;
    float x = point.x / pow(fov,1);
    float y = point.y / pow(fov,1);
    return Vector3(x, y, point.z);
}

Renderer::Renderer (int w, int h) {
    this->width = w;
    this->height = h;
    
    SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &window, &renderer);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::draw(Node *node) {
    
    std::vector<Vector3> vertices = node->geometry.vertices;
    std::vector<int> edges = node->geometry.edges;
    std::vector<int> faces = node->geometry.faces;
    
    // Need 3 vertices for a face
    int nf = floor(faces.size() / 3);
    
    for (int i = 0; i < nf; i++) {
        
        Vector3 one = vertices[faces[i * 3]];
        Vector3 two = vertices[faces[i * 3 + 1]];
        Vector3 three = vertices[faces[i * 3 + 2]];
        
        one = rotatedVector(one, node->worldRotation()) + node->worldPosition();
        two = rotatedVector(two, node->worldRotation()) + node->worldPosition();
        three = rotatedVector(three, node->worldRotation()) + node->worldPosition();
        
        one = one * 350;
        two = two * 350;
        three = three * 350;
        
        SDL_RenderDrawLine(renderer,
                           one.x + width / 2,
                           -one.y + height / 2,
                           two.x + width / 2,
                           -two.y + height / 2);
        SDL_RenderDrawLine(renderer,
                           one.x + width / 2,
                           -one.y + height / 2,
                           three.x + width / 2,
                           -three.y + height / 2);
        SDL_RenderDrawLine(renderer,
                           three.x + width / 2,
                           -three.y + height / 2,
                           two.x + width / 2,
                           -two.y + height / 2);
    }
    
    // Recursively draw children
    for (Node *child : node->getChildren()) draw(child);
    
}

void Renderer::draw(Scene* scene) {
    
    while (!quit) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
        
        // draw
        draw(scene->getRoot());
//        scene->getRoot()->rotation.x += M_PI_4 / 100;
//        scene->getRoot()->rotation.y += M_PI_4 / 100;
        
        SDL_RenderPresent(renderer);
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_KEYDOWN: {
                    quit = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    pressed = true;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    if (pressed) {
                        SDL_Point mouseState;
                        SDL_GetMouseState(&mouseState.x, &mouseState.y);
                        
                        // Dragging started, reset cache
                        if (!dragging) mouseStateCache = mouseState;
                        
                        // Change in (x, y) each frame
                        float dx = static_cast<float>(mouseState.x - mouseStateCache.x) / 100;
                        float dy = static_cast<float>(mouseState.y - mouseStateCache.y) / 100;
                        
                        // call drag handler
                        scene->getRoot()->rotation.y += dx;
                        scene->getRoot()->rotation.x += dy;
                        
                        // Save last state in cache
                        mouseStateCache.x = mouseState.x;
                        mouseStateCache.y = mouseState.y;
                        dragging = true;
                        
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    if (!dragging) {
                        // call click handler
                    }
                    
                    pressed = false;
                    dragging = false;
                    break;
                }
            }
        }
        
        
    }
    
}
