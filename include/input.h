#pragma once
#include <config.h>

bool mousePosOnClickRelease(GLFWwindow* window, double xPos, double yPos);
bool mousePosOnClickPress(GLFWwindow* window, double* xPos, double* yPos);
void processInput(GLFWwindow *window);