
//
//  Primitives.cpp
//  Modern_openGL-Project
//
//  Created by app king on 3/30/20.
//  Copyright © 2020 app king. All rights reserved.
//

#include "Primitives.hpp"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
//#include "../glm/gtc/type_ptr.hpp"

std::vector<float> getUnitCircleVertices(int=10,float=0.0f,float=1.0f);

std::tuple<std::vector<GLfloat>,std::vector<GLuint>> Primitives::CreateSphere(float radius, int hDiv , int vDiv) {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int indicator = 0;
    int lats = vDiv,longs = hDiv;
    for(int i = 0; i <= lats; i++) {
        double lat0 = glm::pi<double>() * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);
        
        double lat1 = glm::pi<double>() * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        
        for(int j = 0; j <= longs; j++) {
            double lng = 2 * glm::pi<double>() * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
            
            vertices.push_back(x * zr0 * radius);
            vertices.push_back(y * zr0 * radius);
            vertices.push_back(z0 * radius);
            indices.push_back(indicator);
            indicator++;
            
            vertices.push_back(x * zr1 * radius);
            vertices.push_back(y * zr1 * radius);
            vertices.push_back(z1 * radius);
            indices.push_back(indicator);
            indicator++;
        }
        indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    }
    return {vertices,indices};
}

std::tuple<std::vector<GLfloat>,std::vector<GLuint>> Primitives::CreateCylinder(float height,int sectorDivision,float baseRadius, float topRadius, bool bCap, bool tCap){
    
    std::vector<GLfloat> vertices = getUnitCircleVertices(sectorDivision,-height/2,baseRadius);
    std::vector<GLuint> indices;
    std::vector<GLfloat> top = getUnitCircleVertices(sectorDivision,height/2,topRadius);
    vertices.insert(vertices.end(), top.begin(), top.end());
    for(int i=0;i<sectorDivision;i++)
    {
        unsigned int a = i%sectorDivision;
        unsigned int b = (i+1)%sectorDivision;
        indices.insert(indices.end(),{a,b,sectorDivision+b});
        indices.insert(indices.end(),{a,sectorDivision+b,sectorDivision+a});
    }
    if(bCap)
    {
        vertices.insert(vertices.end(), {0.0f,-height/2,0.0f});
        unsigned int index = vertices.size()/3 -1;
        for(int i=0;i<sectorDivision;i++)
        {
            unsigned int a = i%sectorDivision;
            unsigned int b = (i+1)%sectorDivision;
            indices.insert(indices.end(), {a,b,index});
        }
    }
    if(tCap)
    {
        vertices.insert(vertices.end(), {0.0f,height/2,0.0f});
        unsigned int index = vertices.size()/3 -1;
        for(int i=0;i<sectorDivision;i++)
        {
            unsigned int a = i%sectorDivision;
            unsigned int b = (i+1)%sectorDivision;
            indices.insert(indices.end(), {sectorDivision+a,sectorDivision+b,index});
        }
    }
    return {vertices,indices};
}

std::vector<float> getUnitCircleVertices(int sectorCount, float yVal, float radius)
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian
    
    std::vector<float> unitCircleVertices;
    for(int i = 0; i < sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle) * radius); // x
        unitCircleVertices.push_back(yVal); // y
        unitCircleVertices.push_back(sin(sectorAngle) * radius);                // z
    }
    return unitCircleVertices;
}

std::tuple<std::vector<GLfloat>,std::vector<GLuint>> Primitives::CreateQuad(float height,float width)
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    vertices.insert(vertices.end(), {-width/2,-height/2,0.0f});
    vertices.insert(vertices.end(), {width/2,-height/2,0.0f});
    vertices.insert(vertices.end(), {width/2,height/2,0.0f});
    vertices.insert(vertices.end(), {-width/2,height/2,0.0f});
    indices.insert(indices.end(), {0,1,2});
    indices.insert(indices.end(), {0,2,3});
    return {vertices,indices};
}
