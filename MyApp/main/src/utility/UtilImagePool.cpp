#include "UtilImagePool.h"

// Singleton Object
static UtilImagePool *selfUtilImagePool = nullptr;

UtilImagePool::UtilImagePool(SDL_Renderer *renderer) : renderer(renderer) {
	SDL_Log("UtilImagePool()");
}

UtilImagePool::~UtilImagePool() {
	SDL_Log("~UtilImagePool()");
}

UtilImagePool *UtilImagePool::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilImagePool) {
		selfUtilImagePool = new UtilImagePool(renderer);
		if (selfUtilImagePool && selfUtilImagePool->init()) {
			return selfUtilImagePool;
		} else {
			delete (selfUtilImagePool);
			selfUtilImagePool = nullptr;
		}
	}
	return selfUtilImagePool;
}

void UtilImagePool::destroyInstance() {
	if (!selfUtilImagePool) return;
	clearImage();// Clear all images
	delete (selfUtilImagePool);
	selfUtilImagePool = nullptr;
}

bool UtilImagePool::init() {
	SDL_Log("UtilImagePool::init()");

	return true;
}

bool UtilImagePool::loadImage(const char *path) {
	SDL_Log("loadImage:%s", path);

	if (mapSurface.count(path) > 0) return false;
	SDL_Surface *imgSurface = IMG_Load(path);
	if (!imgSurface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Couldn't load image: %s", IMG_GetError());
		return false;
	}
	mapSurface[path] = imgSurface;

	if (mapTexture.count(path) > 0) return false;
	SDL_Texture *imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
	if (!imgTexture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Couldn't create texture: %s", IMG_GetError());
		return false;
	}
	mapTexture[path] = imgTexture;

	return true;
}

void UtilImagePool::clearImage() {
	SDL_Log("clearImage");

	auto itT = mapTexture.begin();
	while (itT != mapTexture.end()) {
		auto pair = static_cast<std::pair<const string, SDL_Texture *>>(*itT);
		SDL_DestroyTexture(pair.second);
		SDL_Log("Destroy texture:%s", pair.first.c_str());
		itT++;
	}
	mapTexture.clear();

	auto itS = mapSurface.begin();
	while (itS != mapSurface.end()) {
		auto pair = static_cast<std::pair<const string, SDL_Surface *>>(*itS);
		SDL_FreeSurface(pair.second);
		SDL_Log("Destroy surface:%s", pair.first.c_str());
		itS++;
	}
	mapSurface.clear();
}

SDL_Surface *UtilImagePool::getSurface(const char *path) {
	if (mapSurface.count(path) <= 0) return nullptr;
	return mapSurface.at(path);
}

SDL_Texture *UtilImagePool::getTexture(const char *path) {
	if (mapTexture.count(path) <= 0) return nullptr;
	return mapTexture.at(path);
}