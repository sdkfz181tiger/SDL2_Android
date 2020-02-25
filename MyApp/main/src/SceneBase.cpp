#include "SceneBase.h"

SceneBase::SceneBase(SDL_Window *window, SDL_Renderer *renderer,
					 const int windowW, const int windowH,
					 const int centerX, const int centerY) :
		window(window), renderer(renderer),
		windowW(windowW), windowH(windowH),
		centerX(centerX), centerY(centerY),
		scale(4), grid(32), listener(nullptr) {
	SDL_Log("SceneBase()");
}

SceneBase::~SceneBase() {
	SDL_Log("~SceneBase()");

	delete (frame);
	frame = nullptr;

	delete (background);
	background = nullptr;

	removeSceneModeListener();
}

bool SceneBase::init() {
	SDL_Log("SceneBase::init()");

	// Frame
	frame = new FrameSprite(renderer, windowW, windowH);

	// Background
	background = new StarBackground(renderer, windowW, windowH);

	// Scale, Grid
	float s = (windowW / 1080.0F) * 4.0F;
	scale = UtilMath::getInstance(renderer)->getRound(s);
	grid = frame->getWidth() / 12;

	// UtilTimer
	UtilTimer::getInstance(renderer);

	return true;
}

void SceneBase::onBtnPressed(const BtnTag &tag) {
	SDL_Log("onBtnPressed");
}

void SceneBase::onBtnReleased(const BtnTag &tag) {
	SDL_Log("onBtnReleased");
}

void SceneBase::addSceneModeListener(SceneModeListener *listener) {
	this->listener = listener;
}

void SceneBase::removeSceneModeListener() {
	this->listener = nullptr;
}