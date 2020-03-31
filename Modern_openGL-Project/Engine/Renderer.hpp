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
#include "Mesh.hpp"

struct RenderData
{
    Mesh& mesh;
    Material& material;
    
    RenderData(Mesh& mesh,Material& material)
    :mesh(mesh),material(material){}
    
};

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode = GL_TRIANGLES) const;
    void Draw(const RenderData& renderData);
};

#endif /* Renderer_hpp */
