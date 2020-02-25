#include "BtnSprite.h"

BtnSprite::BtnSprite(SDL_Renderer *renderer, const char *path,
					 int x, int y, int w, int h, int scale, BtnTag tag) :
		renderer(renderer), path(path), x(x), y(y), w(w), h(h), scale(scale),
		tag(tag), fingerID(-1), pressed(false), eventListener(nullptr) {
	SDL_Log("BtnSprite():%s", path);
	this->init();
}

BtnSprite::~BtnSprite() {
	SDL_Log("~BtnSprite()");
	// Delete SDL_Surface, SDL_Texture objects
	imgTexture = nullptr;
	imgSurface = nullptr;
}

bool BtnSprite::init() {
	SDL_Log("BtnSprite::init()");

	imgSurface = UtilImagePool::getInstance(renderer)->getSurface(path);
	if (!imgSurface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Couldn't get image:%s", path);
		return false;
	}

	imgTexture = UtilImagePool::getInstance(renderer)->getTexture(path);
	if (!imgTexture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Couldn't get texture:%s", path);
		return false;
	}

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = w;
	srcRect.h = h;

	dstRect.x = x - w * scale / 2;
	dstRect.y = y - h / 2;
	dstRect.w = w * scale;
	dstRect.h = h * scale;

	return true;
}

void BtnSprite::addEventListener(BtnEventListener *eventListener) {
	this->eventListener = eventListener;
}

void BtnSprite::removeEventListener() {
	this->eventListener = nullptr;
}

void BtnSprite::setFingerDown(const SDL_Point &point, const SDL_FingerID &id) {
	if (!isInside(point)) return;
	fingerID = id;
	if (pressed) return;
	pressed = true;
	if (eventListener) eventListener->onBtnPressed(tag);
}

void BtnSprite::setFingerMotion(const SDL_Point &point, const SDL_FingerID &id) {
	if (isInside(point)) {
		fingerID = id;
		if (pressed) return;
		pressed = true;
		if (eventListener) eventListener->onBtnPressed(tag);
	} else {
		if (fingerID != id) return;
		if (!pressed) return;
		pressed = false;
		if (eventListener) eventListener->onBtnReleased(tag);
	}
}

void BtnSprite::setFingerUp(const SDL_Point &point, const SDL_FingerID &id) {
	if (!isInside(point)) return;
	if (fingerID != id) return;
	fingerID = -1;
	if (!pressed) return;
	pressed = false;
	if (eventListener) eventListener->onBtnReleased(tag);
}

bool BtnSprite::isInside(const SDL_Point &point) {
	if (point.x < dstRect.x) return false;
	if (point.y < dstRect.y) return false;
	if (dstRect.x + dstRect.w < point.x) return false;
	if (dstRect.y + dstRect.h < point.y) return false;
	return true;
}

void BtnSprite::render() {

	if (pressed) {
		srcRect.x = w;
	} else {
		srcRect.x = 0;
	}

	SDL_RenderCopy(renderer, imgTexture, &srcRect, &dstRect);
}