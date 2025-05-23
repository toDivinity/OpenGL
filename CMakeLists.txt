cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
project(DivineEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Configuring DivineEngine project")
message(STATUS "C++ standard set to ${CMAKE_CXX_STANDARD}")

# Источники
file(GLOB SOURCES "src/*.cpp" "src/*.c" "progs/*/*.cpp" "progs/*/*.c")

add_executable(DivineEngine ${SOURCES})

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)
    add_subdirectory(dependencies/glfw3)
endif()

# GLM
find_package(glm QUIET)
if (NOT glm_FOUND)
    add_subdirectory(dependencies/glm)
endif()

# Заголовочные директории
target_include_directories(DivineEngine PRIVATE
    include
    progs
    dependencies
)

# Линковка
target_link_libraries(DivineEngine PRIVATE
    OpenGL::GL
    glfw
    glm::glm
)
