cmake_minimum_required(VERSION 3.10)
project(DivineEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Configuring DivineEngine project")
message(STATUS "C++ standard set to ${CMAKE_CXX_STANDARD}")

# Источники
file(GLOB SOURCES "src/*.cpp" "src/*.c" "progs/*/*.cpp" "progs/*/*.c")
message(STATUS "Found source files: ${SOURCES}")

add_executable(DivineEngine ${SOURCES})

# OpenGL
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found: ${OpenGL_FOUND} (${OpenGL_GLU_LIBRARY})")

# GLFW
find_package(glfw3 QUIET)
if (glfw3_FOUND)
    message(STATUS "GLFW found in system: ${glfw3_VERSION}")
else()
    message(STATUS "GLFW not found in system, building from submodule")
    add_subdirectory(dependencies/glfw3)
    set(GLFW_BUILT_FROM_SOURCE TRUE)
endif()

# Assimp
find_package(assimp QUIET)
if (assimp_FOUND)
    message(STATUS "Assimp found in system: ${assimp_VERSION}")
else()
    message(STATUS "Assimp not found in system, building from submodule")
    add_subdirectory(dependencies/assimp)
    set(ASSIMP_BUILT_FROM_SOURCE TRUE)
    add_library(assimp::assimp ALIAS assimp)
endif()

# GLM
find_package(glm QUIET)
if (glm_FOUND)
    message(STATUS "GLM found in system: ${glm_VERSION}")
else()
    message(STATUS "GLM not found in system, using submodule version")
    add_subdirectory(dependencies/glm)
    set(GLM_BUILT_FROM_SOURCE TRUE)
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
    $<$<BOOL:${glfw3_FOUND}>:glfw3> $<$<BOOL:${GLFW_BUILT_FROM_SOURCE}>:glfw>
    $<$<BOOL:${assimp_FOUND}>:assimp::assimp> $<$<BOOL:${ASSIMP_BUILT_FROM_SOURCE}>:assimp>
    glm::glm
)

# Итоговый отчёт
message(STATUS "")
message(STATUS "=== Dependency Summary ===")
message(STATUS "OpenGL: system (${OpenGL_GLU_LIBRARY})")
message(STATUS "GLFW: $<$<BOOL:${glfw3_FOUND}>:system> $<$<BOOL:${GLFW_BUILT_FROM_SOURCE}>:built from source>")
message(STATUS "Assimp: $<$<BOOL:${assimp_FOUND}>:system> $<$<BOOL:${ASSIMP_BUILT_FROM_SOURCE}>:built from source>")
message(STATUS "GLM: $<$<BOOL:${glm_FOUND}>:system> $<$<BOOL:${GLM_BUILT_FROM_SOURCE}>:built from source>")
message(STATUS "=========================")