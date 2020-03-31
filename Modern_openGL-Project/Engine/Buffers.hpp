//
//  Buffers.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/26/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Buffers_hpp
#define Buffers_hpp

#include "Debugger.hpp"
#include <vector>
#include <GL/glew.h>

class IndexBuffer
{
public:
    IndexBuffer():m_RendererID(0),m_Count(0){};
    IndexBuffer(const unsigned int* indices, unsigned int count);
    ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
    inline unsigned int GetCount() const { return m_Count; }
    
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};

class VertexBuffer
{
public:
    VertexBuffer():m_RendererID(0){};
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind();
    
private:
    unsigned int m_RendererID;
};

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT         : return sizeof(GLfloat);
            case GL_UNSIGNED_INT  : return sizeof(GLuint);
            case GL_UNSIGNED_BYTE : return sizeof(GLbyte);
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement> m_Elements;
    
public:
    VertexBufferLayout() :
    m_Stride(0) { }
    
    void AddFloat(unsigned int count)        { Push(GL_FLOAT, count, GL_FALSE);        }
    void AddUnsignedInt(unsigned int count)  { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
    void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }
    
    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
    inline unsigned int GetStride() const { return m_Stride; };
    
private:
    void Push(unsigned int type, unsigned int count, unsigned char normalized)
    {
        struct VertexBufferElement vbe = {type, count, normalized};
        m_Elements.push_back(vbe);
        m_Stride += count * VertexBufferElement::GetSizeOfType(type);
    };
};

class VertexArray
{
private:
    unsigned int m_RendererID;
    
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};

#endif /* Buffers_hpp */
