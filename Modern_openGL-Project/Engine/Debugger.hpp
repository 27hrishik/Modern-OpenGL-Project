//
//  Renderer.hpp
//  Modern_openGL-Project
//
//  Created by app king on 3/26/20.
//  Copyright © 2020 app king. All rights reserved.
//

#ifndef Debugger_hpp
#define Debugger_hpp

#include <GL/glew.h>
#include <assert.h>

#define ASSERT(x) if (!(x)) assert(false)
#define INT2VOIDP(i) (void*)(uintptr_t)(i)

#define GLCall(x) GLClearError();\
x;\
ASSERT(GLCheckError())

void GLClearError();
bool GLCheckError();

#endif /* Renderer_hpp */
