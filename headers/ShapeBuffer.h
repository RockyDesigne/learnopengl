//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_SHAPEBUFFER_H
#define LEARNGL_SHAPEBUFFER_H
#include <glad.h>
#include <glfw3.h>
#include <vector>
class ShapeBuffer
{
public:
    ShapeBuffer(const std::vector<float>& vertices);
    void bind() const;
    void unbind() const;
    virtual void draw() = 0;
    void setVertices(const std::vector<float>& vertices);
    ~ShapeBuffer();
private:
    GLuint VAO;
    GLuint VBO;
    std::vector<float> m_vertices;
};

#endif //LEARNGL_SHAPEBUFFER_H
