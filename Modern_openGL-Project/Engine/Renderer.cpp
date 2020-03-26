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
    GLCall( glClear( GL_COLOR_BUFFER_BIT ) );
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall( glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr) );
}
