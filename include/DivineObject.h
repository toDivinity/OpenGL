#pragma once
#include "DivineConfig.h"
#include "DivineMath.h"

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

    class Mesh 
    {
    public:
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw();
    private:

        unsigned int VAO, VBO, EBO;

        void setupMesh();
    };  

    class Object
    {
        public:
        std::vector<float> data;
        unsigned int VBO;
        unsigned int VAO;
        unsigned int texture;
        Object();
        Object(std::string object_filepath, GLuint DRAW_MODE);
        ~Object();
        GLuint load_object(std::string object_filepath, GLuint DRAW_MODE);
        GLuint load_texture(std::string texture_filepath);
        void draw_object();
    };
    
    void switchPolygonMode();
}