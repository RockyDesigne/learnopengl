cmake_minimum_required(VERSION 3.25)
set(CMAKE_VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)

project(learnGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -pedantic")

include_directories(headers)

set(SOURCES src/main.cpp src/Shader.cpp src/glad.c headers/Shader.h headers/Window.h src/Window.cpp headers/ShapeBuffer.h src/ShapeBuffer.cpp src/Shape.cpp headers/Triangle.h src/Triangle.cpp src/Square.cpp)

configure_file(./shaders/vertex.glsl ${CMAKE_BINARY_DIR}/vertex.glsl)
configure_file(./shaders/fragment.glsl ${CMAKE_BINARY_DIR}/fragment.glsl)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/glfw-3.3.9.bin.WIN64/include/GLFW")

link_directories("G:/projects/repos/libraries/glfw-3.3.9.bin.WIN64/lib-mingw-w64")

target_link_libraries(${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/glfw-3.3.9.bin.WIN64/lib-mingw-w64/libglfw3.a"
        opengl32
        kernel32
        user32
        gdi32
        shell32
        )
