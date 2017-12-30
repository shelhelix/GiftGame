//
// Created by shelhelix on 29.12.17.
//

#ifndef GIFTGAME_GAMEOBJECT_H
#define GIFTGAME_GAMEOBJECT_H

#include "../utils/Dot2D.h"
#include "../utils/Area.h"
#include "IntersectionSide.h"
#include <list>
#include <string>

using namespace std;


class Action;


class GameObject {
private:
    const string objectName;
    list<Action*> activeActions;
public:
    Area objectArea;
    Dot2D speed;

    const string& getName();
    GameObject(const Area &area, const string name);
    void addAction(Action* a);
    void appltActionsOnIntersectWith(GameObject *other, IntersectionSide ourSide);

};


#endif //GIFTGAME_GAMEOBJECT_H
