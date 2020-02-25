#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "ozateck.h"
#include "SceneManager.h"

class GameManager {

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	Uint32 fpsRate;
	bool quitFlg;

	SceneManager *sManager;

public:
	GameManager();

	~GameManager();

	bool init();

	void renderClear();

	void renderCopy();

	void renderPresent();

	SDL_Window *getWindow();

	SDL_Renderer *getRenderer();

	void setFPS(Uint32 fps);

	Uint32 getFPS();

	void setQuit(bool flg);

	bool getQuit();

	void onFingerDown(const SDL_Event &event);

	void onFingerMotion(const SDL_Event &event);

	void onFingerUp(const SDL_Event &event);
};

#endif // _GAME_MANAGER_H_