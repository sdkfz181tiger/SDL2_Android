#ifndef _UTILLOCALSAVES_H_
#define _UTILLOCALSAVES_H_

#include "utility.h"

using namespace std;

// UtilLocalSaves
class UtilLocalSaves {

private:
	SDL_Renderer *renderer;
	const char *fileName;
	const char *dateFormat;
	int rankin;
	char *prefPath;
	string fullPath, dateStr;
	vector<int> scores, highs;

public:
	UtilLocalSaves(SDL_Renderer *renderer);

	~UtilLocalSaves();

	static UtilLocalSaves *getInstance(SDL_Renderer *renderer);

	void destroyInstance();

	bool init();

	bool exists(const char *path);

	bool load(const char *path);

	bool save();

	int pushScore(const int num);

	int getRankin() { return rankin; }

	vector<int> &getScores() { return scores; }

	vector<int> &getHighs() { return highs; }
};

#endif // _UTILLOCALSAVES_H_