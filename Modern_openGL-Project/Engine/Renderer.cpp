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
    renderData.material.Bind();
    //
    renderData.mesh.v_Array.Bind();
    renderData.mesh.i_Buffer.Bind();
    if(renderData.mesh.restart)
    {
        GLCall( glEnable(GL_PRIMITIVE_RESTART));
        GLCall( glPrimitiveRestartIndex(GL_PRIMITIVE_RESTART_FIXED_INDEX));
    } else
    {
        GLCall( glDisable(GL_PRIMITIVE_RESTART));
    }
    GLCall( glDrawElements(renderData.mesh.mode, renderData.mesh.i_Buffer.GetCount(), GL_UNSIGNED_INT, nullptr) );
}

