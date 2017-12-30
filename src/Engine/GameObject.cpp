//
// Created by shelhelix on 29.12.17.
//

#include "GameObject.h"
#include "./actions/Action.h"


void GameObject::appltActionsOnIntersectWith(GameObject *other, IntersectionSide ourSide) {
    for (auto a : activeActions) {
        a->applyOnIntersect(ourSide, this, other);
    }
}

void GameObject::addAction(Action *a) {
    activeActions.push_back(a);
}

GameObject::GameObject(const Area &area, const string name) : objectName(name), objectArea (area){
}

const string &GameObject::getName() {
    return objectName;
}

