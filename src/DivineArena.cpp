#include "DivineArena.h"

GLint DivineArena()
{
    if(!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Divine Arena", NULL, NULL);

    if(!mainWindow)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(mainWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -3;
    }

    GLuint mainProgram = make_shader("../../shaders/mainVertex.glsl", "../../shaders/mainFragment.glsl");

    
    
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    while(!glfwWindowShouldClose(mainWindow))
    {
       
        glUseProgram(mainProgram);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}