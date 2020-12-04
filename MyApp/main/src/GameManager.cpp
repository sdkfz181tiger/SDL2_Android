#include "GameManager.h"

GameManager::GameManager() : window(nullptr), renderer(nullptr), fpsRate(60), quitFlg(false) {
	SDL_Log("GameManager()");
	this->init();
}

GameManager::~GameManager() {
	SDL_Log("~GameManager()");

	delete (sManager);            // SceneManager
	sManager = nullptr;

	SDL_DestroyRenderer(renderer);// Destroy Renderer
	SDL_DestroyWindow(window);    // Destroy Window
	Mix_CloseAudio();             // Close Audio
	TTF_Quit();                   // Quit TTF
	SDL_Quit();                   // Quit SDL
}

bool GameManager::init() {
	SDL_Log("GameManager::init()");

	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Could not initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
			"Hello, SDL2!!",       // window title
			SDL_WINDOWPOS_UNDEFINED, // initial x position
			SDL_WINDOWPOS_UNDEFINED, // initial y position
			480,                     // width, in pixels
			320,                     // height, in pixels
			SDL_WINDOW_OPENGL     // flags - see below
	);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Could not create window: %s", SDL_GetError());
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Could not create renderer: %s", SDL_GetError());
		return false;
	}

	// Initialize Audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Could not open mixer: %s", Mix_GetError());
		return false;
	}

	// Initialize TTF
	if (TTF_Init() == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Could not initialize ttf: %s", TTF_GetError());
		return false;
	}

	// SceneManager
	sManager = new SceneManager(window, renderer);

	return true;
}

void GameManager::renderClear() {
	if (renderer == nullptr) return;

	// Draw background
	SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);

	// Clear the screen
	SDL_RenderClear(renderer);
}

void GameManager::renderCopy() {
	if (renderer == nullptr) return;

	// SceneManager
	sManager->render();
}

void GameManager::renderPresent() {
	if (renderer == nullptr) return;

	// Render to the screen
	SDL_RenderPresent(renderer);
}

SDL_Window *GameManager::getWindow() {
	return window;
}

SDL_Renderer *GameManager::getRenderer() {
	return renderer;
}

void GameManager::setFPS(Uint32 fps) {
	this->fpsRate = fps;
}

Uint32 GameManager::getFPS() {
	return fpsRate;
}

void GameManager::setQuit(bool flg) {
	this->quitFlg = flg;
}

bool GameManager::getQuit() {
	return quitFlg;
}

void GameManager::onFingerDown(const SDL_Event &event) {
	//SDL_Log("onFingerDown()");
	sManager->setFingerDown(event);
}

void GameManager::onFingerMotion(const SDL_Event &event) {
	//SDL_Log("onFingerMotion()");
	sManager->setFingerMotion(event);
}

void GameManager::onFingerUp(const SDL_Event &event) {
	//SDL_Log("onFingerUp()");
	sManager->setFingerUp(event);
}