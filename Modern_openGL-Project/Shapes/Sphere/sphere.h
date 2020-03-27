//
//  sphere.h
//  Sphere-cylinder GL4
//
//  Created by Deepak Honakeri on 27/03/20.
//  Copyright © 2020 Deepak Honakeri. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include <GL/glew.h>


class Sphere
{
public:
    Sphere();
    ~Sphere();
    void init(GLuint vertexPositionID);
    void cleanup();
    void draw();

private:
    int lats, longs;
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
    int numsToDraw;
};

#endif /* sphere_h */
