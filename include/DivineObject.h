#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"

namespace DivineObject
{
    static bool PolygonView = false;
    class Object
    {
        public:
        std::vector<DivineMath::vec4> vertices;
        std::vector<float> data;
        unsigned int VBO;
        unsigned int VAO;
        unsigned int texture;
        Object();
        Object(std::string object_filepath, GLuint DRAW_MODE);
        ~Object();
        GLuint load_object(std::string object_filepath, GLuint DRAW_MODE);
        GLuint load_obj(std::string object_filepath);
        GLuint load_texture(std::string texture_filepath);
        void move_object(DivineMath::vec3 moveVec);
        void draw_object();
    };

    void switchPolygonMode();
}