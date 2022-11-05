//
//  Vector.hpp
//  3DImplementation
//
//  Created by Chaniel Ezzi on 10/19/22.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include <concepts>
#include <math.h>

//template<typename T>
//concept arithmetic = std::integral<T> || std::floating_point<T>;

//template<arithmetic T>
struct Vector3 {
    float x, y, z;
    Vector3 (float x, float y, float z) : x(x), y(y), z(z) {}
    
    Vector3 operator + (const Vector3 &v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator - (const Vector3 &v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator * (const float scalar)   const { return Vector3(x * scalar, y * scalar, z * scalar); }
    Vector3 operator / (const float scalar)   const { return Vector3(x / scalar, y / scalar, z / scalar); }
    
    bool operator == (const Vector3 &v) const { return (x == v.x && y == v.y && z == v.z); }
    bool operator != (const Vector3 &v) const { return !(*this == v); }
    
    float dot(const Vector3 v) const { return (x * v.x) + (y * v.y) + (z * v.z); }
    float magnitude () { return sqrt(x*x + y*y + z*z); }
    
};

#endif /* Vector_hpp */
