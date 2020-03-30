//
//  Renderer.cpp
//  Modern_openGL-Project
//
//  Created by app king on 3/26/20.
//  Copyright © 2020 app king. All rights reserved.
//

#include "Renderer.hpp"
#include "Shader.hpp"
#include <iostream>

void Renderer::Clear() const
{
    GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,GLenum mode) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDisable(GL_PRIMITIVE_RESTART));
    GLCall( glDrawElements(mode, ib.GetCount(), GL_UNSIGNED_INT, nullptr) );
}

void Renderer::Draw(const RenderData &renderData)
{
    renderData.shader.Bind();
    renderData.vertexArray.Bind();
    renderData.indexBuffer.Bind();
    if(renderData.primitiveRestart)
    {
        GLCall( glEnable(GL_PRIMITIVE_RESTART));
        GLCall( glPrimitiveRestartIndex(GL_PRIMITIVE_RESTART_FIXED_INDEX));
    } else
    {
        GLCall( glDisable(GL_PRIMITIVE_RESTART));
    }
    GLCall( glDrawElements(renderData.mode, renderData.indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr) );
}

