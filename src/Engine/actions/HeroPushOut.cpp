//
// Created by shelhelix on 30.12.17.
//

#include "HeroPushOut.h"
#include "PushOutAction.h"

void HeroPushOut::applyOnIntersect(IntersectionSide otherSide, GameObject *one, GameObject *other) {
    PushOutAction a;
    if (one->getName() == "hero" && other->getName() == "hero2" || other->getName() == "hero" && one->getName() == "hero2" ) {

        //a.applyOnIntersect(otherSide, one, other);
    }

}
