#ifndef _UTILTIMER_H_
#define _UTILTIMER_H_

#include "utility.h"

using namespace std;

// Timer
class Timer {

private:

	bool running;
	int counter, interval, repeat;
	function<void()> callback;

public:
	Timer(int interval, int repeat, function<void()> callback);

	~Timer();

	void tictac();

	void start();

	void stop();

	bool getRunning();
};

// UtilTimer
class UtilTimer {

private:
	SDL_Renderer *renderer;
	vector<Timer *> timers;

public:
	UtilTimer(SDL_Renderer *renderer);

	~UtilTimer();

	static UtilTimer *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	void tictac();

	void pushTimer(int interval, int repeat, function<void()> callback);

	void clearTimer();

	unsigned getSize();
};

#endif // _UTILTIMER_H_