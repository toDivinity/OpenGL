#include "scene.h"
#include "scene_input.hpp"

GLint Scene3d()
{
    
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

    DivineEngine::setWindowIcon(window, "resources/NEicon.png");
    
    GLFWcursor* cursor;
    DivineEngine::setCursorIcon(window, cursor, "resources/nightelf.png");

    GLuint mainShader = DivineEngine::make_shader(
        "shaders/mainVertex.glsl",
        "shaders/mainFragment.glsl"
    );

    GLuint UIshader = DivineEngine::make_shader(
        "shaders/UI_vertex_shader.glsl",
        "shaders/UI_fragment_shader.glsl"
    );
    
    DivineCamera::Camera camera;

    glfwSetWindowUserPointer(window, &camera);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    DivineObject::Object NElf;
    NElf.load_object("resources/Object.txt", GL_DYNAMIC_DRAW);
    NElf.load_texture("resources/NEicon.png");

    DivineObject::Object Ground;
    Ground.load_object("resources/ground.txt", GL_DYNAMIC_DRAW);
    Ground.load_texture("resources/grass.png");

    DivineObject::Object CoordinateSystem;
    CoordinateSystem.load_object("resources/CoordinateSystem.txt", GL_DYNAMIC_DRAW);

    DivineObject::Object UI;
    UI.load_object("resources/UI.txt", GL_STATIC_DRAW);
    UI.load_texture("resources/AutumnNE_UI.png");
    
    GLuint mixPercentLocation = glGetUniformLocation(mainShader, "mixPercent");

    GLuint modelMatrixLocation = glGetUniformLocation(mainShader, "modelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(mainShader, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(mainShader, "projectionMatrix");

    float angle = 0;
    DivineMath::mat4 modelMat;
    DivineMath::mat4 viewMat;
    DivineMath::mat4 projectionMat;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while(!glfwWindowShouldClose(window))
    {
        float deltaTime = DivineEngine::getDeltaTime(&deltaTime);

        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT );

        projectionMat = DivineMath::create_projection_matrix((float)glm::radians(90.0f), (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);

        glClearColor((cos(glfwGetTime())/3)+0.5f, (cos(glfwGetTime())/3)+0.5f, (cos(glfwGetTime())/3)+0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.cameraMovement(window, &camera, deltaTime);
        
        //viewMat = DivineMath::create_x_rotation_matrix(viewAngle)*DivineMath::create_translation_matrix(DivineMath::vec3(camera.cameraPos));
        viewMat = camera.lookAt(camera.cameraPos, camera.cameraTarget, DivineCamera::up);

        glUseProgram(mainShader);

        modelMat = DivineMath::create_x_rotation_matrix(90)*DivineMath::create_scale_matrix(DivineMath::vec3(10.0f, 1.0f, 10.0f));
        glUniform1f(mixPercentLocation, 0.0f);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, modelMat.data);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMat.data);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMat.data);
        Ground.draw_object();

        modelMat = DivineMath::create_scale_matrix(DivineMath::vec3(10.0f, 10.0f, 10.0f));
        glUniform1f(mixPercentLocation, 1.0f);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, modelMat.data);
        CoordinateSystem.draw_object();
      
        glUniform1f(mixPercentLocation, (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f);
        angle+=60.0f*deltaTime;
        modelMat =  DivineMath::create_scale_matrix(DivineMath::vec3(0.5f, 0.5f, 0.5f))*
                    DivineMath::create_z_rotation_matrix(angle)*  
                    DivineMath::create_y_rotation_matrix(0) *
                    DivineMath::create_x_rotation_matrix(angle);

        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, modelMat.data);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMat.data);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMat.data);
        NElf.draw_object();

        glUseProgram(UIshader);
        modelMat =  DivineMath::create_scale_matrix(DivineMath::vec3(1.0f, 1.0f, 1.0f)) *
                    DivineMath::create_translation_matrix(DivineMath::vec3 (0.0f, 0.0f, -1.0f));

        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, modelMat.data);
        UI.draw_object();

       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if(cursor)
    {
        glfwDestroyCursor(cursor);
        std::cout<<"cursor destroyed";
    }

    glDeleteProgram(mainShader);
    glfwTerminate();
    return 0;
}