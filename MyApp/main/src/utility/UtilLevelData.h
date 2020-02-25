#ifndef _UTILLEVEL_H_
#define _UTILLEVEL_H_

#include "utility.h"

using namespace std;

// UtilLevelData
class UtilLevelData {

private:
	SDL_Renderer *renderer;

	int score;
	int index;
	vector<int> cols;
	vector<int> rows;
	vector<int> intervalBonuses;
	vector<int> intervalAttacking;

public:
	UtilLevelData(SDL_Renderer *renderer);

	~UtilLevelData();

	static UtilLevelData *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	void reset();

	void next();

	void setScore(const int score);

	int getScore();

	int getRows();

	int getCols();

	int getIntervalBonuses();

	int getIntervalAttacking();
};

#endif // _UTILLEVEL_H_