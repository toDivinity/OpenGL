#include "input.h"

namespace input
{
    bool isButtonPressed = false;
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