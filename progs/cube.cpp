#include "cube.h"
#include "stb_image.h"

int cube()
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

    Object cube;
    float i = 1.0f;
    float j = 1.0f;
    float k = 1.0f;

    glUseProgram(program);
    int vertexTransformationLocation = glGetUniformLocation(program, "transformation");
    float mixPercent = glGetUniformLocation(program, "mixPercent");

    cube.load_object("../../resources/myCube.txt");
    cube.load_texture("../../resources/NEicon.png");
    glClearColor(1.0f, 0.98f, 0.92f, 1.0f);
    
    while(!glfwWindowShouldClose(window))
    {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) j+=0.001f;
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) j-=0.001f;
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) i+=0.001f;
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) i-=0.001f;
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glUniform1f(mixPercent, (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f);
        glUniform4f(vertexTransformationLocation, i, j, k, 1.0f);
        
        glViewport(0, 0, 100, 100);
        cube.draw_object();
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