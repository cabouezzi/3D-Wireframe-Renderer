//
//  Models.cpp
//  3D
//
//  Created by Chaniel Ezzi on 11/4/22.
//

#include "Models.hpp"

Geometry obj_Models (string path) {
    fstream file;
    file.open(path);
    
    if (!file.is_open()) cout << "Couldn't find file\n" << filesystem::current_path();
    
    vector<Vector3> vertices = {};
    vector<int> faces = {};
    
    string line;
    
    while (getline(file, line)) {
        
        vector<string> tokens = {};
        
        char* tok = strtok(line.data(), " ");
        while (tok != NULL) {
            tokens.push_back(string(tok));
            tok = strtok(NULL, " ");
        }
        
        if (tokens[0] == "v") {
            vertices.push_back(Vector3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
        }
        if (tokens[0] == "f") {
            for (int i = 1; i < tokens.size(); i++) {
                faces.push_back(stoi(tokens[i]) - 1);
            }
        }
        
    }
    
    return Geometry(static_cast<Vector3*>(vertices.data()),
                    static_cast<int>(vertices.size()),
                    {},
                    0,
                    static_cast<int*>(faces.data()),
                    static_cast<int>(faces.size()));
}

Geometry Models::cube() {
    Geometry c = obj_Models("/Users/chanielezzi/Desktop/Code/Personal/3D/3D/cube.obj");
    
    for (int i = 0; i < c.vertices.size(); i++) c.vertices[i] = c.vertices[i];
    
    return c;
    
}

Geometry Models::face() {
    return obj_Models("/Users/chanielezzi/Desktop/Code/Personal/3D/3D/face.obj");
}

Geometry Models::bunny() {
    return obj_Models("/Users/chanielezzi/Desktop/Code/Personal/3D/3D/bunny.obj");
}
