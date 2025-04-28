#include "rotation.h"

int rotation()
{
    int WIDTH = 800, HEIGHT = 800;
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    if(!glfwInit())
    {
        std::cerr<<"GLFW initialization failed\n";
        return 1;
    }
    //glfwGetPrimaryMonitor() - fullscreen
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

    GLFWimage icon[1];
    icon[0].pixels = stbi_load("../../resources/NEicon.png", &icon[0].width, &icon[0].height, 0, 4);
    if (icon[0].pixels) {
        glfwSetWindowIcon(window, 1, icon);
        stbi_image_free(icon[0].pixels);
    }

    GLFWcursor* cursor;
    GLFWimage cursorImage;
    cursorImage.pixels = stbi_load("../../resources/nightelf.png", &cursorImage.width, &cursorImage.height, 0, 4);
    if (cursorImage.pixels) 
    {
        cursor = glfwCreateCursor(&cursorImage, 0, 0);  // hotspot x and y are 0
        if (cursor) 
        {
            glfwSetCursor(window, cursor);
        }
        stbi_image_free(cursorImage.pixels);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    DivineObject::Object NElf;
    NElf.load_object("../../resources/Object.txt", GL_DYNAMIC_DRAW);
    NElf.load_texture("../../resources/NEicon.png");

    DivineObject::Object Ground;
    Ground.load_object("../../resources/ground.txt", GL_DYNAMIC_DRAW);
    Ground.load_texture("../../resources/grass.png");

    DivineObject::Object CoordinateSystem;
    CoordinateSystem.load_object("../../resources/CoordinateSystem.txt", GL_DYNAMIC_DRAW);
    
    GLuint mixPercentLocation = glGetUniformLocation(program, "mixPercent");

    GLuint modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");

    GLuint staticModelMatrixLocation = glGetUniformLocation(staticShader, "modelMatrix");
    GLuint staticViewMatrixLocation = glGetUniformLocation(staticShader, "viewMatrix");
    GLuint staticProjectionMatrixLocation = glGetUniformLocation(staticShader, "projectionMatrix");

    float angle = 0;
    float viewAngleX = 0;
    float viewAngleY = 0;
    DivineMath::mat4 modelMat;
    DivineMath::mat4 viewMat;
    DivineMath::mat4 projectionMat;

    //start camera pos
    DivineCamera::Camera camera;
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT );

        projectionMat = DivineMath::create_projection_matrix((float)glm::radians(90.0f), (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);

        glClearColor((cos(glfwGetTime())/3)+0.5f, (cos(glfwGetTime())/3)+0.5f, (cos(glfwGetTime())/3)+0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DivineInput::processInput(window, &camera, deltaTime, &viewAngleX, &viewAngleY);
        
        //viewMat = DivineMath::create_x_rotation_matrix(viewAngle)*DivineMath::create_translation_matrix(DivineMath::vec3(camera.cameraPos));
        viewMat = camera.lookAt(camera.cameraPos, camera.cameraTarget, DivineCamera::up);

        glUseProgram(staticShader);
        modelMat = DivineMath::create_x_rotation_matrix(90)*DivineMath::create_scale_matrix(DivineMath::vec3(10.0f, 1.0f, 10.0f));
        
        glUniformMatrix4fv(staticModelMatrixLocation, 1, GL_FALSE, modelMat.data);
        glUniformMatrix4fv(staticViewMatrixLocation, 1, GL_FALSE, viewMat.data);
        glUniformMatrix4fv(staticProjectionMatrixLocation, 1, GL_FALSE, projectionMat.data);
        Ground.draw_object();

        modelMat = DivineMath::create_scale_matrix(DivineMath::vec3(10.0f, 10.0f, 10.0f));
        glUniformMatrix4fv(staticModelMatrixLocation, 1, GL_FALSE, modelMat.data);
        CoordinateSystem.draw_object();

        glUseProgram(program);        
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

       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if(cursor)
    {
        glfwDestroyCursor(cursor);
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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}