#ifndef _UTILTTF_H_
#define _UTILTTF_H_

#include "utility.h"

using namespace std;

enum class UtilTtfAlign {
	DEFAULT,
	LEFT,
	RIGHT,
	CENTER
};

class UtilTtf {

private:
	SDL_Renderer *renderer;
	TTF_Font *ttfFont;
	map<char, SDL_Surface *> ttfSurfaceMap;
	map<char, SDL_Texture *> ttfTextureMap;
	int size, pad;

public:
	UtilTtf(SDL_Renderer *renderer);

	~UtilTtf();

	static UtilTtf *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	bool loadFont(const char *path, int size);

	void clearFont();

	void render(const string str, int x, int y,
				const UtilTtfAlign &align);
};

#endif // _UTILTTF_H_