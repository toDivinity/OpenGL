#include "DivineObject.h"
#include "stb_image.h"
namespace DivineObject
{
    DivineObject::Object::Object()
    {

    }

    DivineObject::Object::Object(std::string object_filepath, GLuint DRAW_MODE) 
    {
        load_object(object_filepath, DRAW_MODE);
    }

    DivineObject::Object::~Object()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    GLuint DivineObject::Object::load_object(std::string object_filepath, GLuint DRAW_MODE )
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
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), DRAW_MODE);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);  
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return 0;
    }

    GLuint DivineObject::Object::load_texture(std::string texture_filepath) {
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


    void DivineObject::Object::draw_object()
    {
        if(VAO == 0) return;
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, (int)data.size()/3);
        glBindVertexArray(0);
    }

    void DivineObject::switchPolygonMode()
    {
        if(!DivineObject::PolygonView)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            DivineObject::PolygonView = true;
        }
        else 
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            DivineObject::PolygonView = false;
        }
    }

    DivineObject::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }

    void DivineObject::Mesh::setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                    &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }  
}