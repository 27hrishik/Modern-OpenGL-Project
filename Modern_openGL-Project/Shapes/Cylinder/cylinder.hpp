//
//  cylinder.hpp
//  Sphere-cylinder GL4
//
//  Created by Deepak Honakeri on 28/03/20.
//  Copyright © 2020 Deepak Honakeri. All rights reserved.
//

#ifndef cylinder_hpp
#define cylinder_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <iostream>

class Cylinder
{
public:
    Cylinder();
    ~Cylinder();
    void init(GLuint vertexPositionID);
    void cleanup();
    void draw();
    std::vector<float> getUnitCircleVertices();

private:
    GLuint m_vao, m_vboVertex, m_vboIndex;
    bool isInited;
    long long int numsToDraw;
    int height,radius;
//    int lats, longs;
    int sectorCount;
};

#endif /* cylinder_hpp */
