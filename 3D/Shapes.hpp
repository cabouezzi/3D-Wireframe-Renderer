//
//  Shapes.hpp
//  3D
//
//  Created by Chaniel Ezzi on 11/4/22.
//

#ifndef Shapes_hpp
#define Shapes_hpp

#include <stdio.h>
#include "Geometry.hpp"

namespace Shapes {

static Geometry Cube (int rad) {
    
    Vector3 vertices[8] = {
        Vector3(-rad, rad, rad),
        Vector3(rad, rad, rad),
        Vector3(rad, -rad, rad),
        Vector3(-rad, -rad, rad),
        
        Vector3(-rad, rad, -rad),
        Vector3(rad, rad, -rad),
        Vector3(rad, -rad, -rad),
        Vector3(-rad, -rad, -rad),
    };
    
    int faces[36] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        0, 4, 7,
        7, 3, 0,

        1, 5, 6,
        6, 2, 1,
        
        0, 1, 4,
        4, 5, 1,
        
        3, 7, 2,
        7, 2, 6
    };
    
    return Geometry(vertices, 8, {}, 0, faces, 36);
};

}

#endif /* Shapes_hpp */
