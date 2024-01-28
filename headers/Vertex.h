//
// Created by HORIA on 26.01.2024.
//

#ifndef LEARNGL_VERTEX_H
#define LEARNGL_VERTEX_H

#ifndef LA_IMPLEMENTATION
#define LA_IMPLEMENTATION
#endif

#include "la.h"

enum VertexAttribs : GLuint {
    VA_POS,
    VA_UV,
    VA_COLOR,
    COUNT_VAS,
};

struct Vertex {
    V2f pos;
    V2f uv;
    V4f color;
};

#endif //LEARNGL_VERTEX_H
