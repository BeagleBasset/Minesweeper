#pragma once
#include <raylib.h>
#include "button.hpp"
#include <string>
#include <vector>
#include <fstream>

class Difficulty
{
public:
	Difficulty(std::string name, int rows, int cols, int mines, Vector2 position);
	std::vector<int> DifficultyParams();
	Button button;
	int LoadHighScoreFromFile();
	void SaveHighScoreToFile(int highscore);

private:
	std::string Name;
	int Rows{};
	int Cols{};
	int Mines{};
	Vector2 ButtonPosition;

};

