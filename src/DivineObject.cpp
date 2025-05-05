#include "DivineObject.h"
#include "stb_image.h"
namespace DivineObject
{
    Object::Object()
    {
    }

    Object::Object(std::string object_filepath, GLuint DRAW_MODE) 
    {
        load_object(object_filepath, DRAW_MODE);
    }

    Object::~Object()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    GLuint Object::load_object(std::string object_filepath, GLuint DRAW_MODE )
    {
        std::ifstream object_datafile(DivineEngine::sourceDir + object_filepath);
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
        glDrawArrays(GL_TRIANGLES, 0, (int)data.size()/3);
        glBindVertexArray(0);
    }

    void Object::Translate(const DivineMath::vec3& translation)
    {
        this->position += translation;
    }

    void Object::Rotate(const DivineMath::vec3& axis)
    {
        this->rotation += DivineMath::vec3(axis.x, axis.y, axis.z);
    }

    void Object::Scale(const DivineMath::vec3& scale)
    {
        this->scale = scale;
    }

    void Object::UpdateModelMatrix() {
        modelMat = 
        DivineMath::create_scale_matrix(scale)*
        DivineMath::create_rotation_matrix(rotation)*
        DivineMath::create_translation_matrix(position);
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