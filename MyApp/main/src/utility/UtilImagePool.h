#ifndef _UTILIMAGEPOOL_H_
#define _UTILIMAGEPOOL_H_

#include "utility.h"

using namespace std;

// UtilImagePool
class UtilImagePool {

private:
	SDL_Renderer *renderer;
	map<string, SDL_Surface *> mapSurface;
	map<string, SDL_Texture *> mapTexture;

public:
	UtilImagePool(SDL_Renderer *renderer);

	~UtilImagePool();

	static UtilImagePool *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	bool loadImage(const char *path);

	void clearImage();

	SDL_Surface *getSurface(const char *path);

	SDL_Texture *getTexture(const char *path);
};

#endif // _UTILIMAGEPOOL_H_