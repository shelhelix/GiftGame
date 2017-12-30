//
// Created by shelhelix on 29.12.17.
//

#ifndef GIFTGAME_DOT2D_H
#define GIFTGAME_DOT2D_H


class Dot2D {
public:
    float x;
    float y;

    Dot2D operator+(const Dot2D& b);

    Dot2D operator-(const Dot2D& b);

    void normalize();
};


#endif //GIFTGAME_DOT2D_H
