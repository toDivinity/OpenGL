#include "DivineObject.h"
#include "stb_image.h"
namespace DivineObject
{
    Object::Object()
    {
    }

    Object::Object(std::string object_filepath) 
    {
        load_object(object_filepath);
    }

    Object::Object(std::string object_filepath, std::string texture_filepath) 
    {
        load_object(object_filepath);
        load_texture(texture_filepath);
    }

    Object::~Object()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    GLuint Object::load_object(std::string object_filepath)
    {
        std::ifstream object_datafile(DivineEngine::sourceDir + object_filepath);
        if (!object_datafile.is_open()) {
            return -1;
        }

        std::vector<float> data;
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

        verticesCount=(int)data.size()/3;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_DYNAMIC_DRAW);
        
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

    GLuint Object::load_texture(std::string texture_filepath) {
        if (texture_filepath.empty()) {
            std::cerr << "Texture filepath is empty!" << std::endl;
            return -1;
        }

        if (texture != 0) {
            glDeleteTextures(1, &texture);
        }

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *textureData = stbi_load((DivineEngine::sourceDir + texture_filepath).c_str(), &width, &height, &nrChannels, 0);
        
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


    void Object::draw_object(GLFWwindow* window, GLuint shader)
    {
        if(VAO == 0) return;

        glfwMakeContextCurrent(window);
        glUseProgram(shader);

        int WIDTH, HEIGHT;
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);

        UpdateModelMatrix();

        GLuint mixPercentLocation = glGetUniformLocation(shader, "mixPercent");
        GLuint modelMatrixLocation = glGetUniformLocation(shader, "modelMatrix");
        GLuint viewMatrixLocation = glGetUniformLocation(shader, "viewMatrix");
        GLuint projectionMatrixLocation = glGetUniformLocation(shader, "projectionMatrix");

        DivineMath::mat4 view = DivineCamera::currentCamera->CreateView();
        DivineMath::mat4 projection = DivineMath::create_projection_matrix(
            DivineMath::radians(DivineCamera::currentCamera->GetCameraFOV()),
            (float)WIDTH/(float)HEIGHT,
            0.01f, 100.0f
        );

        glUniform1f(mixPercentLocation, mixPercent);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, modelMat.data);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, view.data);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projection.data);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) verticesCount);
        glBindVertexArray(0);
    }

    void Object::Translate(float x ,float y ,float z)
    {
        position = DivineMath::vec3(x, y, z);
    }

    void Object::Rotate(float x ,float y ,float z)
    {
        rotation += DivineMath::vec3(x, y, z);
    }

    void Object::Scale(float x ,float y ,float z)
    {
        scale = DivineMath::vec3(x, y, z);
    }

    void Object::UpdateModelMatrix() {
        modelMat = 
        DivineMath::create_scale_matrix(scale)*
        DivineMath::create_rotation_matrix(rotation)*
        DivineMath::create_translation_matrix(position);
    }

    void Object::load_obj_model(const std::string object_filepath)
    {
        std::vector<DivineMath::vec3> v;
        std::vector<DivineMath::vec2> vt;
        std::vector<DivineMath::vec3> vn;
        std::vector<float> vertices;

        std::ifstream file(object_filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + object_filepath);
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty()) continue;
            
            std::vector<std::string> words = DivineEngine::split(line, " ");
            if (words.empty()) continue;

            if (words[0] == "v" && words.size() >= 4) {
                v.push_back(DivineMath::readVec3(words));
            }
            else if (words[0] == "vt" && words.size() >= 3) {
                vt.push_back(DivineMath::readVec2(words));
            }
            else if (words[0] == "vn" && words.size() >= 4) {
                vn.push_back(DivineMath::readVec3(words));
            }
            else if (words[0] == "f" && words.size() >= 5) {
                read_face(words, v, vt, vn, vertices);
            }
        }
        file.close();

        verticesCount = vertices.size();
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2); 

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(1); 
        

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        std::cout << "Loaded model:" << std::endl;
        std::cout << "Vertices: " << v.size() << std::endl;
        std::cout << "TexCoords: " << vt.size() << std::endl;
        std::cout << "Normals: " << vn.size() << std::endl;
        std::cout << "vertices: " << vertices.size() << std::endl;
    }

    void Object::read_face(std::vector<std::string> words, 
        std::vector<DivineMath::vec3>& v, 
        std::vector<DivineMath::vec2>& vt, 
        std::vector<DivineMath::vec3>& vn,
        std::vector<float>& vertices)
    {
        size_t triangleCount = words.size()-3;

        for(size_t i=0; i<triangleCount; i++)
        {
            read_corner(words[1], v, vt, vn, vertices);
            read_corner(words[2+i], v, vt, vn, vertices);
            read_corner(words[3+i], v, vt, vn, vertices);
        }
    }

    void Object::read_corner(std::string description, 
        std::vector<DivineMath::vec3>& v, 
        std::vector<DivineMath::vec2>& vt, 
        std::vector<DivineMath::vec3>& vn,
        std::vector<float>& vertices)
    {
        std::vector<std::string> v_vt_vn = DivineEngine::split(description, "/");

        DivineMath::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);

        DivineMath::vec2 tex = vt[std::stol(v_vt_vn[1]) - 1];
        vertices.push_back(tex.x);
        vertices.push_back(tex.y);

        DivineMath::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
        vertices.push_back(normal.x);
        vertices.push_back(normal.y);
        vertices.push_back(normal.z);
    }

    void TogglePolygonMode()
    {
        if(!PolygonView)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            PolygonView = true;
        }
        else 
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            PolygonView = false;
        }
    }
}