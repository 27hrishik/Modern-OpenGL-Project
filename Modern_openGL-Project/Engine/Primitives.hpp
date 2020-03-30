//
//  Primitives.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/30/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Primitives_hpp
#define Primitives_hpp

#include <GL/glew.h>
#include <tuple>
#include <vector>

//class To generate primitives
class Primitives{
public:
    static std::tuple<std::vector<GLfloat>,std::vector<GLuint>> CreateSphere(float radius =0.5f,int hDiv = 40 ,int vDiv = 40);
    static std::tuple<std::vector<GLfloat>,std::vector<GLuint>> CreateCylinder(float height =1.0f,int sectorDivision = 40,float baseRadius = 0.5f,float topRadius = 0.5f,bool bCap = true,bool tCap = true);
    static std::tuple<std::vector<GLfloat>,std::vector<GLuint>> CreateQuad(float height=1.0f,float width=1.0f);
};


#endif /* Primitives_hpp */
