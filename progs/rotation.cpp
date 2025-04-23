#include "rotation.h"

int rotation()
{
    if(!glfwInit())
    {
        std::cerr<<"GLFW initialization failed\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "rotation", NULL, NULL);

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
    icons[0].pixels = stbi_load("NEicon.png", &icons[0].width, &icons[0].height, 0, 4); // Используйте stb_image.h
    if (icons[0].pixels) {
        glfwSetWindowIcon(window, 1, icons);
        stbi_image_free(icons[0].pixels);
    }

    GLuint program = DivineEngine::make_shader(
        "../../shaders/rotationShader/rotationVertex.glsl",
        "../../shaders/rotationShader/rotationFragments.glsl"
    );

    glfwSetKeyCallback(window, key_callback);

    DivineObject::Object NElf;

    GLuint matrix = glGetUniformLocation(program, "transform");
    GLuint mixPercent = glGetUniformLocation(program, "mixPercent");

    float angle = 0;
    DivineMath::mat4 transformMat;

    NElf.load_object("../../resources/Object.txt");
    NElf.load_texture("../../resources/NEicon.png");
    
    float x = 0, y = 0, z = 0;
    while(!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            y-=0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            x+=0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            y+=0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            x-=0.001;
        }
        glClearColor((cos(glfwGetTime())/3)+0.5, (cos(glfwGetTime())/3)+0.5, (cos(glfwGetTime())/3)+0.5, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glViewport(0, 0, 800, 800);
        
        glUniform1f(mixPercent, (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f);

        angle+=0.01f;
        transformMat =  
                        DivineMath::create_x_rotation_matrix(angle) * 
                        DivineMath::create_z_rotation_matrix(angle) * 
                        DivineMath::create_y_rotation_matrix(angle) * 
                        DivineMath::create_translation_matrix(DivineMath::vec3(x, y, z))*
                        DivineMath::create_scale_matrix(DivineMath::vec3(0.5f, 0.5f, 0.0f));
        glUniformMatrix4fv(matrix, 1, GL_FALSE, transformMat.data);
        
        NElf.draw_object();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
    {
        DivineObject::switchPolygonMode();
    }
}