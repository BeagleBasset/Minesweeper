#include "grid.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

Grid::Grid()
{
	image = LoadTexture("Graphic/flag.png");
	image2 = LoadTexture("Graphic/Mine.png");
	DeathPos = { 0,0 };
}

Grid::~Grid()
{
	UnloadTexture(image);
	UnloadTexture(image2);
}

void Grid::GridInit()
{
	BombPlacement();
	BombCheck();


	for (int i{ 0 }; i < NumRows; ++i) {
		for (int j{ 0 }; j < NumCols; ++j) {
			std::cout << GridVector[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Grid::GridDraw()
{
	Rectangle rectangle;
	for (int i{ 0 }; i < NumCols; ++i) {
		for (int j{ 0 }; j < NumRows; ++j) {
			rectangle = { (float)(CellSize * i), (float)(CellSize * j) + 75, (float)RectSize, (float)RectSize };
			if (Revealed[j][i] == 1) {
				DrawTiles(GridVector[j][i], CellSize * i, (CellSize * j) + Offset);
			}
			else {
				Vector2 mouseposition = GetMousePosition();
				if (CheckCollisionPointRec(mouseposition, rectangle)) {
					DrawRectangle((CellSize * i), (CellSize * j) + Offset, RectSize, RectSize, WHITE);
					if (Revealed[j][i] == 2)
						DrawTexture(image, CellSize * i, (CellSize * j) + Offset, WHITE);
				}
				else {
					if ((i + j) % 2 == 0) {
						DrawRectangle((CellSize * i), (CellSize * j) + Offset, RectSize, RectSize, DARKBLUE);
						if (Revealed[j][i] == 2)
							DrawTexture(image, CellSize * i, (CellSize * j) + Offset, WHITE);
					}
					else {
						DrawRectangle((CellSize * i), (CellSize * j) + Offset, RectSize, RectSize, BLUE);
						if (Revealed[j][i] == 2)
							DrawTexture(image, CellSize * i, (CellSize * j) + Offset, WHITE);
					}
				}
			}
			


		}
	}
}

void Grid::BombPlacement()
{
	Revealed.resize(NumRows, std::vector<int>(NumCols, 0)); // 0 : Hidden, 1 : Revelead, 2 : Flaged 
	GridVector.resize(NumRows, std::vector<int>(NumCols, 0));
	std::vector<std::pair<int, int>> positions;

	for (int row = 0; row < NumRows; ++row) {
		for (int col = 0; col < NumCols; ++col) {
			positions.emplace_back(row, col);
		}
	}
	std::srand(static_cast<unsigned int>(std::time(0)));
	std::random_shuffle(positions.begin(), positions.end(), [](int i) { return std::rand() % i; });

	for (int i = 0; i < NumBombs; ++i) {
		int row = positions[i].first;
		int col = positions[i].second;
		GridVector[row][col] = 9;
	}
}

void Grid::BombCheck()
{
	for (int row{}; row < NumRows; ++row) {
		for (int col{}; col < NumCols; ++col) {
			if (GridVector[row][col] == 9)
				continue;

			int bombcount = 0;
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					int checkrow = row + i;
					int checkcol = col + j;
					if (checkrow >= 0 && checkrow < NumRows && checkcol >= 0 && checkcol < NumCols) {
						if (GridVector[checkrow][checkcol] == 9)
							bombcount++;
					}
				}
			}
			GridVector[row][col] = bombcount;
		}
	}
}

bool Grid::RevealedUpdate()
{
	int mouse_x = GetMouseX() / CellSize;
	int mouse_y = (GetMouseY() - Offset) / CellSize;
	//std::cout << mouse_x << " " << mouse_y << std::endl;
	if (mouse_x >= 0 && mouse_x < NumCols && GetMouseY() >= Offset && mouse_y < NumRows) {
		//std::cout << "GAMEFIELD" << std::endl;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (GridVector[mouse_y][mouse_x] == 9 && Revealed[mouse_y][mouse_x] != 2) {
				DeathPos = { (float)mouse_x, (float)mouse_y };
				return false; //Gameover
			}
			if(Revealed[mouse_y][mouse_x] == 0){
				GameStarted = true;
				RevealingCells(mouse_y, mouse_x); //reveal
				//std::cout << Revealed[mouse_y][mouse_x] << std::endl;
			}
		}
		bool ispressed = true;
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && Revealed[mouse_y][mouse_x] == 0) {
			Revealed[mouse_y][mouse_x] = 2; //flagged
			//std::cout << Revealed[mouse_y][mouse_x] << std::endl;
			FlaggedCells++;
			ispressed = false;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && Revealed[mouse_y][mouse_x] == 2 && ispressed) {
			Revealed[mouse_y][mouse_x] = 0; //unflagged
			FlaggedCells--;
			//std::cout << Revealed[mouse_y][mouse_x] << std::endl;
		}

	}
	return true;

}

