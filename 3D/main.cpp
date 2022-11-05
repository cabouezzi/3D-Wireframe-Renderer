//
//  main.cpp
//  3D
//
//  Created by Chaniel Ezzi on 10/26/22.
//

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "Renderer.hpp"
#include "Shapes.hpp"
#include "Parser.hpp"

using namespace std;

Vector3 project (Vector3 point, float distance) {
    float fov = distance / point.z;
    float x = point.x * fov;
    float y = point.y * fov;
    return Vector3(x, y, point.z);
}

int main(int argc, const char * argv[]) {
    
    Renderer renderer = Renderer(1200, 800);
    Scene scene = Scene();
    
    Node cube = Node();
    cube.geometry = Parser::bunny();
    cout << endl << cube.geometry.vertices.size() << " " << cube.geometry.faces.size();
    scene.getRoot()->addChildNode(&cube);
    
    renderer.draw(&scene);
    
    return 0;
}
