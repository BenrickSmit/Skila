#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include <GL/glew.h>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "Skila.h"

// Create a Custom Compiler Specific Assert
#ifdef __GNUC__
    #include <signal.h>
    #ifdef SIGTRAP
        #define ASSERT(x) if(!(x)) raise(SIGTRAP);
    #else
        #define ASSERT(x) if(!(x)) raise(SIGABRT);
    #endif
#elif defined( __clang__ )
    #define ASSERT(x) if(!(x)) __debugbreak();
#elif defined( _MSV_VER )
    #define ASSERT(x) if(!(x)) __debugbreak();
#endif

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));


std::string get_current_dir();

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);



class Renderer  
{
	private:

	public:
		Renderer();
		~Renderer();

};
#endif