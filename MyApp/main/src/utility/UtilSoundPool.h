#ifndef _UTILSOUNDPOOL_H_
#define _UTILSOUNDPOOL_H_

#include "utility.h"

using namespace std;

// UtilSoundPool
class UtilSoundPool {

private:
	SDL_Renderer *renderer;
	map<string, Mix_Chunk *> mapWav;

public:
	UtilSoundPool(SDL_Renderer *renderer);

	~UtilSoundPool();

	static UtilSoundPool *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	bool loadWav(const char *path);

	void clearWav();

	void play(const char *path, int loop);

	void halt();
};

#endif // _UTILSOUNDPOOL_H_