#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <vector>
#include "GUI/Drawer.h"
#include "Engine/actions/PushOutAction.h"
#include "Engine/actions/HeroPushOut.h"


using namespace std;

#define EPS 0.00001

IntersectionSide intersect(GameObject *a, GameObject *b) {
    Dot2D diff = b->objectArea.center - a->objectArea.center;
    Dot2D urVec = a->objectArea.getURCorner() - a->objectArea.center;
    urVec.normalize();
    Dot2D ulVec = a->objectArea.getULCorner() - a->objectArea.center;
    ulVec.normalize();
    Dot2D dlVec = a->objectArea.getDLCorner() - a->objectArea.center;
    dlVec.normalize();
    Dot2D drVec = a->objectArea.getDRCorner() - a->objectArea.center;
    drVec.normalize();

    if (abs(diff.x) < a->objectArea.w2+b->objectArea.w2 && abs(diff.y) < a->objectArea.h2+b->objectArea.h2) {
        diff.normalize();
        int i = 0;
        float xVectorCoeff = abs(urVec.x)/abs(diff.x);
        float yVectorCoeff = abs(urVec.y)/abs(diff.y);

        Dot2D xTemp = {diff.x*xVectorCoeff, diff.y*xVectorCoeff};
        Dot2D yTemp = {diff.x*yVectorCoeff, diff.y*yVectorCoeff};
        if (abs(xTemp.x - urVec.x) <= EPS && xTemp.y >= drVec.y && xTemp.y <= urVec.y)
            return RIGHT;
        if (xTemp.y >= dlVec.y && xTemp.y <= ulVec.y)
            return LEFT;
        if (abs(yTemp.y - drVec.y) <= EPS && yTemp.x >= dlVec.x && yTemp.x <= drVec.x)
            return UP;
        if (yTemp.x >= ulVec.x && yTemp.x <= urVec.x) return DOWN;
    }

    return NONE;
}

void moveObjects(list<GameObject *> list, Drawer debug) {
    for (auto oRef : list) {
        oRef->objectArea.center = oRef->objectArea.center + oRef->speed;
        for (auto otherRef : list) {
            if (oRef == otherRef) continue;
            debug.drawCenterLine(oRef, otherRef);
//            SDL_Delay(2);

            IntersectionSide side = intersect(oRef, otherRef);
            if (side != NONE){
                oRef->appltActionsOnIntersectWith(otherRef, side);
            }
        }

    }
}


int main(int argc, char **argv ) {
    SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* win = SDL_CreateWindow("Physics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, SDL_WINDOW_SHOWN);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    int winW, winH;
    SDL_GetWindowSize(win, &winW, &winH);

    Drawer d{winW, winH, rend};

    list<GameObject*> objs;
    HeroPushOut b;
    GameObject hero2{{{-1,0},1,1}, "hero2"};
    hero2.speed = {0,0.1};
    hero2.addAction(&b);
    objs.push_back(&hero2);

    GameObject hero{{{0,0},1,1}, "hero"};
    hero.speed = {0,0.1};
    hero.addAction(&b);
    objs.push_back(&hero);

    PushOutAction a;
    GameObject floor{{{-2,2},4,2}, "object"};
    floor.speed = {0,0};
    floor.addAction(&a);
    objs.push_back(&floor);

    GameObject wallR{{{9,4},2,11}, "object"};
    wallR.speed = {0,0};
    wallR.addAction(&a);
    objs.push_back(&wallR);

    GameObject wallL{{{-10,4},2,11}, "object"};
    wallL.speed = {0,0};
    wallL.addAction(&a);
    objs.push_back(&wallL);

    GameObject wallD{{{-10,-7},21,2}, "object2"};
    wallD.speed = {0,0};
    wallD.addAction(&a);
    objs.push_back(&wallD);

    GameObject wallU{{{-10, 6},21,2}, "object2"};
    wallU.speed = {0,0};
    wallU.addAction(&a);
    objs.push_back(&wallU);


//

    float zoomScale = 50;
    float value = 0.1;
    Area visible = {{-25,15}, zoomScale, zoomScale*((float)winH)/winW};
    d.setVisibleArea(visible);
    bool timeToStop = false;
    while (!timeToStop) {
        SDL_SetRenderDrawColor(rend, 0,0,0,0);
        SDL_RenderClear(rend);

//        d.draw(&hero);
        for (auto o : objs) {
            d.draw(o);
        }
        d.drawCenterLine(&hero, &hero2);
        moveObjects(objs, d);

        if (intersect(&hero, &hero2) == UP) {
            cout << "winner is PURPLE" << endl;
            timeToStop = true;
        }
        if (intersect(&hero2, &hero) == UP) {
            cout << "winner is GREEN" << endl;
            timeToStop = true;
        }

//        moveObjects(hero, interactable);
//
//
        SDL_Event e{};
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    timeToStop = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_DOWN)  hero.speed.y = value;
                    if (e.key.keysym.sym == SDLK_UP)    hero.speed.y = -value;
                    if (e.key.keysym.sym == SDLK_RIGHT) hero.speed.x = value;
                    if (e.key.keysym.sym == SDLK_LEFT)  hero.speed.x = -value;
                    if (e.key.keysym.sym == SDLK_s)  hero2.speed.y = value;
                    if (e.key.keysym.sym == SDLK_w)  hero2.speed.y = -value;
                    if (e.key.keysym.sym == SDLK_d)  hero2.speed.x = value;
                    if (e.key.keysym.sym == SDLK_a)  hero2.speed.x = -value;
                    break;
                default:break;
            }
        }
//
//
//        //Gravity
//
//
        SDL_RenderPresent(rend);
        SDL_Delay(10);
    }

    //After game loop
    timeToStop = false;
    while(!timeToStop) {
        SDL_Event e{};
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    timeToStop = true;
                    break;
                default:break;
            }
        }
    }
}


