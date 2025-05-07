#include "scene.h"
#include "scene_input.hpp"

GLint Scene3d()
{
    GLFWwindow* window = DivineEngine::createWindow(WIDTH, HEIGHT, "3D Scene");

    DivineEngine::setWindowIcon(window, "resources/NEicon.png");
    
    GLFWcursor* cursor = nullptr;
    DivineEngine::setCursorIcon(window, cursor, "resources/nightelf.png");

    DivineCamera::currentCamera->SetCameraPos(DivineMath::vec3(0.0f,0.0f,0.5f));

    GLuint mainShader = DivineEngine::make_shader(
        "shaders/mainVertex.glsl",
        "shaders/mainFragment.glsl"
    );

    double mousePosX, mousePosY;

    glfwSetWindowUserPointer(window, &DivineCamera::mainCamera);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Hero nissan;
    nissan.load_obj_model("resources/nissan.obj");
    nissan.load_texture("resources/nissan.png");
    nissan.Scale(0.1f, 0.1f, 0.1f);
    nissan.Translate(0.6f, 0.0f, 0.6f);

    DivineEngine::Object NElf("resources/Object.txt", "resources/NEicon.png");
    NElf.Scale(0.2f, 0.2f, 0.2f);
    
    DivineEngine::Object Ground("resources/ground.txt", "resources/grass.png");
    Ground.Translate(0.0f, 0.3f, 0.0f);
    Ground.Scale(2.0f, 2.0f, 1.0f);
    Ground.Rotate(90.0f, 0.0f, 0.0f);

    DivineEngine::Object CoordinateSystem("resources/CoordinateSystem.txt");
    CoordinateSystem.mixPercent = 0.8f;
    CoordinateSystem.Scale(2.0f, 2.0f, 2.0f);

    while(!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);

        float deltaTime = DivineEngine::getDeltaTime();
        DivineCamera::currentCamera->CameraMovement(window, deltaTime);

        if(DivineEngine::CursorView)
        {
        DivineInput::mousePosOnClickPress(window, &mousePosX, &mousePosY);
        }
        
        float bgColor = (float)(cos(glfwGetTime())/3)+0.5f;
        glClearColor(bgColor, bgColor, bgColor, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        nissan.movement(window, deltaTime);
        nissan.draw_object(window, mainShader);

        Ground.draw_object(window, mainShader);

        CoordinateSystem.draw_object(window, mainShader);

        NElf.mixPercent = (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f;
        NElf.Rotate(60.0f*deltaTime, 0.0f, 60.0f*deltaTime);
        NElf.draw_object(window, mainShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if(cursor)
    {
        glfwDestroyCursor(cursor);
        cursor = nullptr;
    }

    glDeleteProgram(mainShader);
    glfwTerminate();
    return 0;
}