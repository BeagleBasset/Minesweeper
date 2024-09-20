#include "game.hpp"

Game::Game()
	:easy("Easy",9,9,10,{195, 80}),
	normal("Normal",16,16,40,{195,160}),
	hard("Hard",16,30,99,{195,240}),
	newgame("New",{10, (float)GameScreenHeigth}),
	changediff("Change", { 148, (float)GameScreenHeigth })
{
	//grid = Grid();
	clock = LoadTexture("Graphic/Clock.png");
	trophy = LoadTexture("Graphic/Trophy.png");
}

Game::~Game()
{
	UnloadTexture(clock);
}

void Game::StartWindow()
{
	SetWindowSize(500, 400);
	isSetWindowNeed = true;
}

void Game::UpdateStart()
{
	DrawText("Minesweeper", 135, 10, 40, WHITE);
	SetDifficulty();


}

void Game::GameWindow()
{
	ResetTime();
	grid.FlaggedCells = 0;
	GameScreenWidth = ActualDifficult[1] * CellSize;
	GameScreenHeigth = (ActualDifficult[0] * CellSize) + 150;
	grid.ResetVectors();
	grid.SetGrid(ActualDifficult[0], ActualDifficult[1], ActualDifficult[2]);
	if (isSetWindowNeed) {
		SetWindowSize(GameScreenWidth, GameScreenHeigth);
		isSetWindowNeed = false;
	}
	newgame.SetPosition({ 10, (float)GameScreenHeigth - 69 });
	changediff.SetPosition({ 148, (float)GameScreenHeigth - 69 });
	grid.GridInit();
	//clock = LoadTexture("Graphic/Clock.png");


}

void Game::Update()
{

	isVictory = false;
	isLose = false;
	std::vector<int> time = GetGameTime();
	DrawRectangle(0, 0, GameScreenWidth, 73, SKYBLUE);
	DrawRectangle(0, GameScreenHeigth - 73, GameScreenWidth, 73, SKYBLUE);
	DrawTexture(grid.image, 0, 22, WHITE);
	DrawText(TextFormat("%d", grid.FlaggedCells), 40, 20, 40, WHITE);
	DrawTexture(clock, GameScreenWidth - 140, 22, WHITE);
	DrawText(TextFormat("%02d:%02d", time[0],time[1]), GameScreenWidth - 110,  20, 40, WHITE);
	newgame.DrawButton();
	changediff.DrawButton();
	if (newgame.UpdateButton() && !isMouseButtonDown) {
		isGame = false;
		
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		isMouseButtonDown = true;
	else
		isMouseButtonDown = false;

	if (changediff.UpdateButton()) {
		isGame = false;
		GameState = 0;
		isStartInit = false;
	}
	grid.GridDraw();
	if (!grid.RevealedUpdate()) {
		std::cout << "GAMEOVER" << std::endl;
		isInGame = false;
		isLose = true;
	}
	if (grid.IsGameWin()) {
		std::cout << "WIN" << std::endl;
		isInGame = false;
		isVictory = true;
	}
	
	
}

void Game::WinScreenUpdate()
{

	int minute = ElapsedTime / 60;
	int sec = ElapsedTime % 60;
	if (!isOpen) {
		LoadHighScore();
		isOpen = true;
	}
	if (ElapsedTime < BestTime) {
		BestTime = ElapsedTime;
		SaveHighScore();
	}
	int minute2 = BestTime / 60;
	int sec2 = BestTime% 60;
	DrawRectangle(0, 0, GameScreenWidth, 73, SKYBLUE);
	DrawRectangle(0, GameScreenHeigth - 73, GameScreenWidth, 73, SKYBLUE);
	DrawTexture(clock, 0, 22, WHITE);
	DrawText(TextFormat("%02d:%02d", minute, sec), 40, 20, 40, WHITE);
	DrawTexture(trophy, GameScreenWidth - 140, 22, WHITE);
	DrawText(TextFormat("%02d:%02d", minute2, sec2), GameScreenWidth - 105, 20, 40, WHITE);
	newgame.DrawButton();
	changediff.DrawButton();
	if (newgame.UpdateButton() && !isMouseButtonDown) {
		isGame = false;
		isInGame = true;
		isOpen = false;
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		isMouseButtonDown = true;
	else
		isMouseButtonDown = false;
	if (changediff.UpdateButton()) {
		isGame = false;
		GameState = 0;
		isInGame = true;
		isStartInit = false;
		isOpen = false;
	}

	grid.GridDrawWin();
}

void Game::LoseScreenUpdate()
{
	DrawRectangle(0, 0, GameScreenWidth, 73, SKYBLUE);
	DrawRectangle(0, GameScreenHeigth - 73, GameScreenWidth, 73, SKYBLUE);
	DrawTexture(clock, 0, 22, WHITE);
	DrawText("FAILED", 40, 20, 40, WHITE);
	newgame.DrawButton();
	changediff.DrawButton();
	if (newgame.UpdateButton() && !isMouseButtonDown) {
		isGame = false;
		isInGame = true;
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		isMouseButtonDown = true;
	else
		isMouseButtonDown = false;
	if (changediff.UpdateButton()) {
		isGame = false;
		isInGame = true;
		GameState = 0;
		isStartInit = false;
	}
	grid.DrawAllCell();

}

void Game::SetDifficulty()
{
	easy.button.DrawButton();
	if (easy.button.UpdateButton()) {
		ActualDifficult = easy.DifficultyParams();
		isEasy = true;
		isNormal = false;
		isHard = false;
		GameState = 1;
	}
	normal.button.DrawButton();
	if (normal.button.UpdateButton()) {
		ActualDifficult = normal.DifficultyParams();
		isEasy = false;
		isNormal = true;
		isHard = false;
		GameState = 1;
	}
	hard.button.DrawButton();
	if (hard.button.UpdateButton()) {
		ActualDifficult = hard.DifficultyParams();
		isEasy = false;
		isNormal = false;
		isHard = true;
		GameState = 1;
	}
}

void Game::LoadHighScore()
{
	if (isEasy)
		BestTime = easy.LoadHighScoreFromFile();
	if(isNormal)
		BestTime = normal.LoadHighScoreFromFile();
	if(isHard)
		BestTime = hard.LoadHighScoreFromFile();


}

void Game::SaveHighScore()
{
	if (isEasy)
		easy.SaveHighScoreToFile(BestTime);
	if (isNormal)
		normal.SaveHighScoreToFile(BestTime);
	if (isHard)
		hard.SaveHighScoreToFile(BestTime);
}

std::vector<int> Game::GetGameTime()
{
	int minute{ 0 };
	int sec{ 0 };
	if (!grid.GameStarted) {
		StartTime = (int)GetTime();
	}
	else {
		ElapsedTime = (int)GetTime() - StartTime;
		minute = ElapsedTime / 60;
		sec = ElapsedTime % 60;

	}
	return { minute, sec };

}

void Game::ResetTime()
{
	StartTime = 0;
	ElapsedTime = 0;
	grid.GameStarted = false;
}


