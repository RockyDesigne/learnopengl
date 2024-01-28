//
// Created by HORIA on 17.01.2024.
//

#include "ShapeBuffer.h"


ShapeBuffer::ShapeBuffer(const std::vector<float>& vertices) : m_vertices{vertices}
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Unbind to prevent modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShapeBuffer::bind() const {
    glBindVertexArray(VAO);
}

void ShapeBuffer::unbind() const {
    glBindVertexArray(0);
}

ShapeBuffer::~ShapeBuffer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ShapeBuffer::setVertices(const std::vector<float> &vertices) {

}
