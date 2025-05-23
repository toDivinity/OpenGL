#include "DivineConfig.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace DivineEngine
{
    GLuint mainShader;
    GLuint* currentShader = &mainShader;
    GLFWwindow* currentWindow = nullptr;

    GLFWwindow* createWindow(int width, int height, const char* title)
    {
        if(!glfwInit())
        {
            std::cerr << "GLFW initialization failed\n";
            return nullptr;
        }

        GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
        if(!window)
        {
            std::cerr << "window creation failed\n";
            glfwTerminate();
            return nullptr;
        }

        setWindowCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "GLAD initialization failed" << std::endl;
            glfwTerminate();
            return nullptr;
        }
            
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mainShader = DivineEngine::make_shader(
            "shaders/mainVertex.glsl",
            "shaders/mainFragment.glsl"
        );

        return window;
    }

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

        file.open(sourceDir + filepath);
        if(!file)
        {
            std::cerr<<"could not open shader file"<<std::endl;
            return -1;
        }
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
        else std::cout << filepath << " Shaders loaded successfuly\n";

        return shaderModule;
    }

    static float lastFrame;
    float getDeltaTime()
    {
        GLfloat currentFrame = (float)glfwGetTime();
        GLfloat deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        return deltaTime;
    }

    
    void setWindowIcon(GLFWwindow* window, std::string filepath)
    {
        GLFWimage icon[1];
        icon[0].pixels = stbi_load((sourceDir + filepath).c_str(), &icon[0].width, &icon[0].height, 0, 4);
        if (icon[0].pixels) {
            glfwSetWindowIcon(window, 1, icon);
            stbi_image_free(icon[0].pixels);
        }
    }

    void setCursorIcon(GLFWwindow* window, GLFWcursor*& cursor, std::string filepath)
    {
        GLFWimage cursorImage;
        cursorImage.pixels = stbi_load((sourceDir + filepath).c_str(), &cursorImage.width, &cursorImage.height, 0, 4);
        if (cursorImage.pixels) 
        {
            cursor = glfwCreateCursor(&cursorImage, 0, 0);  // hotspot x and y are 0
            if (cursor) 
            {
                glfwSetCursor(window, cursor);
            }
            stbi_image_free(cursorImage.pixels);
        }
    }

    std::vector<std::string> split(const std::string line, const std::string delimiter) 
    {
        std::vector<std::string> result;
        if (line.empty()) return result;
        if (delimiter.empty()) {
            result.push_back(line);
            return result;
        }

        size_t start = 0;
        size_t end = line.find(delimiter);
        
        while (end != std::string::npos) {
            result.push_back(line.substr(start, end - start));
            start = end + delimiter.length();
            end = line.find(delimiter, start);
        }
        
        result.push_back(line.substr(start));
        
        return result;
    }
    
    void setShaderCurrent(GLuint* shader)
    {
        currentShader = shader;
    }
    void setWindowCurrent(GLFWwindow* window)
    {
        currentWindow = window;
        glfwMakeContextCurrent(currentWindow);
    }
}