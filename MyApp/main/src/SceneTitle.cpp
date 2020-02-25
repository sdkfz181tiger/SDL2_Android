#include "SceneTitle.h"

SceneTitle::SceneTitle(SDL_Window *window, SDL_Renderer *renderer,
					   const int windowW, const int windowH,
					   const int centerX, const int centerY) :
		SceneBase(window, renderer, windowW, windowH, centerX, centerY) {
	SDL_Log("SceneTitle()");
	this->init();
}

SceneTitle::~SceneTitle() {
	SDL_Log("~SceneTitle()");

	delete (sbRenderer);
	sbRenderer = nullptr;

	delete (btnTitle);
	btnTitle = nullptr;

	delete (btnGame);
	btnGame = nullptr;

	delete (btnResult);
	btnResult = nullptr;
}

bool SceneTitle::init() {
	SDL_Log("SceneTitle::init()");
	if (!SceneBase::init()) return false;

	// Ready
	ready();

	return true;
}

void SceneTitle::setFingerDown(const SDL_Event &event) {
	SDL_Point point = {0, 0};
	point.x = (int) (event.tfinger.x * windowW);
	point.y = (int) (event.tfinger.y * windowH);
	//SDL_Log("Down:%d, %d", point.x, point.y);

	// Buttons
	btnTitle->setFingerDown(point, event.tfinger.fingerId);
	btnGame->setFingerDown(point, event.tfinger.fingerId);
	btnResult->setFingerDown(point, event.tfinger.fingerId);
}

void SceneTitle::setFingerMotion(const SDL_Event &event) {
	SDL_Point point = {0, 0};
	point.x = (int) (event.tfinger.x * windowW);
	point.y = (int) (event.tfinger.y * windowH);
	//SDL_Log("Motion:%d, %d", point.x, point.y);

	// Buttons
	btnTitle->setFingerMotion(point, event.tfinger.fingerId);
	btnGame->setFingerMotion(point, event.tfinger.fingerId);
	btnResult->setFingerMotion(point, event.tfinger.fingerId);
}

void SceneTitle::setFingerUp(const SDL_Event &event) {
	SDL_Point point = {0, 0};
	point.x = (int) (event.tfinger.x * windowW);
	point.y = (int) (event.tfinger.y * windowH);
	//SDL_Log("Up:%d, %d", point.x, point.y);

	// Buttons
	btnTitle->setFingerUp(point, event.tfinger.fingerId);
	btnGame->setFingerUp(point, event.tfinger.fingerId);
	btnResult->setFingerUp(point, event.tfinger.fingerId);
}

void SceneTitle::render() {

	// UtilTimer
	UtilTimer::getInstance(renderer)->tictac();

	// Frame
	frame->render();

	// Background
	background->render();

	// ScoreBarRenderer
	sbRenderer->render();

	// Buttons
	btnTitle->render();
	btnGame->render();
	btnResult->render();
}

void SceneTitle::onBtnPressed(const BtnTag &tag) {
	SDL_Log("onBtnPressed");
}

void SceneTitle::onBtnReleased(const BtnTag &tag) {
	SDL_Log("onBtnReleased");
	switch (tag) {
		case BtnTag::TITLE:
			SDL_Log("TITLE!!");
			if (listener) listener->onSceneChange(SceneMode::TITLE);
			break;
		case BtnTag::GAME:
			SDL_Log("GAME!!");
			if (listener) listener->onSceneChange(SceneMode::GAME);
			break;
		case BtnTag::RESULT:
			SDL_Log("RESULT!!");
			if (listener) listener->onSceneChange(SceneMode::RESULT);
			break;
		default:
			break;
	}
}

void SceneTitle::ready() {

	// Levels
	UtilLevelData::getInstance(renderer)->reset();

	// Scores
	vector<int> &scores = UtilLocalSaves::getInstance(renderer)->getScores();
	vector<int> &highs = UtilLocalSaves::getInstance(renderer)->getHighs();

	// Score
	int score = 0;// Reset
	int last = (0 < scores.size()) ? scores.at(scores.size() - 1) : 0;
	int high = highs.at(0);

	for (int i = 0; i < scores.size(); i++) {
		SDL_Log("Score[%d]: %d", i, scores.at(i));
	}

	for (int i = 0; i < highs.size(); i++) {
		SDL_Log("High[%d]: %d", i, highs.at(i));
	}

	// ScoreBar
	sbRenderer = new ScoreBarRenderer(renderer, frame, grid);
	sbRenderer->setScore(score);
	sbRenderer->setLast(last);
	sbRenderer->setHigh(high);

	int btnY = frame->getMidY() + grid * 2;

	btnTitle = new BtnSprite(renderer, "images/btn_title.png",
							 frame->getMidX(), btnY,
							 80, 29, scale, BtnTag::TITLE);
	btnTitle->addEventListener(this);

	btnGame = new BtnSprite(renderer, "images/btn_start.png",
							frame->getMidX(), btnY + grid * 2,
							80, 29, scale, BtnTag::GAME);
	btnGame->addEventListener(this);

	btnResult = new BtnSprite(renderer, "images/btn_result.png",
							  frame->getMidX(), btnY + grid * 4,
							  80, 29, scale, BtnTag::RESULT);
	btnResult->addEventListener(this);

	// Test
	UtilLocalSaves::getInstance(renderer);
}