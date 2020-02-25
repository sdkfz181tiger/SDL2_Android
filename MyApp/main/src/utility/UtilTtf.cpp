#include "UtilTtf.h"

// Singleton Object
static UtilTtf *selfUtilTtf = nullptr;

UtilTtf::UtilTtf(SDL_Renderer *renderer) : renderer(renderer), size(42) {
	SDL_Log("UtilTtf()");
}

UtilTtf::~UtilTtf() {
	SDL_Log("~UtilTtf()");
}

UtilTtf *UtilTtf::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilTtf) {
		selfUtilTtf = new UtilTtf(renderer);
		if (selfUtilTtf && selfUtilTtf->init()) {
			return selfUtilTtf;
		} else {
			delete (selfUtilTtf);
			selfUtilTtf = nullptr;
		}
	}
	return selfUtilTtf;
}

bool UtilTtf::init() {
	SDL_Log("UtilTtf::init()");

	return true;
}

void UtilTtf::destroyInstance() {
	if (!selfUtilTtf) return;
	clearFont();// Clear all font
	delete (selfUtilTtf);
	selfUtilTtf = nullptr;
}

bool UtilTtf::loadFont(const char *path, int size) {
	// Font
	ttfFont = TTF_OpenFont(path, size);
	if (!ttfFont) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					 "Unable to load font: %s", TTF_GetError());
		return false;
	}

	const string str = " 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,:;!?_@+-*/%=()[]<>";
	const SDL_Color textColor = {255, 255, 255, 255};
	for (unsigned i = 0; i < str.length(); i++) {
		const string s = str.substr(i, 1);// Important!!
		SDL_Surface *ttfSurface = TTF_RenderText_Solid(ttfFont, s.c_str(), textColor);
		SDL_Texture *ttfTexture = SDL_CreateTextureFromSurface(renderer, ttfSurface);
		ttfSurfaceMap[str[i]] = ttfSurface;
		ttfTextureMap[str[i]] = ttfTexture;
	}

	// Size
	this->size = size;
	this->pad = size - ttfSurfaceMap[str[0]]->w;

	return true;
}

void UtilTtf::clearFont() {
	SDL_Log("UtilTtf::clearFont()");

	auto itT = ttfTextureMap.begin();
	while (itT != ttfTextureMap.end()) {
		SDL_DestroyTexture(itT->second);
		itT++;
	}
	ttfTextureMap.clear();

	auto itS = ttfSurfaceMap.begin();
	while (itS != ttfSurfaceMap.end()) {
		SDL_FreeSurface(itS->second);
		itS++;
	}
	ttfSurfaceMap.clear();

	TTF_CloseFont(ttfFont);
}

void UtilTtf::render(const string str, int x, int y,
					 const UtilTtfAlign &align) {

	if (ttfSurfaceMap.empty()) return;
	if (ttfTextureMap.empty()) return;

	switch (align) {
		case UtilTtfAlign::LEFT:
			// Do nothing
			break;
		case UtilTtfAlign::RIGHT:
			x -= str.length() * size;
			break;
		case UtilTtfAlign::CENTER:
			x -= (str.length() - 1) * size / 2 + pad / 2;
			break;
		default:
			break;
	}

	SDL_Rect rect;
	unsigned offset = 0;
	for (unsigned i = 0; i < str.length(); i++) {
		const char &c = str.at(i);
		rect.x = x + offset;
		rect.y = y;
		rect.w = ttfSurfaceMap.at(c)->w;
		rect.h = ttfSurfaceMap.at(c)->h;
		offset += size;
		if (isspace(c)) continue;
		SDL_RenderCopy(renderer, ttfTextureMap.at(c), nullptr, &rect);
	}
}