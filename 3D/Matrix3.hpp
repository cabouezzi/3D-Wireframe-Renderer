//
//  Matrix3.hpp
//  3D
//
//  Created by Chaniel Ezzi on 10/26/22.
//

#ifndef Matrix3_hpp
#define Matrix3_hpp

#include <stdlib.h>
#include <vector>
#include "Vector3.hpp"

struct Matrix3 {

private:
    float values[3][3];
public:
    
    Matrix3 (float x1, float x2, float x3,
            float y1, float y2, float y3,
            float z1, float z2, float z3)
    {
        values[0][0] = x1;
        values[0][1] = x2;
        values[0][2] = x3;
        
        values[1][0] = y1;
        values[1][1] = y2;
        values[1][2] = y3;
        
        values[2][0] = z1;
        values[2][1] = z2;
        values[2][2] = z3;
    }
    
    Vector3 operator * (const Vector3 v) {
        return Vector3(values[0][0]*v.x + values[0][1]*v.y + values[0][2]*v.z,
                       values[1][0]*v.x + values[1][1]*v.y + values[1][2]*v.z,
                       values[2][0]*v.x + values[2][1]*v.y + values[2][2]*v.z);
    }
    
    float* operator[](int i) {
        return values[i];
    }
    
};

static Vector3 rotatedVector (Vector3 vector, Vector3 rotation) {
    Matrix3 xtransform = Matrix3(1, 0, 0,
                                 0, cos(rotation.x), -sin(rotation.x),
                                 0, sin(rotation.x),  cos(rotation.x));
    
    Matrix3 ytransform = Matrix3( cos(rotation.y), 0, sin(rotation.y),
                                 0, 1, 0,
                                 -sin(rotation.y), 0, cos(rotation.y));
    
    Matrix3 ztransform = Matrix3(cos(rotation.z), -sin(rotation.z), 0,
                                 sin(rotation.z),  cos(rotation.z), 0,
                                                              0, 0, 1);
    Vector3 rotated = vector;
    rotated = xtransform * (rotated);
    rotated = ytransform * (rotated);
    rotated = ztransform * (rotated);
    return rotated;
}

#endif /* Matrix3_hpp */
