#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"

namespace DivineCamera
{
    static DivineMath::vec3 up (0.0f, 1.0f, 0.0f);
    class Camera
    {
        public:
            float cameraYaw = 90.0f; 
            float cameraPitch = 0.0f;
            float cameraRotationSpeed;
            float cameraSpeed;
            DivineMath::vec3 cameraPos;
            DivineMath::vec3 cameraTarget;
            Camera();
            ~Camera();
            DivineMath::mat4 lookAt(DivineMath::vec3 cameraPos, DivineMath::vec3 cameraTarget, DivineMath::vec3 up);
            void cameraUpdage();
    };
}