
#include <iostream>
#include <raylib.h>
#include "game.hpp"

using namespace std;

int main() {

    SetTargetFPS(60);
    InitWindow(500, 400, "Minesweeper");
    Game game = Game();

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(BLACK);
        if(game.GameState == 0) {
            if (!game.isStartInit) {
                game.StartWindow();
                game.isStartInit = true;
            }
            else
                game.UpdateStart();
        }
        if (game.GameState == 1) {
            if (game.isGame == false) {
                game.GameWindow();
                game.isGame = true;
            }
            else   
            {
                if(game.isInGame)
                    game.Update();
                if (game.isVictory)
                    game.WinScreenUpdate();
                if (game.isLose)
                    game.LoseScreenUpdate();

            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
