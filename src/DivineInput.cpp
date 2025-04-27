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

    bool mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos)
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

    void processInput(GLFWwindow *window, DivineCamera::Camera *camera, GLfloat deltaTime, float* viewAngleX, float* viewAngleY)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera->cameraPos -= camera->cameraTarget*camera->cameraSpeed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera->cameraPos += DivineMath::cross(camera->cameraTarget, DivineCamera::up)*camera->cameraSpeed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            camera->cameraPos += camera->cameraTarget*camera->cameraSpeed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera->cameraPos -= DivineMath::cross(camera->cameraTarget, DivineCamera::up)*camera->cameraSpeed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        {
            camera->cameraPos += DivineMath::cross(DivineMath::cross(camera->cameraTarget, DivineCamera::up), camera->cameraTarget)*camera->cameraSpeed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            camera->cameraPos -= DivineMath::cross(DivineMath::cross(camera->cameraTarget, DivineCamera::up), camera->cameraTarget)*camera->cameraSpeed * deltaTime;
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        {
            *viewAngleX += 10 * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            *viewAngleX -= 10 * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        {
            *viewAngleY += 10 * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            *viewAngleY -= 10 * deltaTime;
        }
        
        std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
    }

}