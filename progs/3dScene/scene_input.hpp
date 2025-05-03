#include "scene.h"

int WIDTH = 1200, HEIGHT = 1000;
GLfloat lastX = (float)WIDTH/2, lastY = (float)HEIGHT/2;
GLfloat savedLastX = 0, savedLastY = 0;
bool firstMouse = true;
bool cursorWasVisible = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
    {
        static bool isFullscreen = false;
        static int savedWidth = WIDTH;
        static int savedHeight = HEIGHT;
        static int savedPosX, savedPosY;
        
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        
        if (!isFullscreen)
        {
            // Сохраняем текущие размеры и позицию окна
            glfwGetWindowPos(window, &savedPosX, &savedPosY);
            savedWidth = WIDTH;
            savedHeight = HEIGHT;
            
            // Переключаем в полноэкранный режим
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            // Возвращаем оконный режим с предыдущими размерами и позицией
            glfwSetWindowMonitor(window, NULL, savedPosX, savedPosY, savedWidth, savedHeight, 0);
        }
        
        isFullscreen = !isFullscreen;
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) 
    {
        DivineObject::switchPolygonMode();
    }
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, true);
    }
    
    if ((key == GLFW_KEY_KP_ADD || key == GLFW_KEY_KP_SUBTRACT) && action == GLFW_PRESS) {
        DivineCamera::Camera* camera = static_cast<DivineCamera::Camera*>(glfwGetWindowUserPointer(window));
        camera->UpdateCameraSpeed(key);
    }
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_3 && action == GLFW_PRESS && DivineObject::CursorView==false) 
    {
        // Сохраняем последнюю позицию перед переключением в видимый режим
        savedLastX = lastX;
        savedLastY = lastY;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        DivineObject::CursorView = true;
        cursorWasVisible = true;
    }

    else if(button == GLFW_MOUSE_BUTTON_3 && action == GLFW_PRESS && DivineObject::CursorView==true)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        DivineObject::CursorView = false;
        
        // Восстанавливаем последнюю позицию мыши из сохраненных значений
        if(cursorWasVisible)
        {
            lastX = savedLastX;
            lastY = savedLastY;
            firstMouse = true; // Это заставит курсор callback сброситься при следующем движении
            cursorWasVisible = false;
        }
    }
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (DivineObject::CursorView == false)
    {
        DivineCamera::Camera* camera = static_cast<DivineCamera::Camera*>(glfwGetWindowUserPointer(window));
        camera->UpdateCameraAngles(&lastX, &lastY, &firstMouse, xpos, ypos);
        // if(firstMouse)
        // {
        //     lastX = (float)xpos;
        //     lastY = (float)ypos;
        //     firstMouse = false;
        //     return; // Пропускаем первый кадр, чтобы избежать резкого скачка
        // }

        // GLfloat xoffset = float (xpos - lastX);
        // GLfloat yoffset = float (lastY - ypos); // Обратный знак, так как y-координаты идут сверху вниз
        // lastX = (float)xpos;
        // lastY = (float)ypos;

        // const GLfloat sensitivity = 0.1f;
        // xoffset *= sensitivity;
        // yoffset *= sensitivity;

        // camera->cameraYaw += xoffset;
        // camera->cameraPitch -= yoffset;

        // if(camera->cameraPitch > 89.0f)
        //     camera->cameraPitch = 89.0f;
        // if(camera->cameraPitch < -89.0f)
        //     camera->cameraPitch = -89.0f;

        // DivineMath::vec3 front;
        // front.x = cos(glm::radians(camera->cameraYaw)) * cos(glm::radians(camera->cameraPitch));
        // front.y = sin(glm::radians(camera->cameraPitch));
        // front.z = sin(glm::radians(camera->cameraYaw)) * cos(glm::radians(camera->cameraPitch));
        // camera->cameraTarget = DivineMath::normalize(front);
    }
}