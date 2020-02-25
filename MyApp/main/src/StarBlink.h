#ifndef _STARBLINK_H_
#define _STARBLINK_H_

#include "ozateck.h"

class StarBlink {

private:
	SDL_Renderer *renderer;
	const int x, y;

	SDL_Rect rects[4];
	int total, size;

public:
	StarBlink(SDL_Renderer *renderer, int x, int y);

	virtual ~StarBlink();

public:
	bool init();

	void render();
};

#endif // _STARBLINK_H_