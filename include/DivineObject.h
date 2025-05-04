#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"
#include "DivineCamera.h"

namespace DivineObject
{
    static bool PolygonView = false;
    static bool CursorView = false;

    struct Vertex 
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture 
    {
        unsigned int id;
        std::string type;
    };

    class Object
    {
        public:
        float mixPercent = 0.0f;
        DivineMath::mat4 modelMat, viewMat, projectionMat;
        std::vector<float> data;
        unsigned int VBO, VAO, texture;
        Object();
        Object(std::string object_filepath, GLuint DRAW_MODE);
        ~Object();
        GLuint load_object(std::string object_filepath, GLuint DRAW_MODE);
        GLuint load_texture(std::string texture_filepath);
        void draw_object(GLFWwindow* window, GLuint shader);
    };
    
    void switchPolygonMode();
}