#include "scene.h"
#include "scene_input.hpp"

GLint Scene3d()
{
    GLFWwindow* window = DivineEngine::createWindow(WIDTH, HEIGHT, "3D Scene");

    DivineEngine::setWindowIcon(window, "resources/NEicon.png");
    
    GLFWcursor* cursor = nullptr;
    DivineEngine::setCursorIcon(window, cursor, "resources/nightelf.png");

    GLuint mainShader = DivineEngine::make_shader(
        "shaders/mainVertex.glsl",
        "shaders/mainFragment.glsl"
    );

    glfwSetWindowUserPointer(window, &DivineCamera::mainCamera);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    tinyobj::attrib_t attrib;                // Хранит вершины, нормали, UV-координаты
    std::vector<tinyobj::shape_t> shapes;    // Информация о мешах (подобъектах)
    std::vector<tinyobj::material_t> materials;  // Материалы (необязательно)
    std::string warn, err;                   // Предупреждения и ошибки

    // Загрузка модели
    bool success = tinyobj::LoadObj(
        &attrib, &shapes, &materials,
        &warn, &err,
        "../../resources/tyanka.obj"  // Путь к файлу
    );

    if (!warn.empty()) std::cout << "WARN: " << warn << std::endl;
    if (!err.empty()) std::cerr << "ERR: " << err << std::endl;
    if (!success) {
        std::cerr << "Failed to load model!" << std::endl;
    }

    DivineObject::Object tyanka;
    tyanka.data = attrib.GetVertices();

    DivineObject::Object NElf;
    NElf.load_object("resources/Object.txt", GL_DYNAMIC_DRAW);
    NElf.load_texture("resources/NEicon.png");
    float angle = 0;

    DivineObject::Object Ground;
    Ground.load_object("resources/ground.txt", GL_DYNAMIC_DRAW);
    Ground.load_texture("resources/grass.png");
    Ground.modelMat = DivineMath::create_x_rotation_matrix(90)*DivineMath::create_scale_matrix(DivineMath::vec3(10.0f, 1.0f, 10.0f));

    DivineObject::Object CoordinateSystem;
    CoordinateSystem.load_object("resources/CoordinateSystem.txt", GL_DYNAMIC_DRAW);
    CoordinateSystem.mixPercent = 0.8f;
    CoordinateSystem.modelMat = DivineMath::create_scale_matrix(DivineMath::vec3(10.0f, 10.0f, 10.0f));

    while(!glfwWindowShouldClose(window))
    {
        float deltaTime = DivineEngine::getDeltaTime();
        DivineCamera::currentCamera->CameraMovement(window, deltaTime);

        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);

        DivineMath::mat4 projection = DivineMath::create_projection_matrix(
            (float)glm::radians(FOV), 
            (GLfloat)WIDTH/(GLfloat)HEIGHT, 
            0.1f, 
            100.0f
        );
        DivineMath::mat4 view = DivineCamera::currentCamera->CreateView();
        
        float bgColor = (cos(glfwGetTime())/3)+0.5f;
        glClearColor(bgColor, bgColor, bgColor, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Ground.projectionMat = projection;
        Ground.viewMat = view;
        Ground.draw_object(window, mainShader);

        CoordinateSystem.projectionMat = projection;
        CoordinateSystem.viewMat = view;
        CoordinateSystem.draw_object(window, mainShader);

        tyanka.projectionMat = projection;
        tyanka.viewMat = view;
        tyanka.draw_object(window, mainShader);

        angle += 60.0f * deltaTime;
        NElf.mixPercent = (float)(sin(glfwGetTime()*2.5f)/2.5f)+0.5f;
        NElf.modelMat = DivineMath::create_scale_matrix(DivineMath::vec3(0.5f, 0.5f, 0.5f)) *
                DivineMath::create_z_rotation_matrix(angle) *  
                DivineMath::create_x_rotation_matrix(angle);
        NElf.projectionMat = projection;
        NElf.viewMat = view;
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