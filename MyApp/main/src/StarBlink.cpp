#include "StarBlink.h"

StarBlink::StarBlink(SDL_Renderer *renderer, int x, int y) :
		renderer(renderer), x(x), y(y) {
	SDL_Log("StarBlink()");
	this->init();
}

StarBlink::~StarBlink() {
	SDL_Log("~StarBlink()");
}

bool StarBlink::init() {
	SDL_Log("StarBlink::init()");

	// Total, Size
	total = sizeof(rects) / sizeof(SDL_Rect);
	size = 4;

	// Stars
	for (int i = 0; i < total; i++) {
		rects[i].x = x + size * i;
		rects[i].y = y + size * i;
		rects[i].w = size;
		rects[i].h = size;
	}

	return true;
}

void StarBlink::render() {
	//SDL_Log("StarBlink::render()");

	SDL_RenderFillRects(renderer, rects, total);
}