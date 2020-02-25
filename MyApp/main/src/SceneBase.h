#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "ozateck.h"
#include "FrameSprite.h"
#include "BtnSprite.h"
#include "StarBackground.h"

enum class SceneMode {
	DEFAULT,
	TITLE, GAME, RESULT
};

// SceneModeListener
class SceneModeListener {
public:
	virtual void onSceneChange(const SceneMode &mode) = 0;
};

class SceneBase : public BtnEventListener {

protected:
	SDL_Window *window;
	SDL_Renderer *renderer;
	const int windowW, windowH;
	const int centerX, centerY;

	FrameSprite *frame;
	StarBackground *background;
	int scale, grid;
	SceneModeListener *listener;

public:
	SceneBase(SDL_Window *window, SDL_Renderer *renderer,
			  const int windowW, const int windowH,
			  const int centerX, const int centerY);

	virtual ~SceneBase();

	virtual bool init();

	virtual void setFingerDown(const SDL_Event &event) = 0;

	virtual void setFingerMotion(const SDL_Event &event) = 0;

	virtual void setFingerUp(const SDL_Event &event) = 0;

	virtual void render() = 0;

	void onBtnPressed(const BtnTag &tag) override;

	void onBtnReleased(const BtnTag &tag) override;

	void addSceneModeListener(SceneModeListener *listener);

	void removeSceneModeListener();
};

#endif // _SCENEBASE_H_