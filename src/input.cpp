#include "input.h"

namespace input
{
    bool isButtonPressed = false;
}

void processInput(GLFWwindow *window)
{
    static bool firstPress = false;
    static double firstPressTime = 0.0;
    static bool escKeyPressed = false;
    
    bool currentEscState = (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
    
    if(currentEscState && !escKeyPressed)
    {
        escKeyPressed = true;
        double currentTime = glfwGetTime();
        
        if(!firstPress)
        {
            firstPress = true;
            firstPressTime = currentTime;
            std::cout << "Press again to close." << std::endl;
        }
        else if(currentTime - firstPressTime <= 1.0)
        {
            glfwSetWindowShouldClose(window, true);
            std::cout << "Closing window..." << std::endl;
        }
    }
    else if(!currentEscState)
    {
        escKeyPressed = false; 
    }

    if(firstPress && (glfwGetTime() - firstPressTime <= 0.1))
    {
        glClearColor(0.95f-(glfwGetTime() - firstPressTime), 0.85f-(glfwGetTime() - firstPressTime), 0.75f-(glfwGetTime() - firstPressTime), 1.0f);
    }

    if(firstPress && (glfwGetTime() - firstPressTime <= 1.0) && (glfwGetTime() - firstPressTime > 0.1))
    {
        glClearColor(-0.05f+(glfwGetTime() - firstPressTime), -0.15f+(glfwGetTime() - firstPressTime), -0.25f+(glfwGetTime() - firstPressTime), 1.0f);
    }
    if(firstPress && (glfwGetTime() - firstPressTime > 1.0))
    {
        firstPress = false;
        std::cout << "Timeout. Press ESC twice again to close." << std::endl;
        glClearColor(0.95f, 0.85f, 0.75f, 1.0f);
    }
}

bool mousePosOnClickRelease(GLFWwindow* window, double xPos, double yPos)
{
    bool clicked = false;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        input::isButtonPressed = true;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && input::isButtonPressed)
    {
        clicked = true;
        input::isButtonPressed = false;
        glfwGetCursorPos(window, &xPos, &yPos);
        std::cout<< xPos << " " << yPos << std::endl;
    }
    return clicked;
}

bool mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos)
{
    bool clicked = false;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !input::isButtonPressed)
    {
        clicked=true;
        input::isButtonPressed = true;
        glfwGetCursorPos(window, xPos, yPos);
        std::cout<< *xPos << " " << *yPos << std::endl;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        input::isButtonPressed = false;
    }

    return clicked;
}