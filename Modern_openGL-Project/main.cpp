//
//  main.cpp
//  Modern_openGL-Project
//
//  Created by app king on 3/22/20.
//  Copyright © 2020 app king. All rights reserved.
//

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Renderer Abstraction
#include "Engine/Debugger.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Buffers.hpp"
#include "Engine/Textures.hpp"

//GL Mathematics Libray
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
//function Declarations
void drawTriangle(int);

// Define main function
int main()
{
    // Initialize GLFW
    glfwInit();
    
    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    // Create OpenGL window and context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Find the Ball", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    // Check for window creation failure
    if (!window)
    {
        // Terminate GLFW
        glfwTerminate();
        return 0;
    }
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, 800, 600);
    // Create a vertex Array Object
    unsigned int VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    cout<<"Vertex Array ID :"<<VertexArrayID<<endl;
    
    //Position to draw a Triangle
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    // Early Termination for Deallocation Before the GLFW Context is Lost
    {
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        IndexBuffer ib(indices, 6);
        
        glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
        
        glm::mat4 ident = glm::mat4(1.0f);
        glm::vec3 trvec = glm::vec3(0, 0, 0);
        glm::mat4 view = glm::translate(ident, trvec);
        
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0));
        
        glm::mat4 mvp = proj * view * model;

        
        VertexBufferLayout layout;
        layout.AddFloat(2);
        layout.AddFloat(2);
    
        va.AddBuffer(vb, layout);
    
        Shader shader("Assets/Shaders/basic.vert");
        shader.Bind();
        
        Texture texture("wood.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniformMat4f("u_MVP", mvp);
        
        float red = 0.0f;
        float step = 0.005f;
    
        Renderer renderer;
    
        // Event loop
        while(!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            
            shader.Bind();
            shader.SetUniform4f("u_Color", red, 0.3, 0.8, 1.0);
            
            renderer.Draw(va, ib, shader);
            
            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            // increment red
            if (red < 0.0f || red > 1.0f)
                step *= -1.0;
            red += step;
        }
    }
    
    // Terminate GLFW
    glfwTerminate(); return 0;
}

