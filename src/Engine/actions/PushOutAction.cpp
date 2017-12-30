//
// Created by shelhelix on 30.12.17.
//

#include "PushOutAction.h"

void PushOutAction::applyOnIntersect(IntersectionSide otherSide, GameObject *one, GameObject *other) {
    switch (otherSide) {
        case NONE:
            break;
        default:
            break;
        case UP:
            other->objectArea.center.y = one->objectArea.center.y-one->objectArea.h2-other->objectArea.h2;
            break;
        case DOWN:
            other->objectArea.center.y = one->objectArea.center.y+one->objectArea.h2+other->objectArea.h2;
            break;
        case LEFT:
            other->objectArea.center.x = one->objectArea.center.x-one->objectArea.w2-other->objectArea.w2;
            break;
        case RIGHT:
            other->objectArea.center.x = one->objectArea.center.x+one->objectArea.w2+other->objectArea.w2;
            break;

    }
}
