#include "raylib.h"
#include "GameState.h"

GameState::GameState(){
    isPaused = false;
    isGameOver = false;
    isGameWon = false;
    isGameStart = true;
    isSoundOn = true;
    selectRestart = false;
    currentLevel = 1;
}