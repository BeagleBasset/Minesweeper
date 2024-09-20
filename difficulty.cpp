#include "difficulty.hpp"

Difficulty::Difficulty(std::string name, int rows, int cols, int mines, Vector2 position)
	:button(name, position)
{
	Name = name;
	Rows = rows;
	Cols = cols;
	Mines = mines;
	ButtonPosition = position;
	
}

std::vector<int> Difficulty::DifficultyParams()
{
	std::vector<int> parameters({ Rows, Cols, Mines });
	return parameters;
}

int Difficulty::LoadHighScoreFromFile()
{
	std::string sfilename = Name + ".txt";
	//std::cout << sfilename << std::endl;
	const char* filename = sfilename.c_str();
	int loadedHighscore = 0;
	std::ifstream highscoreFile(filename);
	if (highscoreFile.is_open()) {
		highscoreFile >> loadedHighscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to load highscore from file." << std::endl;
	}
	return loadedHighscore;

	return 0;
}

void Difficulty::SaveHighScoreToFile(int highscore)
{
	std::string sfilename = Name + ".txt";
	std::cout << sfilename << std::endl;
	const char* filename = sfilename.c_str();
	std::ofstream highscoreFile(filename);
	if (highscoreFile.is_open()) {
		highscoreFile << highscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to save highscore to file" << std::endl;
	}
}
