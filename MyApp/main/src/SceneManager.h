#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "ozateck.h"
#include "DebugRenderer.h"
#include "SceneTitle.h"

class SceneManager : SceneModeListener {

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	int windowW, windowH;
	int centerX, centerY;

	DebugRenderer *dbgRenderer;
	vector<SceneBase *> scenes;

public:
	SceneManager(SDL_Window *window, SDL_Renderer *renderer);

	~SceneManager();

	bool init();

	bool loadAssets(const string &font,
					const vector<string> &images,
					const vector<string> &sounds);

	void setFingerDown(const SDL_Event &event);

	void setFingerMotion(const SDL_Event &event);

	void setFingerUp(const SDL_Event &event);

	void render();

	void onSceneChange(const SceneMode &mode) override;
};

#endif // _SCENEMANAGER_H_