//
//  Scene.hpp
//  3D
//
//  Created by Chaniel Ezzi on 11/4/22.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Node.hpp"

class Scene {
    
private:
    Node root;
    
public:
    
    Scene () {
        root = Node();
    }
    Node* getRoot () { return &root; }
    
};

#endif /* Scene_hpp */
