#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"
#include "DivineCamera.h"

namespace DivineObject
{
    static bool PolygonView = false;

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
        private:
            DivineMath::vec3 position = {0.0f, 0.0f, 0.0f};
            DivineMath::vec3 rotation = {0.0f, 0.0f, 0.0f};
            DivineMath::vec3 scale = {1.0f, 1.0f, 1.0f};
        
            unsigned int VBO, VAO, texture;
        public:
            float mixPercent = 0.0f;
            DivineMath::mat4 modelMat;
            std::vector<float> data;
            Object();
            Object(std::string object_filepath, GLuint DRAW_MODE);
            ~Object();
            GLuint load_object(std::string object_filepath, GLuint DRAW_MODE);
            GLuint load_texture(std::string texture_filepath);
            void draw_object(GLFWwindow* window, GLuint shader);

            void UpdateModelMatrix();
            
            void Translate(const DivineMath::vec3& translation);
            void Rotate(const DivineMath::vec3& axis);
            void Scale(const DivineMath::vec3& scale);
    };

    void TogglePolygonMode();
}