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
    DivineMath::mat4 DivineCamera::Camera::lookAt(DivineMath::vec3 pos, DivineMath::vec3 target, DivineMath::vec3 up)
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
    void DivineCamera::Camera::cameraUpdage()
    {
        DivineMath::vec3 direction;
        direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        direction.y = sin(glm::radians(cameraPitch));
        direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        this->cameraTarget = DivineMath::normalize(direction);
    }

    void Camera::cameraMovement(GLFWwindow *window, DivineCamera::Camera *camera, GLfloat deltaTime)
    {
        float rotationSpeed = 45;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera->cameraPos -= camera->cameraTarget*camera->cameraSpeed * deltaTime;
            //camera->cameraPos -= DivineMath::vec3(camera->cameraTarget.x, 0.0f, camera->cameraTarget.z).normalize()*camera->cameraSpeed * deltaTime;
            //std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera->cameraPos += DivineMath::cross(camera->cameraTarget, DivineCamera::up).normalize()*camera->cameraSpeed * deltaTime;
            //std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            camera->cameraPos += camera->cameraTarget*camera->cameraSpeed * deltaTime;
            //std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera->cameraPos -= DivineMath::cross(camera->cameraTarget, DivineCamera::up).normalize()*camera->cameraSpeed * deltaTime;

            //std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        {
            camera->cameraPos += DivineMath::cross(DivineMath::cross(camera->cameraTarget, DivineCamera::up), camera->cameraTarget).normalize()*camera->cameraSpeed * deltaTime;
            //std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            camera->cameraPos -= DivineMath::cross(DivineMath::cross(camera->cameraTarget, DivineCamera::up), camera->cameraTarget).normalize()*camera->cameraSpeed * deltaTime;
            //std::cout<<camera->cameraPos.x<<" "<<camera->cameraPos.y<<" "<<camera->cameraPos.z<<std::endl;
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            camera->cameraPitch -= camera->cameraRotationSpeed * deltaTime;
            camera->cameraUpdage();
            std::cout<<camera->cameraTarget.x<<" "<<camera->cameraTarget.y<<" "<<camera->cameraTarget.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            camera->cameraPitch += camera->cameraRotationSpeed * deltaTime;
            camera->cameraUpdage();
            std::cout<<camera->cameraTarget.x<<" "<<camera->cameraTarget.y<<" "<<camera->cameraTarget.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            camera->cameraYaw += camera->cameraRotationSpeed * deltaTime;
            camera->cameraUpdage();
            std::cout<<camera->cameraTarget.x<<" "<<camera->cameraTarget.y<<" "<<camera->cameraTarget.z<<std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            camera->cameraYaw -= camera->cameraRotationSpeed * deltaTime;
            camera->cameraUpdage();
            std::cout<<camera->cameraTarget.x<<" "<<camera->cameraTarget.y<<" "<<camera->cameraTarget.z<<std::endl;
        }
    }
}