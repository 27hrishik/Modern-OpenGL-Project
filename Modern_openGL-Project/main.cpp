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
#include "Engine/Mesh.hpp"

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
    
    Mesh m0 = Primitives::CreateSphere();
    Mesh m1 = Primitives::CreateCylinder(1.0f,20,0.6f,0.5f,false);
    Mesh m2 = Primitives::CreateQuad();

    // Early Termination for Deallocation Before the GLFW Context is Lost
    {
        glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -10.0f, 10.0f);
        
        glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
        glm::mat4 model0 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 model1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,0.0f,0.0f));
        glm::mat4 model2 = glm::rotate(glm::mat4(1.0f), -45.0f, glm::vec3(1.0f,0.0f,0.0f));
        
        glm::mat4 mvp0 = proj * view * model0;
        glm::mat4 mvp1 = proj * view * model1;
        glm::mat4 mvp2 = proj * view * model2;
        
        Material material0("Assets/Shaders/Unlit.vert","Assets/Shaders/Unlit.frag");
        //Shader shader1("Assets/Shaders/Basic.vert","Assets/Shaders/Basic.vert");
        
        RenderData rData0(m0,material0);
        RenderData rData1(m1,material0);
        RenderData rData2(m2,material0);
    
        Renderer renderer;
    
        // Event loop
        while(!glfwWindowShouldClose(window))
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            renderer.Clear();
            
            material0.SetUniform("u_Color", 1.0f,1.0f,0.0f,0.0f);
            material0.SetUniform("u_MVP", mvp0);
            renderer.Draw(rData0);

            model1 = glm::rotate(model1,0.005f,glm::normalize(glm::vec3(1.0f,1.0f,1.0f)));
            mvp1 = proj * view * model1;
            material0.SetUniform("u_MVP", mvp1);
            renderer.Draw(rData1);
            
            material0.SetUniform("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
            material0.SetUniform("u_MVP", mvp2);
            renderer.Draw(rData2);
            
            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    
    // Terminate GLFW
    glfwTerminate(); return 0;
}


