//
// Created by shelhelix on 30.12.17.
//

#ifndef GIFTGAME_ACTION_H
#define GIFTGAME_ACTION_H

#include "../GameObject.h"
#include "../IntersectionSide.h"


class Action {
public:
    virtual void applyOnIntersect(IntersectionSide otherSide, GameObject *one, GameObject *other) = 0;
};

#endif //GIFTGAME_ACTION_H
