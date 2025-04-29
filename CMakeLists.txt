cmake_minimum_required(VERSION 3.10)
project(DivineEngine)

# Сбор исходников
file(GLOB SOURCES "src/*.cpp" "src/*.c" "progs/*.cpp" "progs/*.c" "include/*.h")

# Настройка кодировки для MSVC
if (MSVC)
    add_compile_options(/utf-8)
endif()

# Проверка PowerShell
find_program(PWSH_EXECUTABLE pwsh.exe)
if (NOT PWSH_EXECUTABLE)
    set(CMAKE_EXECUTE_PROCESS_COMMAND "powershell.exe")
endif()

# Поиск OpenGL
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

# Поиск GLFW
find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)
message(STATUS "Can't find GLFW in system directories")
message(STATUS "Trying to find in ${CMAKE_SOURCE_DIR}")
find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/glfw/lib/cmake/glfw3" NO_DEFAULT_PATH)
endif()

# Заголовочные файлы
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/progs
    ${PROJECT_SOURCE_DIR}/dependencies
)

add_executable(DivineEngine ${SOURCES})

# Линковка
target_link_libraries(DivineEngine PRIVATE OpenGL::GL)

# Подключаем OpenGL (Windows)
if (WIN32)
    target_link_libraries(DivineEngine PRIVATE opengl32)
    # Для MinGW/GCC добавляем -mwindows
    if(MINGW)
        target_link_options(DivineEngine PRIVATE -mwindows)
    endif()
else()
    # Подключаем OpenGL (Linux/macOS)
    target_link_libraries(DivineEngine PRIVATE OpenGL::GL)
endif()

# Линковка GLFW
target_link_libraries(DivineEngine PRIVATE glfw)