//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_SQUARE_H
#define LEARNGL_SQUARE_H
#include <glad.h>
#include <glfw3.h>
#include "Shape.h"

class Square : public Shape {
public:
    Square(const float* vertices, GLsizei size) : Shape{vertices,size} {}
    void draw() override;
};


#endif //LEARNGL_SQUARE_H
