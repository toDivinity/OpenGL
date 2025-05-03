#pragma once
#include "DivineConfig.h"
#include "DivineCamera.h"

namespace DivineInput
{
    bool mousePosOnClickRelease(GLFWwindow* window, double xPos, double yPos);
    bool mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos);
}