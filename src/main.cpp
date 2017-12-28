#include <iostream>
#include <SDL2/SDL.h>

using namespace std;


int main(int argc, char **argv ) {
	SDL_Window* win = SDL_CreateWindow("Physics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *rend = SDL_CreateRenderer();
	
	SDL_Delay(3000);
}
