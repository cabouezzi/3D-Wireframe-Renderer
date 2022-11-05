//
//  Geometry.hpp
//  3D
//
//  Created by Chaniel Ezzi on 11/2/22.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include <vector>
#include "Vector3.hpp"

struct Geometry {
    
public:
    std::vector<Vector3> vertices;
    std::vector<int> edges;
    std::vector<int> faces;
    
    Geometry () : vertices({}), edges({}), faces({}) {}
    Geometry (Vector3 *vertices, int vsize, int* edges, int esize, int* faces, int fsize) {
        for (int i = 0; i < vsize; i++)
            this->vertices.push_back(vertices[i]);
        
        for (int j = 0; j < esize; j++)
            this->edges.push_back(edges[j]);
        
        for (int k = 0; k < fsize; k++)
            this->faces.push_back(faces[k]);
    }
};

#endif /* Geometry_hpp */
