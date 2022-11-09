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
    
    Matrix3 operator * (Matrix3 m) {
        
        Vector3 m1 = Vector3(m[0][0], m[1][0], m[2][0]);
        Vector3 m2 = Vector3(m[0][1], m[1][1], m[2][1]);
        Vector3 m3 = Vector3(m[0][2], m[1][2], m[2][2]);
        
        Vector3 a1 = *this * m1;
        Vector3 a2 = *this * m2;
        Vector3 a3 = *this * m3;
        
        return Matrix3(a1.x, a2.x, a3.x,
                       a1.y, a2.y, a3.y,
                       a1.z, a2.z, a3.z);
    }
    
    float* operator[](int i) {
        return values[i];
    }
    
};

static inline Vector3 scaledVector (const Vector3 vector, const Vector3 scale) {
    
    Matrix3 scaleMatrix = Matrix3(scale.x, 0, 0,
                                  0, scale.y, 0,
                                  0, 0, scale.z);
    return scaleMatrix * vector;
    
}

static inline Vector3 rotatedVector (const Vector3 vector, const Vector3 rotation) {
    
    Matrix3 xtransform = Matrix3(1, 0, 0,
                                 0, cos(rotation.x), -sin(rotation.x),
                                 0, sin(rotation.x),  cos(rotation.x));
    
    Matrix3 ytransform = Matrix3( cos(rotation.y), 0, -sin(rotation.y),
                                 0, 1, 0,
                                 sin(rotation.y), 0, cos(rotation.y));
    
    Matrix3 ztransform = Matrix3(cos(rotation.z), -sin(rotation.z), 0,
                                 sin(rotation.z),  cos(rotation.z), 0,
                                                              0, 0, 1);
    Vector3 rotated = vector;
    rotated = xtransform * (rotated);
    rotated = ytransform * (rotated);
    rotated = ztransform * (rotated);
    return (ztransform * ytransform * xtransform) * vector;
}

#endif /* Matrix3_hpp */
