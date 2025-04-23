#include "DivineObject.h"
#include "stb_image.h"

DivineObject::Object::Object()
{

}

DivineObject::Object::Object(std::string object_filepath) 
{
    load_object(object_filepath);
}

DivineObject::Object::~Object()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

GLuint DivineObject::Object::load_object(std::string object_filepath)
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
GLuint DivineObject::Object::load_obj(std::string object_filepath)
    {
        std::vector<DivineMath::vec3> temp_vertices;
        std::vector<DivineMath::vec2> temp_uvs;
        std::vector<DivineMath::vec3> temp_normals;
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

        std::ifstream file(object_filepath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open OBJ file: " << object_filepath << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.substr(0, 2) == "v ")
            {
                std::istringstream iss(line.substr(2));
                DivineMath::vec3 vertex;
                iss >> vertex.x >> vertex.y >> vertex.z;
                temp_vertices.push_back(vertex);
            }
            else if (line.substr(0, 3) == "vt ")
            {
                std::istringstream iss(line.substr(3));
                DivineMath::vec2 uv;
                iss >> uv.x >> uv.y;
                temp_uvs.push_back(uv);
            }
            else if (line.substr(0, 3) == "vn ")
            {
                std::istringstream iss(line.substr(3));
                DivineMath::vec3 normal;
                iss >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            }
            else if (line.substr(0, 2) == "f ")
            {
                std::istringstream iss(line.substr(2));
                std::string vertexStr;
                unsigned int vertexIndex, uvIndex, normalIndex;
                char slash;
                
                while (iss >> vertexIndex >> slash >> uvIndex >> slash >> normalIndex)
                {
                    vertexIndices.push_back(vertexIndex);
                    uvIndices.push_back(uvIndex);
                    normalIndices.push_back(normalIndex);
                }
            }
        }
        file.close();

        // Обработка индексов и заполнение vertices
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            DivineMath::vec4 vertex;
            
            // OBJ индексы начинаются с 1, поэтому вычитаем 1
            DivineMath::vec3 v = temp_vertices[vertexIndices[i] - 1];
            vertex.x = v.x;
            vertex.y = v.y;
            vertex.z = v.z;
            vertex.w = 1.0f; // homogeneous coordinate
            
            vertices.push_back(vertex);
        }

        // Генерация VAO и VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DivineMath::vec4), &vertices[0], GL_STATIC_DRAW);

        // Установка атрибутов вершины
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(DivineMath::vec4), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return VAO;
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