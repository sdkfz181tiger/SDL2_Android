#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "ozateck.h"
#include "SceneBase.h"
#include "ScoreBarRenderer.h"

class SceneTitle : public SceneBase {

private:
	ScoreBarRenderer *sbRenderer;
	BtnSprite *btnTitle, *btnGame, *btnResult;

public:
	SceneTitle(SDL_Window *window, SDL_Renderer *renderer,
			   const int windowW, const int windowH,
			   const int centerX, const int centerY);

	~SceneTitle() override;

	bool init() override;

	void setFingerDown(const SDL_Event &event) override;

	void setFingerMotion(const SDL_Event &event) override;

	void setFingerUp(const SDL_Event &event) override;

	void render() override;

	void onBtnPressed(const BtnTag &tag) override;

	void onBtnReleased(const BtnTag &tag) override;

	// Ready
	void ready();
};

#endif // _SCENETITLE_H_