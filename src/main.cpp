#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <vector>

typedef unsigned char byte;

using namespace std;

struct Color {
    byte r;
    byte g;
    byte b;
};

struct Dot2D {
    int x;
    int y;

    Dot2D operator+(const Dot2D& b) {
        Dot2D out{};
        out.x = this->x + b.x;
        out.y = this->y + b.y;
        return out;
    }

    Dot2D operator-(const Dot2D& b) {
        Dot2D out{};
        out.x = this->x - b.x;
        out.y = this->y - b.y;
        return out;
    }
};

struct Object {
    SDL_Rect area;
    Dot2D center;
    Dot2D speed;
    Color color;

    bool hitTheGround;
    bool hitTheCeiling;
    bool hitTheLeftWall;
    bool hitTheRightWall;

    bool intersectedWith(Object otherObject) {
        return (area.w/2+otherObject.area.w/2 > abs(center.x-otherObject.center.x)) &&
                (area.h/2+otherObject.area.h/2 > abs(center.y-otherObject.center.y));
    }
};


void drawObjects(SDL_Renderer *renderer, list<Object*> objects);


void moveObjects(Object& hero, list<Object> &objects);

void drawObject(SDL_Renderer *renderer, const Object &obj) {
    SDL_SetRenderDrawColor(renderer, obj.color.r, obj.color.g, obj.color.b, 255);
    SDL_RenderFillRect(renderer, &obj.area);
}


int main(int argc, char **argv ) {
    SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* win = SDL_CreateWindow("Physics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    int winW, winH;
    SDL_GetWindowSize(win, &winW, &winH);
    SDL_Event{};
    Object hero{ .area = {120,64, 64, 64}, .center = {152, 96}, .speed = {0,-1}, .color = {0,255,0}};
    Object floor{ .area = {120,128, 192, 64},  .center = {216, 160}, .speed = {0,0}, .color = {255,255,0}};

    Object leftWall{ .area = {0,0, 20, winH},  .center = {10, winH/2}, .speed = {0,0}, .color = {255,255,0}};
    Object rightWall{ .area = {winW-20, 0, 20, winH},  .center = {winW-10, winH/2}, .speed = {0,0}, .color = {255,255,0}};
    Object upperWall{ .area = {0, 0, winW, 20},  .center = {winW/2, 10}, .speed = {0,0}, .color = {255,255,0}};
    Object bottomWall{ .area = {0, winH-20, winW, 20},  .center = {winW/2, winH-10}, .speed = {0,0}, .color = {255,255,0}};

    Object background{ .area = {0,0, winW, winH}, .center = {winW/2, winH/2}, .speed = {0,0}, .color = {0,0,0}};

    list<Object*> drawingObjects = {&background, &hero, &floor, &leftWall, &rightWall, &upperWall, &bottomWall};
    list<Object> intersectableObjects = {floor, leftWall, rightWall, upperWall, bottomWall};

    bool timeToStop = false;
    while (!timeToStop) {
        drawObjects(rend, drawingObjects);

        moveObjects(hero, intersectableObjects);


        SDL_Event e{};
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    timeToStop = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_DOWN) hero.speed.y = 1;
                    if (e.key.keysym.sym == SDLK_UP) hero.speed.y = -1;
                    if (e.key.keysym.sym == SDLK_RIGHT) hero.speed.x = 1;
                    if (e.key.keysym.sym == SDLK_LEFT) hero.speed.x = -1;
                    break;
                default:break;
            }
        }


        //Gravity


        SDL_RenderPresent(rend);
        SDL_Delay(10);
    }
}

void moveObjects(Object& hero, list<Object> &objects) {
    vector<Object> newPos;

    Object newHero = hero;

    if (hero.speed.x > 0)
        hero.hitTheRightWall = false;
    if (hero.speed.x < 0)
        hero.hitTheLeftWall = false;
    if (hero.speed.y > 0)
        hero.hitTheGround = false;
    if (hero.speed.y < 0)
        hero.hitTheCeiling = false;


    if (hero.speed.x > 0 && !hero.hitTheRightWall) {
        newHero.center.x = hero.center.x + hero.speed.x;
    }

    if (hero.speed.x < 0 && !hero.hitTheLeftWall) {
        newHero.center.x = hero.center.x + hero.speed.x;
    }

    if (hero.speed.y > 0 && !hero.hitTheGround) {
        newHero.center.y = hero.center.y + hero.speed.y;
    }

    if (hero.speed.y < 0 && !hero.hitTheCeiling) {
        newHero.center.y = hero.center.y + hero.speed.y;
    }


    newHero.area = {   (newHero.center+hero.speed).x - hero.area.w/2,
                (newHero.center+hero.speed).y - hero.area.h/2,
                hero.area.w,
                hero.area.h};
    //Detect collisions
    for (auto& o : objects){
        if (o.intersectedWith(newHero)) {
            Dot2D diff = newHero.center - o.center;

            if (abs(diff.y) >= abs(diff.x) && diff.y <= abs (newHero.area.h/2+o.area.h/2)) {
                if (diff.y > 0) {
                    newHero.area.y = o.area.y +o.area.h;
                    newHero.center.y = newHero.area.y + newHero.area.h/2;
                    newHero.hitTheCeiling = true;
                    cout << "hitted cealing!" << endl;
                    continue;
                }
                if (diff.y < 0) {
                    newHero.area.y = o.area.y - newHero.area.h;
                    newHero.center.y = newHero.area.y + newHero.area.h/2;
                    newHero.hitTheGround = true;
                    cout << "hitted ground!" << endl;
                    continue;
                }
            }
            if (abs(diff.y) <= abs(diff.x) && diff.x <= abs (newHero.area.w/2+o.area.w/2)) {
                if (diff.x > 0) {
                    newHero.area.x = o.area.x - newHero.area.h;
                    newHero.center.x = newHero.area.x + newHero.area.w/2;
                    newHero.hitTheLeftWall = true;
                    cout << "hitted left wall!" << endl;
                    continue;
                }
                if (diff.x < 0) {
                    newHero.area.x = o.area.x + o.area.w;
                    newHero.center.x = newHero.area.x + newHero.area.w/2;
                    newHero.hitTheRightWall = true;
                    cout << "hitted right wall!" << endl;
                    continue;
                }
            }
        }
    }

    hero = newHero;


    for (auto& o : objects) {
        o.center = o.center + o.speed;
        o.area.x = o.center.x - o.area.w/2;
        o.area.y = o.center.y - o.area.h/2;
    }
}


void drawObjects(SDL_Renderer *renderer, list<Object*> objects) {
    for (auto& o : objects) {
        drawObject(renderer, *o);
    }
}

