//
//  loadShader.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/25/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <unordered_map>

#include "../glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_VertPath,m_FragPath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    
public:
    Shader(const std::string& vertPath,const std::string& fragPath);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    int GetUniformLocation(const std::string& name);
private:
    struct ShaderProgramSource ParseShader(const std::string& vertPath,const std::string& fragPath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    
};

class Material{
    Shader shader;
public:
    Material(const std::string& vertPath,const std::string& fragPath):shader(vertPath,fragPath){}
    Material(Shader shader):shader(shader){};
    void SetUniform(const std::string& name, int value);
    void SetUniform(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, const glm::mat4& matrix);
    void Bind()
    {
        shader.Bind();
    }
    void Unbind()
    {
        shader.Unbind();
    }

};

#endif /* loadShader_hpp */
