//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_SHAPE_H
#define LEARNGL_SHAPE_H
#include "ShapeBuffer.h"
#include <glad.h>
#include <glfw3.h>
class Shape : public ShapeBuffer {
public:
    Shape(const std::vector<float>& vertices, const V4f& color) : ShapeBuffer {vertices}, m_color{color} {}
    Shape()=default;
    void setColor(const V4f& color);
    V4f getColor() const;
private:
    V4f m_color;
};


#endif //LEARNGL_SHAPE_H
