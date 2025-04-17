#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <thread>


unsigned int make_shader (const std::string& vertex_filepath, const std::string& fragment_filepath);
unsigned int make_module (const std::string& filepath, unsigned int module_type);

void switchPolygonMode();

class Object
{
    public:
    std::vector<float> data;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int texture;
    Object();
    Object(std::string object_filepath);
    ~Object();
    int load_object(std::string object_filepath);
    int load_texture(std::string texture_filepath);
    void draw_object();
};