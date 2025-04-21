#include "rotation.h"

int rotation()
{
    if(!glfwInit())
    {
        std::cerr<<"GLFW initialization failed\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "Cube", NULL, NULL);

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

    unsigned int program = make_shader(
        "../../shaders/mainVertex.glsl",
        "../../shaders/mainFragments.glsl"
    );

    glfwSetKeyCallback(window, key_callback);

    Object NElf;

    glUseProgram(program);

    int matrix = glGetUniformLocation(program, "transform");

    vec3 transformVec ={1, 0, 0};
    float angle = 0;
    mat4 transformMat;
    int mixPercent = glGetUniformLocation(program, "mixPercent");

    NElf.load_object("../../resources/Object.txt");
    NElf.load_texture("../../resources/NEicon.png");
    glClearColor(1.0f, 0.98f, 0.92f, 1.0f);
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glViewport(0, 0, 800, 800);
        
        glUniform1f(mixPercent, (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f);

        angle+=0.01f;
        transformMat = create_z_rotate(angle);
        glUniformMatrix4fv(matrix, 1, GL_FALSE, transformMat.data);
        NElf.draw_object();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
    {
        switchPolygonMode();
    }
}

#undef STB_IMAGE_IMPLEMENTATION