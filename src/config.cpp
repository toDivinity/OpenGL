#include "config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace engine
{
    bool polygonMode = false;
}

unsigned int make_shader (const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::vector <unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for(unsigned int shaderModule : modules)
    {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    
    if(!success)
    {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader Linking error:\n" << errorLog << std::endl;   
    }
    else std::cout<< "Shaders linked successfuly\n";

    for(unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }
    return shader;
}

unsigned int make_module (const std::string& filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while(std::getline(file,line))
    {
        bufferedLines<<line<<"\n";
    }

    std::string shadersSource = bufferedLines.str();
    const char* shadersSrc = shadersSource.c_str();
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shadersSrc, NULL);
    glCompileShader(shaderModule);
    
    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;   
    }
    else std::cout <<  module_type << " Shaders loaded successfuly\n";

    return shaderModule;
}

Object::Object()
{
}

Object::Object(std::string object_filepath) 
{
    load_object(object_filepath);
}

Object::~Object()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

int Object::load_object(std::string object_filepath)
{
    std::ifstream object_datafile(object_filepath);
    if (!object_datafile.is_open()) {
        return -1;
    }

    std::string line;
    std::stringstream bufferedLines;
    while(std::getline(object_datafile, line))
    {
        bufferedLines << line << "\n";
    }

    float value;
    while(bufferedLines >> value)
    {
        data.push_back(value);
    }

    if(data.empty() || data.size() % 3 != 0) {
        return -2;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);  
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    return 0;
}

void Object::draw_object()
{
    if(VAO == 0) return;
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (int)data.size()/3);
    glBindVertexArray(0);
}

int Object::load_texture(std::string texture_filepath) {
    if (texture_filepath.empty()) {
        std::cerr << "Texture filepath is empty!" << std::endl;
        return -1;
    }

    if (texture != 0) {
        glDeleteTextures(1, &texture);
    }

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *textureData = stbi_load(texture_filepath.c_str(), &width, &height, &nrChannels, 0);
    
    if (!textureData) {
        std::cerr << "Failed to load texture: " << texture_filepath << std::endl;
        return -1;
    }

    GLenum format = GL_RGB;
    if (nrChannels == 1) format = GL_RED;
    else if (nrChannels == 3) format = GL_RGB;
    else if (nrChannels == 4) format = GL_RGBA;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(textureData);

    return 0;
}


void switchPolygonMode()
{
    if(!engine::polygonMode)
    {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    engine::polygonMode = true;
    }
    else 
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        engine::polygonMode = false;
    }
}

#undef STB_IMAGE_IMPLEMENTATION