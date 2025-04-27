#include "DivineCamera.h"

namespace DivineCamera
{
    Camera::Camera()
    {
        cameraPos = DivineMath::vec3(0.0f, 0.0f, 3.0f);
        cameraTarget = DivineMath::vec3(0.0f, 0.0f, 1.0f);
        cameraRight = DivineMath::normalize(DivineMath::cross(up, cameraTarget));
        cameraUp = DivineMath::normalize(DivineMath::cross(cameraRight, cameraTarget));
    }
    Camera::~Camera()
    {

    }
    DivineMath::mat4 DivineCamera::Camera::lookAt(DivineMath::vec3 eye, DivineMath::vec3 center, DivineMath::vec3 up)
{
    DivineMath::vec3 D = DivineMath::normalize(center);
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
        -eye.x, -eye.y, -eye.z, 1.0f
    };

    DivineMath::mat4 result = leftMat*rightMat;

    return result;
}

}