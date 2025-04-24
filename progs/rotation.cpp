#include "rotation.h"

int rotation()
{
    GLuint WIDTH = 800, HEIGHT = 800 ;
    if(!glfwInit())
    {
        std::cerr<<"GLFW initialization failed\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,  "rotation", NULL, NULL);

    if(!window)
    {
        std::cerr<<"window creation failed\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "GLAD initialization failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLFWimage icons[1];
    icons[0].pixels = stbi_load("../../resources/NEicon.png", &icons[0].width, &icons[0].height, 0, 4);
    if (icons[0].pixels) {
        glfwSetWindowIcon(window, 1, icons);
        stbi_image_free(icons[0].pixels);
    }

    GLuint program = DivineEngine::make_shader(
        "../../shaders/rotationShader/rotationVertex.glsl",
        "../../shaders/rotationShader/rotationFragments.glsl"
    );

    GLuint staticShader = DivineEngine::make_shader(
        "../../shaders/rotationShader/staticVertex.glsl",
        "../../shaders/rotationShader/staticFragments.glsl"
    );
    glfwSetKeyCallback(window, key_callback);

    DivineObject::Object NElf;
    NElf.load_object("../../resources/Object.txt", GL_DYNAMIC_DRAW);
    NElf.load_texture("../../resources/NEicon.png");

    DivineObject::Object Ground;
    Ground.load_object("../../resources/ground.txt", GL_STATIC_DRAW);
    Ground.load_texture("../../resources/grass.png");
    
    GLuint mixPercentLocation = glGetUniformLocation(program, "mixPercent");

    GLuint modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");

    GLuint staticModelMatrixLocation = glGetUniformLocation(staticShader, "modelMatrix");
    GLuint staticViewMatrixLocation = glGetUniformLocation(staticShader, "viewMatrix");
    GLuint staticProjectionMatrixLocation = glGetUniformLocation(staticShader, "projectionMatrix");

    float angle = 0;
    DivineMath::mat4 modelMat;
    DivineMath::mat4 viewMat;
    DivineMath::mat4 projectionMat = DivineMath::create_projection_matrix((float)glm::radians(90.0f), WIDTH/HEIGHT, 0.1f, 10.0f);

    //start camera pos
    float x = 0, y = 0, z = -1.0;
    
    glViewport(0, 0, WIDTH, HEIGHT );
    while(!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            z+=0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            x+=0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            z-=0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            x-=0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        {
            y-=0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            y+=0.001f;
        }

        glClearColor((cos(glfwGetTime())/3)+0.5f, (cos(glfwGetTime())/3)+0.5f, (cos(glfwGetTime())/3)+0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(staticShader);
        modelMat =  DivineMath::create_scale_matrix(DivineMath::vec3(5.0f, 5.0f, 1.0f))*DivineMath::create_x_rotation_matrix(90);
        viewMat =   DivineMath::create_translation_matrix(DivineMath::vec3(x, y, z));
        
        glUniformMatrix4fv(staticModelMatrixLocation, 1, GL_FALSE, modelMat.data);
        glUniformMatrix4fv(staticViewMatrixLocation, 1, GL_FALSE, viewMat.data);
        glUniformMatrix4fv(staticProjectionMatrixLocation, 1, GL_FALSE, projectionMat.data);
        Ground.draw_object();

        glUseProgram(program);        
        glUniform1f(mixPercentLocation, (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f);
        angle+=0.01f;
        modelMat =  DivineMath::create_scale_matrix(DivineMath::vec3(0.5f, 0.5f, 0.5f))*
                    DivineMath::create_z_rotation_matrix(angle)*  
                    DivineMath::create_y_rotation_matrix(0) *
                    DivineMath::create_x_rotation_matrix(angle);

        viewMat =   DivineMath::create_translation_matrix(DivineMath::vec3(x, y, z));

        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, modelMat.data);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMat.data);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMat.data);
        NElf.draw_object();

       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glDeleteProgram(staticShader);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) 
    {
        DivineObject::switchPolygonMode();
    }
}