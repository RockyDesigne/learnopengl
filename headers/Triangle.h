//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_TRIANGLE_H
#define LEARNGL_TRIANGLE_H
#include "Shape.h"
#include <glad.h>
#include <glfw3.h>
#include "la.h"
class Triangle : public Shape {
public:
    Triangle(const V3f& x, const V3f& y, const V3f& z, const V4f& color) : Shape{std::vector<float>{x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z}, color} {}
    void draw() override;
};


#endif //LEARNGL_TRIANGLE_H
