//
//  main.cpp
//  Modern_openGL-Project
//
//  Created by app king on 3/22/20.
//  Copyright © 2020 app king. All rights reserved.
//

#include<iostream>

//Base GL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Renderer Abstraction
#include "Engine/Debugger.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Buffers.hpp"
#include "Engine/Textures.hpp"
#include "Engine/Primitives.hpp"

//GL Mathematics Libray
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
//function Declarations
std::vector<float> getUnitCircleVertices(float,float);

//global declaration
float height = 1.0f;
float radius = 0.5f;

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
//    float positions[] = {
//        -0.5f, -0.5f, 0.0f, 0.0f, // 0
//         0.5f, -0.5f, 1.0f, 0.0f, // 1
//         0.5f,  0.5f, 1.0f, 1.0f, // 2
//        -0.5f,  0.5f, 0.0f, 1.0f  // 3
//    };
//
//    unsigned int indices[] = {
//        0, 1, 2,
//        2, 3, 0
//    };
    
    auto[vertices0,indices0] = Primitives::CreateSphere();
    auto[vertices1,indices1] = Primitives::CreateCylinder(1.0f,20,0.6f,0.5f,false);
    auto[vertices2,indices2] = Primitives::CreateQuad();
    
    for(auto& vert:vertices2)
        std::cout<<vert<<" ";
    std::cout<<endl;
    for(auto& ind:indices2)
        std::cout<<ind<<" ";
    // Early Termination for Deallocation Before the GLFW Context is Lost
    {
        VertexArray va0,va1,va2;
        
        VertexBuffer vb0(&vertices0[0], vertices0.size()*sizeof(GLfloat));
        IndexBuffer ib0(&indices0[0], indices0.size());
        
        VertexBuffer vb1(&vertices1[0], vertices1.size()*sizeof(GLfloat));
        IndexBuffer ib1(&indices1[0], indices1.size());
        
        VertexBuffer vb2(&vertices2[0], vertices2.size()*sizeof(GLfloat));
        IndexBuffer ib2(&indices2[0], indices2.size());
        
        glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -10.0f, 10.0f);
        
        glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
        glm::mat4 model0 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 model1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,0.0f,0.0f));
        glm::mat4 model2 = glm::rotate(glm::mat4(1.0f), -45.0f, glm::vec3(1.0f,0.0f,0.0f));
        
        glm::mat4 mvp0 = proj * view * model0;
        glm::mat4 mvp1 = proj * view * model1;
        glm::mat4 mvp2 = proj * view * model2;
        
        VertexBufferLayout layout0,layout1,layout2;
        layout0.AddFloat(3);
        layout1.AddFloat(3);
        layout2.AddFloat(3);
    
        va0.AddBuffer(vb0, layout0);
        va1.AddBuffer(vb1, layout1);
        va2.AddBuffer(vb2, layout2);
        
        Shader shader0("Assets/Shaders/Unlit.vert","Assets/Shaders/Unlit.frag");
        //Shader shader1("Assets/Shaders/Basic.vert","Assets/Shaders/Basic.vert");
        
        RenderData rData0(va0,ib0,shader0,GL_TRIANGLE_STRIP,false);
        RenderData rData1(va1,ib1,shader0,GL_TRIANGLES,false);
        RenderData rData2(va2,ib2,shader0,GL_TRIANGLES,false);
    
        Renderer renderer;
    
        // Event loop
        while(!glfwWindowShouldClose(window))
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            renderer.Clear();
            
            shader0.SetUniform4f("u_Color", 1.0f,1.0f,0.0f,0.0f);
            shader0.SetUniformMat4f("u_MVP", mvp0);
            renderer.Draw(rData0);

            model1 = glm::rotate(model1,0.005f,glm::normalize(glm::vec3(1.0f,1.0f,1.0f)));
            mvp1 = proj * view * model1;
            shader0.SetUniformMat4f("u_MVP", mvp1);
            renderer.Draw(rData1);
            
            shader0.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
            shader0.SetUniformMat4f("u_MVP", mvp2);
            renderer.Draw(rData2);
            
            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    
    // Terminate GLFW
    glfwTerminate(); return 0;
}


