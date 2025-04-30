#include "DivineConfig.h"
#include "DivineCamera.h"

namespace DivineInput
{
    bool isButtonPressed = false;

    bool mousePosOnClickRelease(GLFWwindow* window, double xPos, double yPos)
    {
        bool clicked = false;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            DivineInput::isButtonPressed = true;
        }

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && DivineInput::isButtonPressed)
        {
            clicked = true;
            DivineInput::isButtonPressed = false;
            glfwGetCursorPos(window, &xPos, &yPos);
            std::cout<< xPos << " " << yPos << std::endl;
        }
        return clicked;
    }

    bool  mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos)
    {
        bool clicked = false;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !DivineInput::isButtonPressed)
        {
            clicked=true;
            DivineInput::isButtonPressed = true;
            glfwGetCursorPos(window, xPos, yPos);
            std::cout<< *xPos << " " << *yPos << std::endl;
        }

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            DivineInput::isButtonPressed = false;
        }

        return clicked;
    }
}