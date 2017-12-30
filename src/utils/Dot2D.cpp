//
// Created by shelhelix on 29.12.17.
//

#include <cmath>
#include "Dot2D.h"

Dot2D Dot2D::operator+(const Dot2D &b) {
    Dot2D out{};
    out.x = this->x + b.x;
    out.y = this->y + b.y;
    return out;
}

Dot2D Dot2D::operator-(const Dot2D &b) {
    Dot2D out{};
    out.x = this->x - b.x;
    out.y = this->y - b.y;
    return out;
}

void Dot2D::normalize() {
    x /= sqrtf(x*x+y*y);
    y /= sqrtf(x*x+y*y);
}
