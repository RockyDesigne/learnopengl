//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_SHAPEBUFFER_H
#define LEARNGL_SHAPEBUFFER_H
#include <glad.h>
#include <glfw3.h>

class ShapeBuffer
{
public:
    ShapeBuffer(const float* vertices, GLsizei size);
    void bind() const;
    void unbind() const;
    ~ShapeBuffer();
private:
    GLuint VAO;
    GLuint VBO;
    GLsizei m_size;
};

#endif //LEARNGL_SHAPEBUFFER_H
