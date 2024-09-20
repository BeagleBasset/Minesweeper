#pragma once
#include <raylib.h>
#include <vector>
#include "grid.hpp"
#include "difficulty.hpp"

class Game {
public:
	Game();
	~Game();
	void StartWindow();
	void UpdateStart();
	void GameWindow();
	void Update();
	void WinScreenUpdate();
	void LoseScreenUpdate();
	void SetDifficulty();
	void LoadHighScore();
	void SaveHighScore();
	std::vector<int> GetGameTime();
	void ResetTime();
	int GameState{ 0 };
	int BestTime{ 0 };
	bool isGame = false;
	bool isInGame = true;
	bool isVictory = false;
	bool isLose = false;
	bool isStartInit = false;
	bool isSetWindowNeed = true;
	bool isEasy = false;
	bool isNormal = false;
	bool isHard = false;

private:
	int GameScreenWidth{};
	int GameScreenHeigth{};
	int Row{};
	int Col{};
	int CellSize{ 32 };
	int StartTime{ -1 };
	int ElapsedTime{};
	bool isOpen = false;
	bool isMouseButtonDown = false;
	std::vector<int> ActualDifficult; //row, col, mine
	Grid grid;
	Difficulty easy;
	Difficulty normal;
	Difficulty hard;
	Texture2D clock;
	Texture2D trophy;
	Button newgame;
	Button changediff;


};