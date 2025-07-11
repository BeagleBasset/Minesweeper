
#include <iostream>
#include <raylib.h>
#include "game.hpp"
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#define NOMINMAX
#include <windows.h>



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {

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
