//
//  Node.hpp
//  3D
//
//  Created by Chaniel Ezzi on 10/31/22.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <vector>
#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Geometry.hpp"

class Node {
    
private:
    Node *parent = nullptr;
    std::vector<Node*> children = {};
    
public:
    Vector3 position = Vector3(0,0,0);
    Vector3 rotation = Vector3(0,0,0);
    
    Geometry geometry = Geometry();
    
    Node () {}
    
    Node* getParent () const { return parent; }
    std::vector<Node*> getChildren () { return children; }
    
    void addChildNode (Node *child);
    void removeFromParent ();
    
    Vector3 worldRotation () const;
    Vector3 worldPosition () const;
    
};

#endif /* Node_hpp */

