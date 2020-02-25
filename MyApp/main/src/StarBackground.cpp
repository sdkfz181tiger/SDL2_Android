#include "StarBackground.h"

StarBackground::StarBackground(SDL_Renderer *renderer,
							   int windowW, int windowH) :
		renderer(renderer), windowW(windowW), windowH(windowH),
		ratioX(3), ratioY(4), padding(10),
		minX(0), maxX(0), minY(0), maxY(0) {
	//SDL_Log("StarBackground():%s", path);
	this->init();
}

StarBackground::~StarBackground() {
	//SDL_Log("~StarBackground()");

	for (auto blink : blinks) delete blink;
	blinks.clear();
}

bool StarBackground::init() {
	//SDL_Log("StarBackground::init()");

	// Rect
	rect.x = padding;
	rect.y = padding;
	rect.w = windowW - padding * 2;
	rect.h = rect.w / ratioX * ratioY;

	// Border
	minX = padding;
	maxX = windowW - padding;
	minY = padding;
	maxY = rect.y + rect.h;

	SDL_Log("starlight [minX, maxX, minY, maxY]: [%d, %d, %d, %d]",
			minX, maxX, minY, maxY);

	// Total, Size
	total = sizeof(rects) / sizeof(SDL_Rect);
	size = 8;

	// Stars
	for (int i = 0; i < total; i++) {
		int x = UtilMath::getInstance(renderer)->getRandom(minX + size, maxX - size);
		int y = UtilMath::getInstance(renderer)->getRandom(minY + size, maxY - size);
		rects[i].x = x;
		rects[i].y = y;
		rects[i].w = size;
		rects[i].h = size;
	}

	// Blink
	for (int i = 0; i < 10; i++) {
		int x = UtilMath::getInstance(renderer)->getRandom(minX + size, maxX - size);
		int y = UtilMath::getInstance(renderer)->getRandom(minY + size, maxY - size);
		StarBlink *blink = new StarBlink(renderer, x, y);
		blinks.push_back(blink);
	}

	return true;
}

void StarBackground::render() {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRects(renderer, rects, total);

	// Blink
	auto itB = blinks.begin();
	while (itB != blinks.end()) {
		auto *blink = static_cast<StarBlink *>(*itB);
		blink->render();
		itB++;
	}
}