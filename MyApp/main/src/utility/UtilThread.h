#ifndef _UTILTHREAD_H_
#define _UTILTHREAD_H_

#include "utility.h"

using namespace std;

// UtilThread
class UtilThread {

private:
	SDL_Renderer *renderer;

public:
	UtilThread(SDL_Renderer *renderer);

	~UtilThread();

	static UtilThread *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	void test();
};

#endif // _UTILTHREAD_H_