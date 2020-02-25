#ifndef _DEBUGRENDERER_H_
#define _DEBUGRENDERER_H_

#include "ozateck.h"

class DebugRenderer {

private:
	SDL_Renderer *renderer;

	int windowW, windowH, gridSize;

	int tickTime, tickInterval, tickCounter;

	const int fpsPad;
	char fpsStr[10];
	vector<int> fpsData;

public:
	DebugRenderer(SDL_Renderer *renderer, int windowW, int windowH, int gridSize);

	~DebugRenderer();

	bool init();

	void render();

	void drawGraph();

	void drawFPS();

	void setColor(Uint8 r, Uint8 g, Uint8 b);

	void drawLine(int fromX, int fromY, int toX, int toY);

	void drawRect(const SDL_Rect *rect);
};

#endif // _DEBUGRENDERER_H_