//
// Created by HORIA on 17.01.2024.
//

#include "Shape.h"

void Shape::setColor(const V4f &color) {
    m_color = color;
}

V4f Shape::getColor() const {
    return m_color;
}
