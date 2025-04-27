#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"

namespace DivineCamera
{
    static DivineMath::vec3 up (0.0f, 1.0f, 0.0f);
    class Camera
    {
        public:
            float cameraSpeed = 1.0f;
            DivineMath::vec3 cameraPos;
            DivineMath::vec3 cameraTarget;
            DivineMath::vec3 cameraUp;
            DivineMath::vec3 cameraRight;
            Camera();
            ~Camera();
    };
}