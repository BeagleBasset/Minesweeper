#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
class Grid
{
public:
	Grid();
	~Grid();
	void GridInit();
	void GridDraw();
	void SetGrid(int row, int col, int bombs);
	void BombPlacement();
	void BombCheck();
	bool RevealedUpdate();
	void DrawTiles(int cellnum, int posx, int posy);
	void RevealingCells(int row, int col);
	bool IsGameWin();
	void DrawAllCell();
	void ResetVectors();
	void GridDrawWin();
	int FlaggedCells{};
	Texture2D image;
	Vector2 DeathPos;
	bool GameStarted = false;
private:
	int Offset{ 75 };
	int CellSize{32};
	int RectSize{28};
	int NumCols{};
	int NumRows{};
	int NumBombs{};
	int ReveleadCells{};
	std::vector<std::vector<int>> GridVector;
	std::vector<std::vector<int>> Revealed;
	Texture2D image2;

};

