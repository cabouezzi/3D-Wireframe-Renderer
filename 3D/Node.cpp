//
//  Node.cpp
//  3D
//
//  Created by Chaniel Ezzi on 10/31/22.
//

#include "Node.hpp"
#include <iostream>

void Node::addChildNode(Node *child) {
    child->removeFromParent();
    children.push_back(child);
    child->parent = this;
}

void Node::removeFromParent() {
    if (parent == nullptr) return;
    if (parent->children.empty()) return;
    
    for (int i = 0; i < parent->children.size(); i++) {
        if (parent->children[i] == this) {
            parent->children.erase(parent->children.begin() + i);
            return;
        }
    }
    exit(99);
}

Vector3 Node::worldRotation() const {
    if (parent == nullptr) return rotation;
    return rotation + parent->worldRotation();
}

Vector3 Node::worldPosition() const {
    if (parent == nullptr) return position;
    return rotatedVector(position, parent->worldRotation()) + parent->worldPosition();
}
