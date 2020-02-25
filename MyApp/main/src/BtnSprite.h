#ifndef _BTNSPRITE_H_
#define _BTNSPRITE_H_

#include "ozateck.h"

// Tag
enum class BtnTag {
	DEFAULT,
	OK, NO,
	LEFT, RIGHT, SHOT,
	TITLE, GAME, RESULT
};

// EventListener
class BtnEventListener {
public:
	virtual void onBtnPressed(const BtnTag &tag) = 0;

	virtual void onBtnReleased(const BtnTag &tag) = 0;
};

class BtnSprite {

private:
	SDL_Renderer *renderer;
	SDL_Surface *imgSurface;
	SDL_Texture *imgTexture;

	const char *path;
	const int x, y, w, h, scale;
	const BtnTag tag;
	SDL_FingerID fingerID;
	bool pressed;
	SDL_Rect srcRect, dstRect;

	// EventListener
	BtnEventListener *eventListener;

public:
	BtnSprite(SDL_Renderer *renderer, const char *path,
			  int x, int y, int w, int h, int scale, BtnTag tag);

	~BtnSprite();

	bool init();

	void addEventListener(BtnEventListener *eventListener);

	void removeEventListener();

	void setFingerDown(const SDL_Point &point, const SDL_FingerID &id);

	void setFingerMotion(const SDL_Point &point, const SDL_FingerID &id);

	void setFingerUp(const SDL_Point &point, const SDL_FingerID &id);

	bool isInside(const SDL_Point &point);

	void render();
};

#endif // _BTNSPRITE_H_