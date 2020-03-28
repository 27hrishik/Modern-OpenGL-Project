//
//  main.cpp
//  Sphere-cylinder GL4
//
//  Created by Deepak Honakeri on 27/03/20.
//  Copyright © 2020 Deepak Honakeri. All rights reserved.
//

#include <iostream>
using namespace std;

//Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../glm/gtc/type_ptr.hpp"

//Shaders
#include "./sphere.h"
#include "../Shaders/loadShader.hpp"


//Global declarations
unsigned int shaderProgramID;
glm::mat4 m_projMatrix = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
glm::mat4 m_mvMatrix = glm::mat4(1.0f);
Sphere sphere;


//function Declarations
void drawSphere();

int main(int argc, const char * argv[]) {
    
    GLFWwindow* window;
    
    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Find the ball", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, 800, 600);
    
    shaderProgramID = LoadShaders("Sphere/sphereShader.vert", "Sphere/sphereShader.frag");
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(shaderProgramID, "vertexPosition_modelspace");
    sphere.init(vertexPosition_modelspaceID);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        drawSphere();
            
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void drawSphere() {
    // use corresponding shader program, and set the transformation matrices
    glUseProgram(shaderProgramID);
    GLuint projMatrixID = glGetUniformLocation(shaderProgramID, "projMatrix");
    GLuint mvMatrixID = glGetUniformLocation(shaderProgramID, "mvMatrix");
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(m_projMatrix));
    glUniformMatrix4fv(mvMatrixID, 1, GL_FALSE, glm::value_ptr(m_mvMatrix));
    sphere.draw();
}
