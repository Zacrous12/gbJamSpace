#include "Player.h"
#include <raylib.h>
#include <raylib.h>

Player::Player()
{
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
}

void Player::Update()
{
    if(IsKeyPressed(KEY_D)) {
        if(sprintTimerRight > 0) {
            isSprinting = true;            
        }
        sprintTimerRight = sprintTimeDefault;

        doubleTapRight++;
    }

    if(IsKeyPressed(KEY_A)) {
        if(sprintTimerLeft > 0) {
            isSprinting = true;            
        }
        sprintTimerLeft = sprintTimeDefault;

        doubleTapLeft++;
    }

    sprintTimerLeft -= 1 * GetFrameTime();
    sprintTimerRight -= 1 * GetFrameTime();

    if(IsKeyDown(KEY_D)){
        if(isSprinting) {
            speed = 3.0f;
        } else {
            speed = 2.0f;
        }
        playerX += speed;
    } 
    if(IsKeyDown(KEY_A)) {
                if(isSprinting) {
            speed = 3.0f;
        } else {
            speed = 2.0f;
        }
        playerX -= speed;
    }

    if(IsKeyReleased(KEY_D) || IsKeyReleased(KEY_A)) {
        isSprinting = false;
    }

    if(IsKeyDown(KEY_S)) isDucking = true, height = 10.0f;
    else isDucking = false, height = 0.0f;

    if (IsKeyDown(KEY_SPACE) && canJump)
    {
        speed -= 0.5f;
        canJump = false;
        jumpTimer = 15;
        gravity = 0.5f;
    } else if(!canJump && jumpTimer < 2) {
        playerY += 3.0f * gravity;
        gravity += 0.1f;
    }

    if(jumpTimer > 0 && !canJump)
    {
        playerY -= 0.5f * jumpTimer;
        jumpTimer--;
    }

    if(playerY > 140.0f)
    {
        canJump = true;
        speed = 2.0f;
        jumpTimer = 0;
    }

    position = { playerX, playerY + height, 20.0f, 20.0f - height };
}

void Player::Draw()
{

}