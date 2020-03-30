//
//  Renderer.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/26/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>

#include "Debugger.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"

struct RenderData
{
    VertexArray& vertexArray;
    IndexBuffer& indexBuffer;
    Shader& shader;
    GLenum mode;
    bool primitiveRestart;
    
    RenderData(VertexArray& va,IndexBuffer& ib,Shader& shader,GLenum mode = GL_TRIANGLES,bool enablePrimitiveRestart = false)
    :vertexArray(va),indexBuffer(ib),shader(shader),mode(mode)
    {
        
    }
    
};

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode = GL_TRIANGLES) const;
    void Draw(const RenderData& renderData);
};

#endif /* Renderer_hpp */
