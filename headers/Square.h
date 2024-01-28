//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_SQUARE_H
#define LEARNGL_SQUARE_H
#include <glad.h>
#include <glfw3.h>
#include "Shape.h"
#include "la.h"
class Square : public Shape {
public:
    Square(const V3f& topLeft, const V3f& bottomRight) : Shape{std::vector<float>{topLeft.x,topLeft.y,topLeft.z,bottomRight.x,topLeft.y,topLeft.z,bottomRight.x,bottomRight.y,bottomRight.z,bottomRight.x,bottomRight.y,bottomRight.z,topLeft.x,bottomRight.y,topLeft.z,topLeft.x,topLeft.y,topLeft.z}} {}
    void draw() override;
};


#endif //LEARNGL_SQUARE_H
