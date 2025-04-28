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
}