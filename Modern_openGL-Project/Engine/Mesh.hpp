//
//  Primitives.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/30/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/glew.h>
#include "Buffers.hpp"
#include <tuple>
#include <vector>

//class to Mesh Data
struct Mesh{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    VertexBufferLayout layout;
    VertexBuffer v_Buffer;
    IndexBuffer i_Buffer;
    VertexArray v_Array;
    GLenum mode;
    bool restart;
    Mesh(std::vector<GLfloat> vert,std::vector<GLuint> ind,VertexBufferLayout l,GLenum mode = GL_TRIANGLES,bool restart = false):
    vertices(vert),
    indices(ind),
    layout(l),
    v_Buffer{&vertices[0], static_cast<unsigned int>(vertices.size()*sizeof(GLfloat))},
    i_Buffer{&indices[0],static_cast<unsigned int>(indices.size())},
    v_Array(),
    mode(mode),
    restart(restart)
    {
        v_Array.AddBuffer(v_Buffer, layout);
    }
};

//class To generate primitives
class Primitives{
public:
    static Mesh CreateSphere(float radius =0.5f,int hDiv = 40 ,int vDiv = 40);
    static Mesh CreateCylinder(float height =1.0f,int sectorDivision = 40,float baseRadius = 0.5f,float topRadius = 0.5f,bool bCap = true,bool tCap = true);
    static Mesh CreateQuad(float height=1.0f,float width=1.0f);
};


#endif /* Primitives_hpp */
