//
// Created by shelhelix on 30.12.17.
//

#ifndef GIFTGAME_AREA_H
#define GIFTGAME_AREA_H

#include "Dot2D.h"

struct Area {
    //Center coords
    Dot2D center{};
    //halfSizes
    float w2;
    float h2;

    Area(Dot2D leftCorner, float w, float h) {
        center = {leftCorner.x+w/2, leftCorner.y-h/2};
        w2 = w/2;
        h2 = h/2;
    }

    Dot2D getURCorner() {
        return {center.x+w2, center.y+h2};
    }
    Dot2D getULCorner() {
        return {center.x-w2, center.y+h2};
    }
    Dot2D getDRCorner() {
        return {center.x+w2, center.y-h2};
    }
    Dot2D getDLCorner() {
        return {center.x-w2, center.y-h2};
    }
};
#endif //GIFTGAME_AREA_H
