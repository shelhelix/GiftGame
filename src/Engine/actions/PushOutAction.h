//
// Created by shelhelix on 30.12.17.
//

#ifndef GIFTGAME_PUSHOUTACTION_H
#define GIFTGAME_PUSHOUTACTION_H


#include "Action.h"

class PushOutAction : public Action {
public:
    void applyOnIntersect(IntersectionSide otherSide, GameObject *one, GameObject *other) override;

};


#endif //GIFTGAME_PUSHOUTACTION_H
