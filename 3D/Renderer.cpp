//
//  Renderer.cpp
//  3D
//
//  Created by Chaniel Ezzi on 10/31/22.
//

#include "Renderer.hpp"
#include <iostream>

static inline Vector3 applyTranslations (const Vector3 point, const Node *ref) {
    Vector3 p = point;
    p = scaledVector(point, ref->scale);
    p = rotatedVector(p, ref->worldRotation()) + ref->worldPosition();
    
    return p;
}

SDL_Point Renderer::project (Vector3 point) {
    
    int scale = 300;
    float fov = 3;
    float d = point.z - fov;
    float x = fov / d * point.x;
    float y = fov / d * point.y;
    
    SDL_Point p = { static_cast<int>(x*scale) + width/2, static_cast<int>(y*scale) + height/2 };
    return p;
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
    
    int scale = 350;
    
    node->position = node->position + node->velocity;
    node->rotation = node->rotation + node->angularVelocity;
    
    std::vector<Vector3> vertices = node->geometry.vertices;
    std::vector<int> edges = node->geometry.edges;
    std::vector<int> faces = node->geometry.faces;
    
    // Need 2 vertices for an edge
    int ne = floor(edges.size() / 2);
    
    for (int i = 0; i < ne; i++) {
        Vector3 start = applyTranslations(vertices[edges[i * 2]], node);
        Vector3 end = applyTranslations(vertices[edges[i * 2 + 1]], node);
        
        start = start * scale;
        end = end * scale;
        
        int mod = i % 3;
        SDL_SetRenderDrawColor(renderer, (mod == 0 ? 255 : 0), (mod == 1 ? 255 : 0), (mod == 2 ? 255 : 0), 255);
        SDL_RenderDrawLine(renderer,
                           start.x + width / 2,
                           -start.y + height / 2,
                           end.x + width / 2,
                           -end.y + height / 2);
        
    }
    
    // Need 3 vertices for a face
    int nf = floor(faces.size() / 3);
    
    for (int i = 0; i < nf; i++) {
        
        SDL_Point one = project(applyTranslations(vertices[faces[i * 3]], node));
        SDL_Point two = project(applyTranslations(vertices[faces[i * 3 + 1]], node));
        SDL_Point three = project(applyTranslations(vertices[faces[i * 3 + 2]], node));
        
        SDL_RenderDrawLine(renderer,
                           one.x, one.y,
                           two.x, two.y);
        SDL_RenderDrawLine(renderer,
                           one.x, one.y,
                           three.x, three.y);
        SDL_RenderDrawLine(renderer,
                           three.x, three.y,
                           two.x, two.y);
    }
    
    // Recursively draw children
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
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
        
        SDL_RenderPresent(renderer);
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_KEYDOWN: {
                    keyPressed = true;
                    break;
                }
                case SDL_KEYUP: {
                    keyPressed = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    mousePressed = true;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    
                    if (mousePressed) {
                        SDL_Point mouseState;
                        SDL_GetMouseState(&mouseState.x, &mouseState.y);
                        
                        // Dragging started, reset cache
                        if (!dragging) mouseStateCache = mouseState;
                        
                        // Change in (x, y) each frame
                        float dx = static_cast<float>(mouseState.x - mouseStateCache.x) / 100;
                        float dy = static_cast<float>(mouseState.y - mouseStateCache.y) / 100;
                        
                        // call drag handler
                        if (!keyPressed) {
                            scene->getRoot()->rotation.y += dx;
                            scene->getRoot()->rotation.x -= dy;
                        }
                        else {
                            scene->getRoot()->rotation.z += dx + dy;
                        }
                        
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
                    
                    mousePressed = false;
                    dragging = false;
                    break;
                }
            }
        }
        
        
    }
    
}
