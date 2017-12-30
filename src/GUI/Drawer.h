//
// Created by shelhelix on 29.12.17.
//

#ifndef GIFTGAME_DRAWER_H
#define GIFTGAME_DRAWER_H


#include <SDL_system.h>
#include "../Engine/GameObject.h"
#include "../utils/Dot2D.h"
#include "../utils/Color.h"
#include "ColorBank.h"

class Drawer {

    int drawPortW;
    int drawPortH;
    Dot2D startPos;
    float xToPix;
    float yToPix;

    ColorBank bank;

    SDL_Renderer* renderer;
public:


    Drawer(int winW, int winH, SDL_Renderer* renderer);
    void setVisibleArea(Area& area);
    void draw(GameObject *object);
    void drawCenterLine(GameObject* one, GameObject *other);
};


#endif //GIFTGAME_DRAWER_H
