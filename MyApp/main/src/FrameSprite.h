#ifndef _FRAMESPRITE_H_
#define _FRAMESPRITE_H_

#include "ozateck.h"

class FrameSprite {

private:
	SDL_Renderer *renderer;
	const int windowW, windowH;
	const int ratioX, ratioY, padding;

	SDL_Rect rect;
	SDL_Rect rects[4];
	int minX, maxX, minY, maxY;

public:
	FrameSprite(SDL_Renderer *renderer,
				int windowW, int windowH);

	virtual ~FrameSprite();

public:
	virtual bool init();

	int getMinX() const { return minX; };

	int getMaxX() const { return maxX; }

	int getMinY() const { return minY; }

	int getMaxY() const { return maxY; }

	int getMidX() const { return (maxX - minX) / 2; }

	int getMidY() const { return (maxY - minY) / 2; }

	int getWidth() const { return maxX - minX; }

	int getHeight() const { return maxY - minY; }

	virtual void render();
};

#endif // _FRAMESPRITE_H_