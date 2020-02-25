#ifndef _SCOREBARRENDERER_H_
#define _SCOREBARRENDERER_H_

#include "ozateck.h"
#include "FrameSprite.h"

class ScoreBarRenderer {

private:
	SDL_Renderer *renderer;

	const FrameSprite *frame;
	const int grid;
	int l, c, r, b;
	int numScore, numLast, numHigh;

	char numScoreStr[10];
	char numLastStr[10];
	char numHighStr[10];

	const char *lblScore, *lblLast, *lblHigh;

public:
	ScoreBarRenderer(SDL_Renderer *renderer,
					 const FrameSprite *frame,
					 const int grid);

	~ScoreBarRenderer();

	bool init();

	int getBottomY();

	void render();

	void setScore(int num) { numScore = num; }

	int getScore() { return numScore; }

	void setLast(int num) { numLast = num; }

	int getLast() { return numLast; }

	void setHigh(int num) { numHigh = num; }

	int getHigh() { return numHigh; }

	bool addScore(int num);

	void setColor(Uint8 r, Uint8 g, Uint8 b);

	void drawLine(int fromX, int fromY, int toX, int toY);

	void drawRect(const SDL_Rect *rect);
};

#endif // _SCOREBARRENDERER_H_