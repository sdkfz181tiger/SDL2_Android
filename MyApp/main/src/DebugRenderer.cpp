#include "DebugRenderer.h"

DebugRenderer::DebugRenderer(SDL_Renderer *renderer, int windowW, int windowH,
							 int gridSize) : renderer(renderer), windowW(windowW),
											 windowH(windowH), gridSize(gridSize),
											 tickTime(0), tickInterval(0), tickCounter(0),
											 fpsPad(10) {
	SDL_Log("DebugRenderer():%dx%d, gridSize:%d", windowW, windowH, gridSize);
	this->init();
}

DebugRenderer::~DebugRenderer() {
	SDL_Log("~DebugRenderer()");
}

bool DebugRenderer::init() {
	SDL_Log("SprDebugRendererite::init()");
	tickTime = SDL_GetTicks();// Ticks
	tickInterval = tickTime;  // Interval
	return true;
}

void DebugRenderer::render() {

	const int offset = 5;
	const int rows = windowH / gridSize;
	const int cols = windowW / gridSize;

	// Draw center lines
	this->setColor(100, 255, 100);
	this->drawLine(0, windowH / 2, windowW, windowH / 2);
	this->drawLine(windowW / 2, 0, windowW / 2, windowH);

	// Draw horizontal lines
	for (int r = 1; r < rows; r++) {
		if (r % offset != 0) {
			this->setColor(100, 100, 100);
		} else {
			this->setColor(255, 200, 200);
		}
		this->drawLine(0, r * gridSize, windowW, r * gridSize);
	}

	// Draw vertical lines
	for (int c = 1; c < cols; c++) {
		if (c % offset != 0) {
			this->setColor(100, 100, 100);
		} else {
			this->setColor(255, 200, 200);
		}
		this->drawLine(c * gridSize, 0, c * gridSize, windowH);
	}

	// Graph
	this->drawGraph();

	// FPS
	this->drawFPS();
}

void DebugRenderer::drawGraph() {

	for (int i = 0; i < fpsData.size(); i++) {
		int fps = fpsData.at(i);
		if (fps < 56) {
			setColor(255, 100, 100);
		} else if (fps < 58) {
			setColor(100, 255, 100);
		} else {
			setColor(100, 100, 255);
		}
		const int x = (fpsData.size() * fpsPad) - (i * fpsPad) - fpsPad;
		const int h = fpsData.at(i) * -2;
		SDL_Rect rect{x, windowH, fpsPad, h};
		this->drawRect(&rect);
	}

	const int fpsBars = windowW / fpsPad;
	if (fpsBars < fpsData.size()) {
		fpsData.erase(fpsData.begin());
	}
}

void DebugRenderer::drawFPS() {
	// FPS
	const int tickDelay = SDL_GetTicks() - tickTime;
	const int tickFPS = 1000 / tickDelay;
	sprintf(fpsStr, "FPS:%02d", tickFPS);
	UtilTtf::getInstance(renderer)->render(fpsStr, 0, windowH * 0.9,
										   UtilTtfAlign::LEFT);
	tickTime = SDL_GetTicks();

	// Interval
	if (SDL_GetTicks() - tickInterval < 1000) {
		tickCounter++;
	} else {
		fpsData.push_back(tickCounter);
		tickInterval = SDL_GetTicks();
		tickCounter = 0;
	}
}

void DebugRenderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void DebugRenderer::drawLine(int fromX, int fromY, int toX, int toY) {
	SDL_RenderDrawLine(renderer, fromX, fromY, toX, toY);
}

void DebugRenderer::drawRect(const SDL_Rect *rect) {
	SDL_RenderFillRect(renderer, rect);
}