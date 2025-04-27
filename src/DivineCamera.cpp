#include "DivineCamera.h"

namespace DivineCamera
{
    Camera::Camera()
    {
        cameraPos = DivineMath::vec3(0.0f, 0.0f, 0.0f);
        cameraTarget = DivineMath::vec3(0.0f, 0.0f, 1.0f);
        cameraRight = DivineMath::normalize(DivineMath::cross(up, cameraTarget));
        cameraUp = DivineMath::normalize(DivineMath::cross(cameraRight, cameraTarget));
    }
    Camera::~Camera()
    {

    }
}