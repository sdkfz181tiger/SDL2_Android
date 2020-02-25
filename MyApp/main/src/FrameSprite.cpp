#include "FrameSprite.h"

FrameSprite::FrameSprite(SDL_Renderer *renderer,
						 int windowW, int windowH) :
		renderer(renderer), windowW(windowW), windowH(windowH),
		ratioX(3), ratioY(4), padding(10),
		minX(0), maxX(0), minY(0), maxY(0) {
	//SDL_Log("FrameSprite():%s", path);
	this->init();
}

FrameSprite::~FrameSprite() {
	//SDL_Log("~FrameSprite()");
}

bool FrameSprite::init() {
	//SDL_Log("FrameSprite::init()");

	// Rect
	rect.x = padding;
	rect.y = padding;
	rect.w = windowW - padding * 2;
	rect.h = rect.w / ratioX * ratioY;

	// Left
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = padding;
	rects[0].h = windowH;

	// Top
	rects[1].x = 0;
	rects[1].y = 0;
	rects[1].w = windowW;
	rects[1].h = padding;

	// Right
	rects[2].x = windowW - padding;
	rects[2].y = 0;
	rects[2].w = padding;
	rects[2].h = windowH;

	// Bottom
	rects[3].x = 0;
	rects[3].y = padding + rect.h;
	rects[3].w = windowW;
	rects[3].h = windowH - (rect.y + rect.h);

	// Border
	minX = padding;
	maxX = windowW - padding;
	minY = padding;
	maxY = rect.y + rect.h;

	SDL_Log("frame [minX, maxX, minY, maxY]: [%d, %d, %d, %d]",
			minX, maxX, minY, maxY);

	return true;
}

void FrameSprite::render() {

	SDL_SetRenderDrawColor(renderer, 33, 120, 120, 255);
	SDL_RenderFillRects(renderer, rects, 4);
}