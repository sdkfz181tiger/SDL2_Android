#include "UtilThread.h"

// Singleton Object
static UtilThread *selfUtilThread = nullptr;

UtilThread::UtilThread(SDL_Renderer *renderer) : renderer(renderer) {
	SDL_Log("UtilThread()");
}

UtilThread::~UtilThread() {
	SDL_Log("~UtilThread()");
}

UtilThread *UtilThread::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilThread) {
		selfUtilThread = new UtilThread(renderer);
		if (selfUtilThread && selfUtilThread->init()) {
			return selfUtilThread;
		} else {
			delete (selfUtilThread);
			selfUtilThread = nullptr;
		}
	}
	return selfUtilThread;
}

void UtilThread::destroyInstance() {
	if (!selfUtilThread) return;

	delete (selfUtilThread);
	selfUtilThread = nullptr;
}

bool UtilThread::init() {
	SDL_Log("UtilThread::init()");

	return true;
}

void UtilThread::test() {
	SDL_Log("UtilThread::test()");

	// TODO: this is test!!
	int result = 0;

	SDL_Thread *thread = SDL_CreateThread([](void *data) -> int {
		SDL_threadID id = SDL_GetThreadID(nullptr);
		SDL_Log("SDL_threadID(start):%lu", id);
		for (unsigned i = 0; i < 1000000; i++) {
			if (i % 100000 == 0) SDL_Log("i:%d", i);
		}
		return 999;
	}, "Test!!", nullptr);
	SDL_WaitThread(thread, &result);
	SDL_Log("SDL_threadID(result):%d", result);
}