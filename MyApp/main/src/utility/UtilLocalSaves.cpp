#include "UtilLocalSaves.h"

// Singleton Object
static UtilLocalSaves *selfUtilLocalSaves = nullptr;

UtilLocalSaves::UtilLocalSaves(SDL_Renderer *renderer) :
		renderer(renderer), fileName("scores.json"),
		dateFormat("%Y/%m/%d %H:%M:%S"), rankin(-1) {
	SDL_Log("UtilLocalSaves()");
}

UtilLocalSaves::~UtilLocalSaves() {
	SDL_Log("~UtilLocalSaves()");
}

UtilLocalSaves *UtilLocalSaves::getInstance(SDL_Renderer *renderer) {

	if (!selfUtilLocalSaves) {
		selfUtilLocalSaves = new UtilLocalSaves(renderer);
		if (selfUtilLocalSaves && selfUtilLocalSaves->init()) {
			return selfUtilLocalSaves;
		} else {
			delete (selfUtilLocalSaves);
			selfUtilLocalSaves = nullptr;
		}
	}
	return selfUtilLocalSaves;
}

void UtilLocalSaves::destroyInstance() {
	if (!selfUtilLocalSaves) return;

	delete (selfUtilLocalSaves);
	selfUtilLocalSaves = nullptr;
}

bool UtilLocalSaves::init() {
	SDL_Log("UtilLocalSaves::init()");

	// Preference
	prefPath = SDL_GetPrefPath("Shimeji", "TAKOVADER");
	if (!prefPath) {
		SDL_Log("Error:%s", SDL_GetError());
		return false;
	}
	// FullPath
	fullPath += prefPath;
	fullPath += fileName;

	// Copy or Load
	if (!exists(fullPath.c_str())) {
		if (!load(fileName)) return false;
		if (!save()) return false;
		return true;
	}
	return load(fullPath.c_str());// From preference
}

bool UtilLocalSaves::exists(const char *path) {
	SDL_Log("UtilLocalSaves::exists() -> %s", path);
	// File
	SDL_RWops *fileObj = SDL_RWFromFile(path, "r");
	if (!fileObj) {
		SDL_Log("Error:%s", SDL_GetError());
		return false;
	}
	// Size 0 ?
	const auto size = (size_t) SDL_RWsize(fileObj);
	if (size <= 0) {
		SDL_RWclose(fileObj);
		return false;
	}
	SDL_RWclose(fileObj);
	return true;
}

bool UtilLocalSaves::load(const char *path) {
	SDL_Log("UtilLocalSaves::load() -> %s", path);

	// From preferences
	SDL_RWops *fileObj = SDL_RWFromFile(path, "r");
	if (!fileObj) {
		SDL_Log("Error:%s", SDL_GetError());
		return false;
	}

	// Read
	const auto size = (size_t) SDL_RWsize(fileObj);
	char jsonStr[size + 1];
	jsonStr[size] = '\0';// Terminal
	if (SDL_RWread(fileObj, jsonStr, size, 1) <= 0) {
		SDL_Log("Error:%s", SDL_GetError());
		SDL_RWclose(fileObj);
		return false;
	}

	// Parse
	string err;
	const auto jsonObj = Json::parse(jsonStr, err);
	if (!err.empty()) {
		SDL_Log("Error:%s", err.c_str());
		SDL_RWclose(fileObj);
		return false;
	}

	// Check
	SDL_Log("jsonStr:%s", jsonStr);

	// Date
	dateStr = jsonObj["date_str"].string_value();

	// Scores
	const Json::array &arrScores = jsonObj["scores"].array_items();
	for (int i = 0; i < arrScores.size(); i++) {
		scores.push_back(arrScores.at(i).int_value());
	}

	// Highs
	const Json::array &arrHighs = jsonObj["highs"].array_items();
	for (int i = 0; i < arrHighs.size(); i++) {
		highs.push_back(arrHighs.at(i).int_value());
	}

	SDL_RWclose(fileObj);
	return true;
}

bool UtilLocalSaves::save() {
	SDL_Log("UtilLocalSaves::save()");

	// File
	SDL_RWops *fileObj = SDL_RWFromFile(fullPath.c_str(), "w");
	if (!fileObj) {
		SDL_Log("Error:%s", SDL_GetError());
		return false;
	}

	// Current
	const time_t t = std::time(nullptr);
	char buffer[30];
	strftime(buffer, sizeof(buffer), dateFormat, localtime(&t));
	dateStr = buffer;

	// Scores, Highs
	Json::array scoreArr;
	for (int i = 0; i < scores.size(); i++) {
		scoreArr.push_back(scores.at(i));
	}

	Json::array highArr;
	for (int i = 0; i < highs.size(); i++) {
		highArr.push_back(highs.at(i));
	}

	// Json
	const Json jsonObj = Json::object{
			{"date_str", dateStr},
			{"scores",   scoreArr},
			{"highs",    highArr}
	};
	const string jsonStr = jsonObj.dump();

	// Write
	size_t size = SDL_strlen(jsonStr.c_str());
	if (SDL_RWwrite(fileObj, jsonStr.c_str(), 1, size) != size) {
		SDL_Log("Error:%s", SDL_GetError());
		SDL_RWclose(fileObj);
		return false;
	}

	SDL_RWclose(fileObj);
	return true;
}

int UtilLocalSaves::pushScore(const int num) {
	SDL_Log("UtilLocalSaves::pushScore() -> %d", num);

	// Scores
	scores.push_back(num);
	if (5 < scores.size()){
		scores.erase(scores.begin(), scores.end() - 5);
	}

	// Highs
	rankin = -1;
	for (int i = 0; i < highs.size(); i++) {
		if (num < highs.at(i)) continue;
		for (int d = highs.size() - 1; 0 < d; d--) {
			highs.at(d) = highs.at(d-1);
		}
		highs.at(i) = num;
		rankin = i;
		break;
	}
	return rankin;
}