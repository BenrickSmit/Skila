#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <string>
#include <sstream>

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

//find documentation for OpenGL in docs.GL, go and read the documentation for each of these functions used

// Enable the Current Working Directory without FileSystem and its headache
std::string get_current_dir() {
   char buffer[FILENAME_MAX]; //create string buffer to hold path
   GetCurrentDir( buffer, FILENAME_MAX );
   std::string current_working_dir(buffer);
   return current_working_dir;
}

static void GLClearError(){
    // This function doesn't really care about the actual errors, it just wants
    // to clear all the errors
    while(glGetError() != GL_NO_ERROR);
    // Alternative is: while(!glGetError()); since GL_NO_ERROR == 0;
}

static bool GLLogCall(const char* function, const char* file, int line){
    // This function will return information about the error given
    // it will continue to run while GLenum is not 0 either
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] " << "( " << error << " ): " << function << ", "
        << file << ": " << line << std::endl;
        return false;
    };
    return true;
}

// To contain the Shader Data
struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

// Parse through the shader
static ShaderProgramSource ParseShader(const std::string& filepath){
    
    enum class ShaderType {NONE=-1,VERTEX=0,FRAGMENT=1};
    
    std::ifstream file_stream(filepath);
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    // Error Checking
    if(!file_stream.is_open()){
        std::cerr << "ERROR: opening shaders" << std::endl;
        //std::cerr << filepath << std::endl;
    }else{
        std::cout << "File Open: " << filepath << std::endl;
    }

    std::string line;
    while(getline(file_stream, line)){
        if (line.find("#shader") != std::string::npos){
            // Depending on the type of shader, set mode to that particular shader
            if (line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }else if(line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }else{
            // Add the code based on what kind of shader it is
            ss[(int)type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

// Creating shaders is a process that can be abstracted to save us from duplicated code
// It's better to use only C++ types instead of OpenGL types since this helps us later with
// when we use multiple GPU APIs
static unsigned int CompileShader(unsigned int type, const std::string& source){
    GLCall(unsigned int id = glCreateShader(type));
    // OpenGL will not expect a std::string, but instead will expect a raw string
    // PS: std::string source must currently exist and still exist by this time, or else you'll get garbage!
    const char* src = source.c_str(); //&source[0] is also possible
    // This specifies the source of our shader.
    // the first argument is GLuint which is simply an id to the created shader
    // the second arg is GLsizei which asks how many source codes we are specifying
    // the third argument is the actual source for the shader, but use the memory address
    // the fourth argument is the length of the shader. If you don't want to use the whole shader
    //          simply use nullptr.
    GLCall(glShaderSource(id, 1, &src, nullptr));

    // Now, we actually want to compile the shader, and for that we need to specify which shader
    // to compile, i.e. ID
    GLCall(glCompileShader(id));

    // We can query whether there might be something wrong with our Shader since glCompileShader doesn't return anything
    // The base function is "glGetShader", whereas "iv" is the types it needs
    // The first argument is the shader id
    // the second argument is the GLenum which we know is an uint.
    // The third argument is the pointer to the integer that we can use to validate the shader
    //
    // NOTE: glGetShaderiv - i in "iv" means we are specifying an integer
    //                       v in "iv" means it wants a vector, specifically pointing to the &result pointer
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        // Get the actual error message
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        // This allows us to hack a char creation on the stack without the use of pointers, etc.
        // PS: alloca is a c-function that allows you to allocate on the stack dynamically
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cerr << "ERROR: Failed to compile shader in CompileShader()." << std::endl;
        std::cerr << "Resulting Shader Error? : " << (type == GL_VERTEX_SHADER ? "Vertex Shader":"Fragment Shader") << std::endl;
        std::cerr << message << std::endl;
        GLCall(glDeleteShader(id));

        return 0;
    }


    return id;
}

// Creating Shaders for use with OpenGL
static unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader){
    // These strings above are the actual source code for the shaders that need to be
    // compiled
    // NOTE: Shaders can be downloaded, used as binaries, or simply written as strings
    // in C++

    // Create the shader program, but it doesn't return a reference, instead it
    // returns an unsigned integer in the form of GLint
    GLCall(unsigned int program = glCreateProgram());

    
    // Create the vertex shader
    // The only input to glCreateShader is a GLenum that asks what type of shader it is
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);

    // Create the fragment shader
    // the only input is GLenum which basically asks what type of shader it will be
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    // Now we need to attach these created shaders to our program, so that they can
    // be executed in the graphics pipeline
    // The first argument is the program (on the GPU) that we want to attach the shaders to
    // The second argument is the actual shader you want to attach
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    // Now want to link the actual created program so that it can be executed in the pipeline
    GLCall(glLinkProgram(program));
    // Finally we want to validate the program that we created to see whether it can be
    // executed given the current OpenGL state
    GLCall(glValidateProgram(program));

    // Now we can delete the "intermediates"
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    // Return the program
    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Setup GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: glewInit() main.cpp. Cannot initialize GLEW!" << std::endl;
    }else {
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }

    
    // Define the positions that draw the triangle
    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    // Index buffers help us reduce memory wastage in large projects. GPU memory is limited.
    // this helps us reuse certain coordinates as necessary
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    // Define the vertex buffer to give OpenGL the data to draw
    // We can define many different buffers, but for now we only want 1 buffer
    // we also need to give the function a pointer to an unsigned int.
    // buffer itself is only the ID of the generated buffer.
    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    // We have generated a buffer, now we want to select the buffer. Selecting
    // a buffer in OpenGL is called Binding.
    // GL_ARRAY_BUFFER basically just says that it's an array
    // we select the ID of the buffer we've just generated
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    // We have specified a buffer, but not really the data in it. We have only
    // specified that we are going to work in it.
    // Here we specify the buffer data and how big it is
    // STATIC means that the it will be drawn every frame, but not modified every frame
    // DYNAMIC means it will be drawn and modified every frame
    // DRAW means we want to draw the actual buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_DYNAMIC_DRAW));

    // Need to call glVertex in order to enable the VertexAttrib pointer you use
    // The argument taken is the index you want to enable, in this case it's zero
    GLCall(glEnableVertexAttribArray(0));

    // This function requires the Buffer to already be bound.
    // First argument is the index, in this case: 0. Since this is the first attribute
    // Second argument is the size, we have 2D coordinates, so we use 2 for our component count
    // Third argument is hte type of data that we have that are stored, in this case floats
    // Fourth argument is whether we want our values to be normalised (between 0.0-1.0). Floats are already normalised
    // Fifth argument is the amount of bytes between each vertex (one point, basically). IF you have a struct, you can pass the size of that struct as well
    //          just remember: stride - the amount of bytes you need to go forward to get to the next vertex, etc
    // Sixth argument is kind of the offset, but in this case it will be zero
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));


    // Creating out index buffer
    unsigned int ibo;       //index buffer object
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW));


    // Let's write the actual shader
    ShaderProgramSource source;
    #ifdef __unix
        source = ParseShader(get_current_dir() + "/../../res/shaders/basic.shader");
    #else
        source = ParseShader(get_current_dir() + "/../../res/shaders/basic.shader");
    #endif

    std::cout << "VERTEC_SHADER:" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT_SHADER:" << std::endl;
    std::cout << source.FragmentSource << std::endl;
    
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    // Now we bind the shader to make sure OpenGL uses our shaders
    GLCall(glUseProgram(shader));

    // We need to get the location of the Shader Uniform we wish to send data to
    // we do this by getting the ID from OpenGL. NOTE: the we need a shader that
    // is already bound for this to work properly.
    // shader is the required GPU program to query
    // "u_colour" is the variable we want
    GLCall(int location = glGetUniformLocation(shader, "u_colour"));
    // We also need to assert and make sure that location != -1. This means
    // it couldn't find the shader or that the uniform in the shader is unused
    ASSERT(location  !=  -1);

    // Set the colour of the program via uniform
    // Why glUniform4f? We are sending 4 pieces of data to the GPU
    // and their types are all floats
    // location is the queried location of the uniform in the shader
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // This is the method to use when we don't have an index buffer, which we don't yet
        // GLenum is what kind of primitive to draw, in this case GL_TRIANGLES
        // first here means which coordinate to draw first
        // count here means how many vertices to draw
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Remove the added shaders
    GLCall(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}