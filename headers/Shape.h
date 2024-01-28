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
    Shape(const std::vector<float>& vertices) : ShapeBuffer {vertices} {}
    virtual void draw() = 0;
};


#endif //LEARNGL_SHAPE_H
