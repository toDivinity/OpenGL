    #pragma once
    #include "DivineConfig.h"
    #include "DivineMath.h"
    #include "DivineObject.h"
    #include "DivineInput.h"
    #include "DivineCamera.h"
    #include "stb_image.h"

    GLint Scene3d();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    void cursor_callback(GLFWwindow* window, double xpos, double ypos);