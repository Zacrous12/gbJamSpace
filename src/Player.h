#pragma once
#include <raylib.h>

class Player
{
public:
    Player();
    void Update();
    void Draw();
    float playerX = 10.0f;
    float playerY = 140.0f;
    Rectangle position = { playerX, playerY, 20.0f, 20.0f };
    float jumpHeight = 20.0f;
    float speed = 2.0f;
    float gravity = 0.5f;
    int jumpTimer = 0;
    bool canJump = true;
    bool isDucking = false;
    float height = 20.0f;
    int sprintTimeDefault = 20;
    int sprintTimerLeft = 0;
    int sprintTimerRight = 0;
    bool isSprinting = false;
    int doubleTapRight = 0;
    int doubleTapLeft = 0;
};