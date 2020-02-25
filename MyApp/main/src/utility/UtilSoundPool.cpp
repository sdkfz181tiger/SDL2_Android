#include "UtilSoundPool.h"

// Singleton Object
static UtilSoundPool *selfUtilSoundPool = nullptr;

UtilSoundPool::UtilSoundPool(SDL_Renderer *renderer) : renderer(renderer) {
	SDL_Log("UtilSoundPool()");
}

UtilSoundPool::~UtilSoundPool() {
	SDL_Log("~UtilSoundPool()");
}

UtilSoundPool *UtilSoundPool::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilSoundPool) {
		selfUtilSoundPool = new UtilSoundPool(renderer);
		if (selfUtilSoundPool && selfUtilSoundPool->init()) {
			return selfUtilSoundPool;
		} else {
			delete (selfUtilSoundPool);
			selfUtilSoundPool = nullptr;
		}
	}
	return selfUtilSoundPool;
}

void UtilSoundPool::destroyInstance() {
	if (!selfUtilSoundPool) return;
	clearWav();// Clear all wav
	delete (selfUtilSoundPool);
	selfUtilSoundPool = nullptr;
}

bool UtilSoundPool::init() {
	SDL_Log("UtilSoundPool::init()");

	return true;
}

bool UtilSoundPool::loadWav(const char *path) {
	SDL_Log("loadWav:%s", path);

	if (mapWav.count(path) > 0) return false;
	Mix_Chunk *wav = Mix_LoadWAV(path);
	if (!wav) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Couldn't load wav: %s", Mix_GetError());
		return false;
	}
	mapWav[path] = wav;

	Mix_VolumeChunk(wav, MIX_MAX_VOLUME / 2);// Volume

	return true;
}

void UtilSoundPool::clearWav() {
	SDL_Log("clearWav");

	auto itC = mapWav.begin();
	while (itC != mapWav.end()) {
		auto pair = static_cast<std::pair<const string, Mix_Chunk *>>(*itC);
		Mix_FreeChunk(pair.second);
		SDL_Log("Destroy wav:%s", pair.first.c_str());
		itC++;
	}
	mapWav.clear();
}

void UtilSoundPool::play(const char *path, int loop = 0) {
	if (mapWav.count(path) <= 0) return;
	int channel = Mix_PlayChannel(-1, mapWav.at(path), loop);
}

void UtilSoundPool::halt() {
	Mix_HaltChannel(-1);
}
