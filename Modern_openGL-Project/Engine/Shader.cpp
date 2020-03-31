//
//  loadShader.cpp
//  Modern_openGL-Project
//
//  Created by app king on 3/25/20.
//  Copyright © 2020 app king. All rights reserved.
//

#include "Renderer.hpp"
#include "Shader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertPath,const std::string& fragPath)
: m_VertPath(vertPath),m_FragPath(fragPath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(vertPath,fragPath);
    
    //std::cout << "VERTEX" << std::endl << source.VertexSource << std::endl;
    //std::cout << "FRAGMENT" << std::endl << source.FragmentSource << std::endl;
    
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    
    GLCall( glUseProgram(m_RendererID) );
}

Shader::~Shader()
{
    GLCall( glDeleteProgram(m_RendererID) );
}

void Shader::Bind() const
{
    GLCall( glUseProgram(m_RendererID) );
}

void Shader::Unbind() const
{
    GLCall( glUseProgram(0) );
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    GLCall( int location = glGetUniformLocation(m_RendererID, name.c_str()) );
    if (location == -1)
        std::cout << "No active uniform variable with name " << name << " found" << std::endl;
    
    m_UniformLocationCache[name] = location;
    
    return location;
}

void Material::SetUniform(const std::string& name, int value)
{
    GLCall( glUniform1i(shader.GetUniformLocation(name), value) );
}

void Material::SetUniform(const std::string& name, float value)
{
    GLCall( glUniform1f(shader.GetUniformLocation(name), value) );
}

void Material::SetUniform(const std::string& name, float f0, float f1, float f2, float f3)
{
    GLCall( glUniform4f(shader.GetUniformLocation(name), f0, f1, f2, f3) );
}

void Material::SetUniform(const std::string& name, const glm::mat4& matrix)
{
    GLCall( glUniformMatrix4fv(shader.GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]) );
}

enum ShaderType
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderProgramSource Shader::ParseShader(const std::string& vertPath,const std::string& fragPath)
{
    
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertPath, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertPath.c_str());
        getchar();
        return {"",""};
    }
    
    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragPath, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragPath.c_str());
        getchar();
        return {"",""};
    }
    return {VertexShaderCode,FragmentShaderCode};
    
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall( unsigned int id = glCreateShader(type) );
    const char* src = source.c_str();
    GLCall( glShaderSource(id, 1, &src, nullptr) );
    GLCall( glCompileShader(id) );
    
    // Error handling
    int result;
    GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
    std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compile status: " << result << std::endl;
    if ( result == GL_FALSE )
    {
        int length;
        GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
        char* message = (char*) alloca(length * sizeof(char));
        GLCall( glGetShaderInfoLog(id, length, &length, message) );
        std::cout
        << "Failed to compile "
        << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << "shader"
        << std::endl;
        std::cout << message << std::endl;
        GLCall( glDeleteShader(id) );
        return 0;
    }
    
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    GLCall( glAttachShader(program, vs) );
    GLCall( glAttachShader(program, fs) );
    
    GLCall( glLinkProgram(program) );
    
    GLint program_linked;
    
    GLCall( glGetProgramiv(program, GL_LINK_STATUS, &program_linked) );
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall( glGetProgramInfoLog(program, 1024, &log_length, message) );
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }
    
    GLCall( glValidateProgram(program) );
    
    GLCall( glDeleteShader(vs) );
    GLCall( glDeleteShader(fs) );
    
    return program;
}
