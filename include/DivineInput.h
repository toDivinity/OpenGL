#pragma once
#include <DivineConfig.h>
#include "DivineCamera.h"
namespace DivineInput
{
void processInput(GLFWwindow *window, DivineCamera::Camera *camera, GLfloat deltaTime, float*, float*);
bool mousePosOnClickRelease(GLFWwindow* window, double xPos, double yPos);
bool mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos);
}