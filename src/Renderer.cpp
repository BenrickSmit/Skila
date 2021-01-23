#include "Renderer.h"  

#include <iostream>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


// Enable the Current Working Directory without FileSystem and its headache
std::string get_current_dir() {
   char buffer[FILENAME_MAX]; //create string buffer to hold path
   GetCurrentDir( buffer, FILENAME_MAX );
   std::string current_working_dir(buffer);
   return current_working_dir;
}

void GLClearError(){
    // This function doesn't really care about the actual errors, it just wants
    // to clear all the errors
    while(glGetError() != GL_NO_ERROR);
    // Alternative is: while(!glGetError()); since GL_NO_ERROR == 0;
}

bool GLLogCall(const char* function, const char* file, int line){
    // This function will return information about the error given
    // it will continue to run while GLenum is not 0 either
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] " << "( " << error << " ): " << function << ", "
        << file << ": " << line << std::endl;
        return false;
    };
    return true;
}












// Renderer Class
Renderer::Renderer()
{
	
}
	
Renderer::~Renderer()
{
	
}