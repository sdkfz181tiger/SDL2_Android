#include "ScoreBarRenderer.h"

ScoreBarRenderer::ScoreBarRenderer(SDL_Renderer *renderer,
								   const FrameSprite *frame, const int grid) :
		renderer(renderer), frame(frame), grid(grid),
		numScore(0), numLast(0), numHigh(0),
		lblScore("SCORE"), lblLast("LAST"), lblHigh("HIGH") {
	SDL_Log("ScoreBarRenderer()");
	this->init();
}

ScoreBarRenderer::~ScoreBarRenderer() {
	SDL_Log("~ScoreBarRenderer()");
}

bool ScoreBarRenderer::init() {
	SDL_Log("ScoreBarRenderer::init()");

	// Center, Left, Right, Bottom
	c = frame->getMidX();
	l = c - frame->getWidth() / 3;
	r = c + frame->getWidth() / 3;
	b = grid / 3 * 4;

	return true;
}

int ScoreBarRenderer::getBottomY() {
	return b;
}

void ScoreBarRenderer::render() {

	// Padding
	const int p = grid / 3;

	// Current score
	UtilTtf::getInstance(renderer)->render(lblScore, l, p,
										   UtilTtfAlign::CENTER);
	sprintf(numScoreStr, "%06d", numScore);
	UtilTtf::getInstance(renderer)->render(numScoreStr, l, p * 3,
										   UtilTtfAlign::CENTER);

	// Last score
	UtilTtf::getInstance(renderer)->render(lblLast, r, p,
										   UtilTtfAlign::CENTER);
	sprintf(numLastStr, "%06d", numLast);
	UtilTtf::getInstance(renderer)->render(numLastStr, r, p * 3,
										   UtilTtfAlign::CENTER);

	// High score
	UtilTtf::getInstance(renderer)->render(lblHigh, c, p,
										   UtilTtfAlign::CENTER);
	sprintf(numHighStr, "%06d", numHigh);
	UtilTtf::getInstance(renderer)->render(numHighStr, c, p * 3,
										   UtilTtfAlign::CENTER);
}

bool ScoreBarRenderer::addScore(int num) {
	numScore += num;
	if(numHigh < numScore) {
		numHigh = numScore;
		return true;
	}
	return false;
}

void ScoreBarRenderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void ScoreBarRenderer::drawLine(int fromX, int fromY, int toX, int toY) {
	SDL_RenderDrawLine(renderer, fromX, fromY, toX, toY);
}

void ScoreBarRenderer::drawRect(const SDL_Rect *rect) {
	SDL_RenderFillRect(renderer, rect);
}