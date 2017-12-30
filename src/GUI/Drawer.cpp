//
// Created by shelhelix on 29.12.17.
//

#include "Drawer.h"
#include "../utils/Dot2D.h"
#include "../utils/Color.h"


Drawer::Drawer(int winW, int winH, SDL_Renderer* renderer) {
    this->drawPortW = winW;
    this->drawPortH = winH;
    this->renderer = renderer;
    this->startPos = Dot2D{0,0};
    this->yToPix = 1;
    this->xToPix = 1;
}

void Drawer::draw(GameObject *object) {
    //Mapping
    const Area& rect = object->objectArea;
    SDL_Rect drawArea = {xToPix*(rect.center.x-rect.w2-startPos.x), yToPix*(rect.center.y-rect.h2-startPos.y), xToPix*2*rect.w2, yToPix*2*rect.h2};
    Color c = bank.getObjectColor(object->getName());
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_RenderFillRect(renderer, &drawArea);
}



void Drawer::setVisibleArea(Area &area) {
    startPos = Dot2D{area.center.x-area.w2, area.center.y-area.h2};
    xToPix = (float)(drawPortW)/(area.w2*2);
    yToPix = (float)(drawPortH)/(area.h2*2);
}

void Drawer::drawCenterLine(GameObject *one, GameObject *other) {
    //Mapping
    Dot2D oc = one->objectArea.center;
    Dot2D oc2 = other->objectArea.center;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, (oc-startPos).x*xToPix, (oc-startPos).y*yToPix, (oc2-startPos).x*xToPix, (oc2-startPos).y*yToPix);

}
