#include "SceneManager.h"

SceneManager::SceneManager(SDL_Window *window, SDL_Renderer *renderer) :
		window(window), renderer(renderer),
		windowW(0), windowH(0), dbgRenderer(nullptr) {
	SDL_Log("SceneManager()");
	this->init();
}

SceneManager::~SceneManager() {
	SDL_Log("~SceneManager()");

	delete (dbgRenderer);
	dbgRenderer = nullptr;

	for (auto scene : scenes) delete scene;
	scenes.clear();

	// Utilities
	UtilImagePool::getInstance(renderer)->destroyInstance();
	UtilLocalSaves::getInstance(renderer)->destroyInstance();
	UtilMath::getInstance(renderer)->destroyInstance();
	UtilSoundPool::getInstance(renderer)->destroyInstance();
	UtilThread::getInstance(renderer)->destroyInstance();
	UtilTimer::getInstance(renderer)->destroyInstance();
	UtilTtf::getInstance(renderer)->destroyInstance();
}

bool SceneManager::init() {
	SDL_Log("SceneManager::init()");

	// WindowSize
	SDL_GetWindowSize(window, &windowW, &windowH);
	centerX = windowW / 2;
	centerY = windowH / 2;

	// DebugRenderer
	dbgRenderer = new DebugRenderer(renderer, windowW, windowH, 40);

	// Assets
	const string font = "fonts/SpaceInvaders.ttf";
	const vector<string> images = {
			"images/btn_left.png",
			"images/btn_play.png",
			"images/btn_result.png",
			"images/btn_retry.png",
			"images/btn_right.png",
			"images/btn_shot.png",
			"images/btn_start.png",
			"images/btn_title.png",
	};
	const vector<string> sounds = {
			"sounds/bonus_01.wav",
			"sounds/exp_01.wav",
			"sounds/exp_02.wav",
			"sounds/gameclear_01.wav",
			"sounds/gameover_01.wav",
			"sounds/laser_01.wav",
			"sounds/ready_01.wav"
	};
	if (!loadAssets(font, images, sounds)) return false;

	// Title
	SceneBase *scene = new SceneTitle(window, renderer,
									  windowW, windowH,
									  centerX, centerY);
	scene->addSceneModeListener(this);
	scenes.push_back(scene);

	return true;
}

bool SceneManager::loadAssets(const string &font,
							  const vector<string> &images,
							  const vector<string> &sounds) {

	// Load font
	float s = (windowW / 1080.0F) * 42.0F;
	if (!UtilTtf::getInstance(renderer)->loadFont(font.c_str(), s)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font...");
		return false;
	}

	// Load image
	for (auto &path : images) {
		if (!UtilImagePool::getInstance(renderer)->loadImage(path.c_str())) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load image...");
			return false;
		}
	}

	// Load sound
	for (auto &path : sounds) {
		if (!UtilSoundPool::getInstance(renderer)->loadWav(path.c_str())) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load sound...");
			return false;
		}
	}

	return true;
}

void SceneManager::setFingerDown(const SDL_Event &event) {

	if (!scenes.empty()) scenes.back()->setFingerDown(event);
}

void SceneManager::setFingerMotion(const SDL_Event &event) {

	if (!scenes.empty()) scenes.back()->setFingerMotion(event);
}

void SceneManager::setFingerUp(const SDL_Event &event) {

	if (!scenes.empty()) scenes.back()->setFingerUp(event);
}

void SceneManager::render() {

	// Scenes
	if (!scenes.empty()) scenes.back()->render();

	// DebugRenderer
	dbgRenderer->render();// Debug
}

void SceneManager::onSceneChange(const SceneMode &mode) {
	SDL_Log("SceneManager::onSceneChange()");

	SceneBase *scene = nullptr;
	switch (mode) {
		case SceneMode::TITLE :
			SDL_Log("onSceneChange:TITLE!!");
			scene = new SceneTitle(window, renderer,
								   windowW, windowH,
								   centerX, centerY);
			break;
		case SceneMode::GAME :
			SDL_Log("onSceneChange:GAME!!");

			break;
		case SceneMode::RESULT :
			SDL_Log("onSceneChange:RESULT!!");

			break;
		default:
			break;
	}

	// Push
	if (!scene) return;
	scene->addSceneModeListener(this);
	scenes.push_back(scene);

	// Pop
	if (scenes.size() < 3) return;// 3 is very important!!
	auto itS = scenes.begin();
	auto *front = static_cast<SceneBase *>(*itS);
	delete (front);
	scenes.erase(itS);
}