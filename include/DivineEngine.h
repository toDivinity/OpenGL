#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"
#include "DivineCamera.h"

namespace DivineEngine
{
    static bool PolygonView = false;
    class Object
    {
        protected:
            DivineMath::vec3 position = {0.0f, 0.0f, 0.0f};
            
            DivineMath::vec3 scale = {1.0f, 1.0f, 1.0f};
        
            unsigned int VBO, VAO, texture;
            void read_face(std::vector<std::string> words, 
                            std::vector<DivineMath::vec3>& v, 
                            std::vector<DivineMath::vec2>& vt, 
                            std::vector<DivineMath::vec3>& vn,
                            std::vector<float>& vertices);

            void read_corner(std::string description, 
                std::vector<DivineMath::vec3>& v, 
                std::vector<DivineMath::vec2>& vt, 
                std::vector<DivineMath::vec3>& vn,
                std::vector<float>& vertices);

        public:
        DivineMath::vec3 rotation = {0.0f, 0.0f, 0.0f};
            size_t verticesCount;
            float mixPercent = 0.0f;
            DivineMath::mat4 modelMat;
            Object();
            Object(std::string object_filepath);
            Object(std::string object_filepath ,std::string texture_filepath);
            ~Object();
            GLuint load_object(std::string object_filepath);
            GLuint load_texture(std::string texture_filepath);
            void load_obj_model(std::string object_filepath);
            void draw_object();

            void UpdateModelMatrix();

            //equate
            void TranslateTo(float x ,float y ,float z);
            void RotateTo(float x ,float y ,float z);
            void ScaleTo(float x ,float y ,float z);
            
            //difference
            void Translate(float x ,float y ,float z);
            void Rotate(float x ,float y ,float z);
            void Scale(float x ,float y ,float z);
    }; 
    
    class Scene
    {
        public:
        Scene();
        ~Scene();
        std::vector<Object*> objects;
        void add_object(Object*);
        void draw();
    };

    void TogglePolygonMode();
}