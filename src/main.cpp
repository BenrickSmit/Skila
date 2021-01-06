#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Skila.h"

#include <iostream>

//find documentation for OpenGL in docs.GL

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
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    // Define the vertex buffer to give OpenGL the data to draw
    // We can define many different buffers, but for now we only want 1 buffer
    // we also need to give the function a pointer to an unsigned int.
    // buffer itself is only the ID of the generated buffer.
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    // We have generated a buffer, now we want to select the buffer. Selecting
    // a buffer in OpenGL is called Binding.
    // GL_ARRAY_BUFFER basically just says that it's an array
    // we select the ID of the buffer we've just generated
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // We have specified a buffer, but not really the data in it. We have only
    // specified that we are going to work in it.
    // Here we specify the buffer data and how big it is
    // STATIC means that the it will be drawn every frame, but not modified every frame
    // DYNAMIC means it will be drawn and modified every frame
    // DRAW means we want to draw the actual buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_DYNAMIC_DRAW);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // This is the method to use when we don't have an index buffer, which we don't yet
        // GLenum is what kind of primitive to draw, in this case GL_TRIANGLES
        // first here means which coordinate to draw first
        // count here means how many vertices to draw
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}