void Grid::DrawTiles(int cellnum, int posx, int posy)
{
	int textposx = posx + 7;
	int textposy = posy - 2;
	int textsize = 36;
	switch (cellnum) {
	case 0:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		break;
	case 1:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("1", textposx, textposy, textsize, ORANGE);
		break;
	case 2:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("2", textposx, textposy, textsize, DARKGREEN);
		break;
	case 3:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("3", textposx, textposy, textsize, RED);
		break;
	case 4:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("4", textposx, textposy, textsize, PINK);
		break;
	case 5:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("5", textposx, textposy, textsize, BROWN);
		break;
	case 6:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("6", textposx, textposy, textsize, LIGHTGRAY);
		break;
	case 7:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("7", textposx, textposy, 16, PURPLE);
		break;
	case 8:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawText("8", textposx, textposy, 16, BLACK);
		break;
	case 9:
		DrawRectangle(posx, posy, RectSize, RectSize, SKYBLUE);
		DrawTexture(image2, posx, posy, WHITE);
		break;
	}


}

void Grid::RevealingCells(int row, int col)
{
	if (row < 0 || row >= NumRows || col < 0 || col >= NumCols) {
		return;
	}

	if (Revealed[row][col] == 1 || Revealed[row][col] == 2) {
		return;
	}

	Revealed[row][col] = 1;

	if (GridVector[row][col] != 0) {
		return;
	}

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 || j != 0) {
				RevealingCells(row + i, col + j);
			}
		}
	}

}

bool Grid::IsGameWin()
{
	int numrevealed{ 0 };
	for (int row{ 0 }; row < NumRows; ++row) {
		for (int col{ 0 }; col < NumCols; ++col) {
			if (Revealed[row][col] == 1)
				numrevealed++;
		}
	}
	return (NumCols * NumRows) - numrevealed == NumBombs;
}

void Grid::DrawAllCell()
{
	for (int row{ 0 }; row < NumRows; ++row) {
		for (int col{ 0 }; col < NumCols; ++col) {
			if (row == DeathPos.y && col == DeathPos.x) {
				DrawRectangle((CellSize * col), (CellSize * row) + Offset, RectSize, RectSize, RED);
				DrawTexture(image2, CellSize * col, (CellSize * row) + Offset, WHITE);
			}
			else {
				DrawTiles(GridVector[row][col], CellSize * col, (CellSize * row) + Offset);
			}
		}
	}
}

void Grid::ResetVectors()
{
	GridVector.clear();
	Revealed.clear();
}

void Grid::GridDrawWin()
{
	for (int i{ 0 }; i < NumCols; ++i) {
		for (int j{ 0 }; j < NumRows; ++j) {
			if (Revealed[j][i] == 1) {
				DrawTiles(GridVector[j][i], CellSize * i, (CellSize * j) + Offset);
			}
			else {
				DrawRectangle((CellSize * i), (CellSize * j) + Offset, RectSize, RectSize, DARKBLUE);
				DrawTexture(image, CellSize * i, (CellSize * j) + Offset, WHITE);
			}

		}
		
	}
}

void Grid::SetGrid(int row, int col, int bombs)
{
	NumRows = row;
	NumCols = col;
	NumBombs = bombs;

}
