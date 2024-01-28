//
// Created by HORIA on 17.01.2024.
//

#include "Square.h"

void Square::draw() {
    bind();
    glDrawArrays(GL_TRIANGLES,0,6);
    unbind();
}
