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
#include "Shader/loadShader.hpp"

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
    static const float vertexBufferData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    
    //Create a Vertex Buffer
    // This will identify our vertex buffer
    unsigned int vertexBufferID;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexBufferID);
    cout<<"Vertex Buffer ID :"<<vertexBufferID<<endl;
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexBufferData, GL_STATIC_DRAW);
    
    unsigned int shaderProgramID = LoadShaders("Shader/basic.vert", "Shader/basic.frag");
    // Event loop
    while(!glfwWindowShouldClose(window))
    {
        // Clear the screen to black
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        // the Main code Starts here
        //Use the Shader Program
        glUseProgram(shaderProgramID);
        drawTriangle(vertexBufferID);
        //the Main Code Ends here
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Terminate GLFW
    glfwTerminate(); return 0;
}

void drawTriangle(int vertexBufferID)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}
