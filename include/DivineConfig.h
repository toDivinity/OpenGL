#pragma once
#include <glad/glad.h>
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
unsigned int make_shader (const std::string& vertex_filepath, const std::string& fragment_filepath);
unsigned int make_module (const std::string& filepath, unsigned int module_type);

}