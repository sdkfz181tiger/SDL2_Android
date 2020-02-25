#include "UtilLevelData.h"

// Singleton Object
static UtilLevelData *selfUtilLevelData = nullptr;

UtilLevelData::UtilLevelData(SDL_Renderer *renderer) :
		renderer(renderer), score(0), index(0) {
	SDL_Log("UtilLevelData()");
}

UtilLevelData::~UtilLevelData() {
	SDL_Log("~UtilLevelData()");
}

UtilLevelData *UtilLevelData::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilLevelData) {
		selfUtilLevelData = new UtilLevelData(renderer);
		if (selfUtilLevelData && selfUtilLevelData->init()) {
			return selfUtilLevelData;
		} else {
			delete (selfUtilLevelData);
			selfUtilLevelData = nullptr;
		}
	}
	return selfUtilLevelData;
}

void UtilLevelData::destroyInstance() {
	if (!selfUtilLevelData) return;

	delete (selfUtilLevelData);
	selfUtilLevelData = nullptr;
}

bool UtilLevelData::init() {
	SDL_Log("UtilLevelData::init()");

	score = 0;
	index = 0;
	rows = {1, 3, 3, 3, 4, 4, 4, 5, 5, 5};
	cols = {1, 7, 8, 9, 7, 8, 9, 7, 8, 9};
	intervalBonuses = {1, 16, 14, 12, 10, 8, 6, 4, 4, 4};
	intervalAttacking = {1, 3, 3, 2, 3, 3, 2, 2, 2, 1};

	return true;
}

void UtilLevelData::reset() {
	score = 0;
	index = 0;
}

void UtilLevelData::next() {
	index++;
	if (rows.size() - 1 < index) index = 0;
	if (cols.size() - 1 < index) index = 0;
}

void UtilLevelData::setScore(const int score) {
	this->score = score;
}

int UtilLevelData::getScore() {
	return this->score;
}

int UtilLevelData::getRows() {
	if (rows.size() - 1 < index) return 0;
	return rows.at(index);
}

int UtilLevelData::getCols() {
	if (cols.size() - 1 < index) return 0;
	return cols.at(index);
}

int UtilLevelData::getIntervalBonuses() {
	if (intervalBonuses.size() - 1 < index) return 1;
	return intervalBonuses.at(index);
}

int UtilLevelData::getIntervalAttacking() {
	if (intervalAttacking.size() - 1 < index) return 1;
	return intervalAttacking.at(index);
}