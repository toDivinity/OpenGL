#include "DivineCamera.h"

namespace DivineCamera
{
    Camera::Camera()
    {
        cameraRotationSpeed = 60.0f;
        cameraSpeed = 10.0f;
        cameraPos = DivineMath::vec3(0.0f, 0.0f, 3.0f);
        cameraTarget = DivineMath::vec3(0.0f, 0.0f, 1.0f);
    }
    Camera::~Camera()
    {

    }   
    DivineMath::mat4 DivineCamera::Camera::LookAt(DivineMath::vec3 pos, DivineMath::vec3 target, DivineMath::vec3 up)
    {
        DivineMath::vec3 D = DivineMath::normalize(target);
        DivineMath::vec3 R = DivineMath::normalize(DivineMath::cross(up, D));
        DivineMath::vec3 U = DivineMath::cross(D, R);

        DivineMath::mat4 leftMat =
        {
            R.x, U.x, D.x, 0.0f,
            R.y, U.y, D.y, 0.0f,
            R.z, U.z, D.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };

        DivineMath::mat4 rightMat =
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            -pos.x, -pos.y, -pos.z, 1.0f
        };

        return rightMat*leftMat;
    }
    DivineMath::mat4 Camera::CreateView()
    {
        return LookAt(cameraPos, cameraTarget, DivineCamera::up);
    }    
    void Camera::UpdateCameraSpeed(int key)
    {
        if (key == GLFW_KEY_KP_ADD) 
        {
            cameraSpeed += 5.0f;
        }
        if (key == GLFW_KEY_KP_SUBTRACT)
        {
            cameraSpeed -= 5.0f;
            if (cameraSpeed < 5.0f) cameraSpeed = 5.0f;
        }
        std::cout<<cameraSpeed<<std::endl;
    }
    void Camera::UpdateCameraAngles(GLfloat *lastX, GLfloat *lastY, bool *firstMouse, double xpos, double ypos)
    {
        if(*firstMouse)
        {
            *lastX = (float)xpos;
            *lastY = (float)ypos;
            *firstMouse = false;
            return; // Пропускаем первый кадр, чтобы избежать резкого скачка
        }
        GLfloat xoffset = float (xpos - *lastX);
        GLfloat yoffset = float (*lastY - ypos); // Обратный знак, так как y-координаты идут сверху вниз
        *lastX = (float)xpos;
        *lastY = (float)ypos;

        const GLfloat sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        cameraYaw += xoffset;
        cameraPitch -= yoffset;

        if(cameraPitch > 89.0f)
            cameraPitch = 89.0f;
        if(cameraPitch < -89.0f)
            cameraPitch = -89.0f;

        Camera::CameraUpdate();
    }
    void DivineCamera::Camera::CameraUpdate()
    {
        DivineMath::vec3 direction;
        direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        direction.y = sin(glm::radians(cameraPitch));
        direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        this->cameraTarget = DivineMath::normalize(direction);
    }
    void Camera::CameraMovement(GLFWwindow *window, GLfloat deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraPos -= cameraTarget * cameraSpeed * deltaTime;
            // cameraPos -= DivineMath::vec3( cameraTarget.x, 0.0f,  cameraTarget.z).normalize()* cameraSpeed * deltaTime;
            //std::cout<< cameraPos.x<<" "<< cameraPos.y<<" "<< cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraPos += DivineMath::cross(cameraTarget, DivineCamera::up).normalize() * cameraSpeed * deltaTime;
            //std::cout<< cameraPos.x<<" "<< cameraPos.y<<" "<< cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            cameraPos +=  cameraTarget * cameraSpeed * deltaTime;
            //std::cout<< cameraPos.x<<" "<< cameraPos.y<<" "<< cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraPos -= DivineMath::cross(cameraTarget, DivineCamera::up).normalize() * cameraSpeed * deltaTime;
            //std::cout<< cameraPos.x<<" "<< cameraPos.y<<" "<< cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        {
            cameraPos += DivineMath::cross(DivineMath::cross(cameraTarget, DivineCamera::up), cameraTarget).normalize() * cameraSpeed * deltaTime;
            //std::cout<< cameraPos.x<<" "<< cameraPos.y<<" "<< cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            cameraPos -= DivineMath::cross(DivineMath::cross(cameraTarget, DivineCamera::up), cameraTarget).normalize() * cameraSpeed * deltaTime;
            //std::cout<< cameraPos.x<<" "<< cameraPos.y<<" "<< cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            cameraPitch -= cameraRotationSpeed * deltaTime;
            CameraUpdate();
            std::cout<< cameraTarget.x<<" "<< cameraTarget.y<<" "<< cameraTarget.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            cameraPitch += cameraRotationSpeed * deltaTime;
            CameraUpdate();
            std::cout<< cameraTarget.x<<" "<< cameraTarget.y<<" "<< cameraTarget.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            cameraYaw += cameraRotationSpeed * deltaTime;
            CameraUpdate();
            std::cout<< cameraTarget.x<<" "<< cameraTarget.y<<" "<< cameraTarget.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            cameraYaw -= cameraRotationSpeed * deltaTime;
            CameraUpdate();
            std::cout<< cameraTarget.x<<" "<< cameraTarget.y<<" "<< cameraTarget.z<<std::endl;
        }
    }
}