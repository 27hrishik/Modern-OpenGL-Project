//
//  Textures.cpp
//  Modern_openGL-Project
//
//  Created by app king on 3/26/20.
//  Copyright © 2020 app king. All rights reserved.
//

#include "Textures.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../Vendors/stb_image.h"

Texture::Texture(const std::string& path)
: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 3);
    GLCall( glGenTextures(1, &m_RendererID) );
    if(!m_LocalBuffer)
    {
        std::cout<<"Texture didn't load"<<std::endl;
        exit(-1);
    }
    GLCall( glBindTexture(GL_TEXTURE_2D, m_RendererID) ); // Bind without slot selection
    
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );
    
    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer) );
    Unbind();
    
    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
};

Texture::~Texture()
{
    GLCall( glDeleteTextures(1, &m_RendererID) );
}

void Texture::Bind(unsigned int slot) const
{
    GLCall( glActiveTexture(GL_TEXTURE0 + slot) );
    GLCall( glBindTexture(GL_TEXTURE_2D, m_RendererID) );
}

void Texture::Unbind() const
{
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
}
