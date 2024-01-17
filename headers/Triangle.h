//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_TRIANGLE_H
#define LEARNGL_TRIANGLE_H
#include "Shape.h"
#include <glad.h>
#include <glfw3.h>
class Triangle : public Shape {
public:
    Triangle(const float* vertices, GLsizei size) : Shape{vertices,size} {}
    void draw() override;
};


#endif //LEARNGL_TRIANGLE_H
