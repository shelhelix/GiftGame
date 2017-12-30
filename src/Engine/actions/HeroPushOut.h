//
// Created by shelhelix on 30.12.17.
//

#ifndef GIFTGAME_HEROPUSHOUT_H
#define GIFTGAME_HEROPUSHOUT_H


#include "Action.h"

class HeroPushOut : public Action {
public:
    void applyOnIntersect(IntersectionSide otherSide, GameObject *one, GameObject *other) override;

};


#endif //GIFTGAME_HEROPUSHOUT_H
