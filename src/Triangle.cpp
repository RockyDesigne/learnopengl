//
// Created by HORIA on 17.01.2024.
//

#include "Triangle.h"

void Triangle::draw() {
    bind();
    glDrawArrays(GL_TRIANGLES, 0,3);
    unbind();
}
