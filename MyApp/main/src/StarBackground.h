#ifndef _STARBACKGROUND_H_
#define _STARBACKGROUND_H_

#include "ozateck.h"

#include "StarBlink.h"

class StarBackground {

private:
	SDL_Renderer *renderer;
	const int windowW, windowH;
	const int ratioX, ratioY, padding;

	SDL_Rect rect;
	int minX, maxX, minY, maxY;

	SDL_Rect rects[30];
	int total, size;

	// Blinks
	vector<StarBlink *> blinks;

public:
	StarBackground(SDL_Renderer *renderer,
				   int windowW, int windowH);

	virtual ~StarBackground();

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

#endif // _STARBACKGROUND_H_