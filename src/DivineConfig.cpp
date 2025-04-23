#include "DivineConfig.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace DivineEngine
{
    GLuint make_shader (const std::string& vertex_filepath, const std::string& fragment_filepath)
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
    GLuint make_module (const std::string& filepath, unsigned int module_type)


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

}