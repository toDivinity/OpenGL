#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"

namespace DivineCamera
{
    static DivineMath::vec3 up (0.0f, 1.0f, 0.0f);
    class Camera
    {
        public:            
            Camera();
            ~Camera();
            DivineMath::mat4 CreateView();
            void UpdateCameraSpeed(int key);
            void UpdateCameraAngles(GLfloat *lastX, GLfloat *lastY, bool *firstMouse, double xpos, double ypos);
            void CameraMovement(GLFWwindow *window, GLfloat deltaTime);
            void CameraUpdate();
            
            DivineMath::vec3 GetCameraTarget();
            DivineMath::vec3 GetCameraPos();
            void SetCameraPos(DivineMath::vec3);
            GLfloat GetCameraFOV();
            void SetCameraFOV(GLfloat);
        private:
            GLfloat FOV = 90.0f;
            float cameraYaw = 90.0f; 
            float cameraPitch = 0.0f;
            float cameraRotationSpeed = 60.0f;
            float cameraSpeed = 2.0f;
            DivineMath::vec3 cameraPos = DivineMath::vec3(0.0f, 0.0f, 0.0f);
            DivineMath::vec3 cameraTarget = DivineMath::vec3(0.0f, 0.0f, 1.0f);
            DivineMath::mat4 LookAt(DivineMath::vec3 cameraPos, DivineMath::vec3 cameraTarget, DivineMath::vec3 up);
    };

    extern Camera mainCamera;
    extern Camera* currentCamera;
    void makeCameraCurrent(Camera*);
}