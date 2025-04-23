#pragma once
#include <DivineConfig.h>
namespace DivineInput
{
bool mousePosOnClickRelease(GLFWwindow* window, double xPos, double yPos);
bool mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos);
void processInput(GLFWwindow *window);
}