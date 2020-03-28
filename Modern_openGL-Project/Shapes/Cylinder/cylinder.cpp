//
//  cylinder.cpp
//  Sphere-cylinder GL4
//
//  Created by Deepak Honakeri on 28/03/20.
//  Copyright © 2020 Deepak Honakeri. All rights reserved.
//

#include "cylinder.hpp"

#include <vector>
#include <iostream>
#include "../../glm/gtc/matrix_inverse.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../../glm/gtx/string_cast.hpp"


Cylinder::Cylinder()
{
    isInited = false;
    m_vao = 0;
    m_vboVertex = 0;
    m_vboIndex = 0;

    height = 1.0f;
    radius = 0.5f;
    sectorCount = 3;
}

Cylinder::~Cylinder()
{

}

// generate a unit circle on XY-plane
std::vector<float> Cylinder::getUnitCircleVertices()
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    std::vector<float> unitCircleVertices;
    for(int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y
        unitCircleVertices.push_back(0);                // z
    }
    return unitCircleVertices;
}

void Cylinder::init(GLuint vertexPositionID)
{
    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;        //textCoordinates
    std::vector<GLfloat> normals;
    
    // get unit circle vectors on XY-plane
    std::vector<GLfloat> unitVertices = getUnitCircleVertices();

    // put side vertices to arrays
    for(int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        for(int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k+1];
            float uz = unitVertices[k+2];
            // position vector
            vertices.push_back(ux * radius);             // vx
            vertices.push_back(uy * radius);             // vy
            vertices.push_back(h);                       // vz
            // normal vector
            normals.push_back(ux);                       // nx
            normals.push_back(uy);                       // ny
            normals.push_back(uz);                       // nz
            // texture coordinate
            indices.push_back((GLfloat)j / sectorCount); // s
            indices.push_back(t);                      // t
        }
    }
    int baseCenterIndex = (int)vertices.size() / 3;
    int topCenterIndex = baseCenterIndex + sectorCount + 1; // include center vertex

    // put base and top vertices to arrays
    for(int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float nz = -1 + i * 2;                           // z value of normal; -1 to 1

        // center point
        vertices.push_back(0);     vertices.push_back(0);     vertices.push_back(h);
        normals.push_back(0);      normals.push_back(0);      normals.push_back(nz);
        indices.push_back(0.5f); indices.push_back(0.5f);

        for(int j = 0, k = 0; j < sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k+1];
            // position vector
            indices.push_back(ux * radius);             // vx
            indices.push_back(uy * radius);             // vy
            indices.push_back(h);                       // vz
            // normal vector
            normals.push_back(ux);                       // nx
            normals.push_back(uy);                       // ny
            normals.push_back(nz);                       // nz
            // texture coordinate
            indices.push_back(-ux * 0.5f + 0.5f);      // s
            indices.push_back(-uy * 0.5f + 0.5f);      // t
        }
    }


    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vboVertex);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(vertexPositionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (vertexPositionID);

    glGenBuffers(1, &m_vboIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), &indices[0], GL_STATIC_DRAW);

    numsToDraw = indices.size();

    isInited = true;
}

void Cylinder::cleanup()
{
    if (!isInited) {
        return;
    }
    if(m_vboVertex) {
        glDeleteBuffers(1, &m_vboVertex);
    }
    if(m_vboIndex) {
        glDeleteBuffers(1, &m_vboIndex);
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }

    isInited = false;
    m_vao = 0;
    m_vboVertex = 0;
    m_vboIndex = 0;
}

void Cylinder::draw()
{
    if (!isInited) {
        std::cout << "please call init() before draw()" << std::endl;
    }

    // draw cylinder
    glBindVertexArray(m_vao);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
    glDrawElements(GL_QUAD_STRIP, numsToDraw, GL_UNSIGNED_INT, NULL);
}

