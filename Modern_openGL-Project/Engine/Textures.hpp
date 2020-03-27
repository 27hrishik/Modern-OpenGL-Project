//
//  Textures.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/26/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Textures_hpp
#define Textures_hpp

#include "Renderer.hpp"

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    
public:
    Texture(const std::string& path);
    ~Texture();
    
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
};
#endif /* Textures_hpp */
