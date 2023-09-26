#pragma once
#include "raylib.h"

class GameState
{
    public:
    GameState();
    bool isPaused;
    bool isGameOver;
    bool isGameWon;
    bool isGameStart;
    bool isSoundOn;
    bool selectRestart;
    int currentLevel;
};