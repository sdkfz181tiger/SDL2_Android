#include "ozateck.h"

#include "GameManager.h"

int SDL_main(int argc, char *argv[]) {
	SDL_Log("SDL_main()");

	// GameManager
	GameManager *gameManager = new GameManager();
	SDL_Window *window = gameManager->getWindow();
	SDL_Renderer *renderer = gameManager->getRenderer();

	// FPS
	const Uint32 fps = 1000 / gameManager->getFPS();
	Uint32 ticks = SDL_GetTicks();

	// Event loop
	SDL_Event event;
	while (!gameManager->getQuit()) {

		//==========
		// Events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					gameManager->setQuit(true);// Quit
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_AC_BACK) {
						gameManager->setQuit(true);// Quit
					}
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						gameManager->setQuit(true);// Quit
					}
					break;
				case SDL_FINGERDOWN:
					gameManager->onFingerDown(event);
					break;
				case SDL_FINGERMOTION:
					gameManager->onFingerMotion(event);
					break;
				case SDL_FINGERUP:
					gameManager->onFingerUp(event);
					break;
				default:
					break;
			}
		}

		//==========
		// Render
		gameManager->renderClear();

		// Copy
		gameManager->renderCopy();

		// FPS
		Uint32 passed = SDL_GetTicks() - ticks;
		if (passed < fps) SDL_Delay(fps - passed);
		ticks = SDL_GetTicks();

		// Present
		gameManager->renderPresent();
	}

	delete (gameManager);
	gameManager = nullptr;

	return 0;
}