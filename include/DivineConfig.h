#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <thread>
#include <utility>

namespace DivineEngine 
{
#ifdef WIN32
static std::string sourceDir = "../../";
#else
static std::string sourceDir = "../";
#endif

unsigned int make_shader (const std::string& vertex_filepath, const std::string& fragment_filepath);
unsigned int make_module (const std::string& filepath, unsigned int module_type);

static bool CursorView = false;

GLFWwindow* createWindow(int width, int height, const char* title);
float getDeltaTime();
void setWindowIcon(GLFWwindow* window, std::string filepath);
void setCursorIcon(GLFWwindow* window, GLFWcursor*& cursor, std::string filepath);
}