#include "UtilTimer.h"

// Singleton Object
static UtilTimer *selfUtilTimer = nullptr;

// Timer
Timer::Timer(int interval, int repeat, function<void()> callback) :
		running(false), counter(0), interval(interval),
		repeat(repeat), callback(callback) {
	SDL_Log("TickTac()");
}

Timer::~Timer() {
	SDL_Log("~TickTac()");
}

void Timer::tictac() {
	if (!running) return;
	// Counter
	if (++counter < interval) return;
	counter = 0;

	callback();// Callback

	// Repeat
	if (repeat < 0) return;
	if (0 < --repeat) return;
	running = false;
}

void Timer::start() {
	if (running) return;
	running = true;
}

void Timer::stop() {
	running = false;
}

bool Timer::getRunning() {
	return running;
}

// UtilTimer
UtilTimer::UtilTimer(SDL_Renderer *renderer) : renderer(renderer) {
	SDL_Log("UtilTimer()");
}

UtilTimer::~UtilTimer() {
	SDL_Log("~UtilTimer()");
}

UtilTimer *UtilTimer::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilTimer) {
		selfUtilTimer = new UtilTimer(renderer);
		if (selfUtilTimer && selfUtilTimer->init()) {
			return selfUtilTimer;
		} else {
			delete (selfUtilTimer);
			selfUtilTimer = nullptr;
		}
	}
	return selfUtilTimer;
}

void UtilTimer::destroyInstance() {
	if (!selfUtilTimer) return;
	this->clearTimer();// Clear all timer
	delete (selfUtilTimer);
	selfUtilTimer = nullptr;
}

bool UtilTimer::init() {
	SDL_Log("UtilTimer::init()");

	return true;
}

void UtilTimer::tictac() {

	if (timers.empty()) return;

	vector<Timer *>::iterator it = timers.end();
	while (it != timers.begin()) {
		it--;
		Timer *timer = static_cast<Timer *>(*it);
		timer->tictac();
		if (timer->getRunning()) continue;
		timers.erase(it);
		delete (timer);
		timer = nullptr;
	}
}

void UtilTimer::pushTimer(int interval, int repeat, function<void()> callback) {
	SDL_Log("UtilTimer::pushTimer()");
	// Timer
	Timer *timer = new Timer(interval, repeat, callback);
	timer->start();
	timers.push_back(timer);
}

void UtilTimer::clearTimer() {
	SDL_Log("UtilTimer::clearTimer()");

	auto it = timers.begin();
	while (it != timers.end()) {
		auto *timer = static_cast<Timer *>(*it);
		delete (timer);
		it++;
	}
	timers.clear();
}

unsigned UtilTimer::getSize() {
	return timers.size();
}