#include "Player.h"
#include <raylib.h>
#include <stdio.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

Player::Player()
{
    groundPound=false;
}

void Player::Update(float deltaTime, EnvItem *envItems, int envItemsLength)
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
        canMoveRight = true;
        for (int i = 0; i < envItemsLength; i++) {
        EnvItem *ei = envItems + i;
        if (ei->blocking &&
            playerX + speed < ei->rect.x + ei->rect.width &&
            playerX + 20 + speed > ei->rect.x &&
            playerY + sprite.height > ei->rect.y &&
            playerY < ei->rect.y + ei->rect.height) {
            canMoveRight = false;
            gravity = 0.1f;
            if (IsKeyPressed(KEY_SPACE))
            {
                canJump = true;
            }
            
            break; // No need to check further if collision is detected
            }
        }
        if(canMoveRight) playerX += speed;
    } 
    if(IsKeyDown(KEY_A)) {
                if(isSprinting) {
            speed = 3.0f;
        } else {
            speed = 2.0f;
        }
        canMoveLeft = true;
        for (int i = 0; i < envItemsLength; i++) {
            EnvItem *ei = envItems + i;
            if (ei->blocking &&
                playerX - speed < ei->rect.x + ei->rect.width &&
                playerX + 20 - speed > ei->rect.x &&
                playerY + sprite.height > ei->rect.y &&
                playerY < ei->rect.y + ei->rect.height) {
                canMoveLeft = false;
                gravity = 0.1f;
                if (IsKeyPressed(KEY_SPACE))
                {
                    canJump = true;
                }
                break; // No need to check further if collision is detected
            }
        }
        // Update position if no collision
        if (canMoveLeft) {
            playerX -= speed;
        }
    }

    if(IsKeyReleased(KEY_D)){
        isSprinting = false;
        facingRight = true;
    } 
    if (IsKeyReleased(KEY_A)) {
        isSprinting = false;
        facingRight = false;
    }

    if(IsKeyDown(KEY_S)) isDucking = true, height = 10.0f;
    else isDucking = false, height = 0.0f;

    if (canJump && IsKeyPressed(KEY_SPACE))
    {
        speed -= 0.5f;
        wallJump = false;
        canJump = false;
        jumpTimer = 15;
        gravity = 0.5f;
        if(!canMoveLeft || !canMoveRight){
            jumpTimer = 3;
            wallJump = true;
        }

    } else if(!canJump && jumpTimer < 2 && playerY < 140.0f) {
        playerY += 3.0f * gravity;
        gravity += 0.1f;
    }

    if(IsKeyPressed(KEY_SPACE) && wallJump){
        jumpTimer = 8;
        playerY -= 4.0f * gravity;
        gravity += 0.1f;
        wallJump = false;
        if(IsKeyDown(KEY_A)) playerX += 2.0f * gravity;
        else playerX -= 2.0f * gravity;
    } 

    //GROUND POUND IS BROKEN
    if (IsKeyPressed(KEY_SPACE) && jumpTimer < 10 && jumpTimer > 0 && canMoveLeft && canMoveRight){
        jumpTimer = 20;
        groundPound = true;
        printf("Ground Pound\n");
    }

    if (playerY > 141.0f) playerY = 140.0f;

    if(jumpTimer > 0)
    {
        if(groundPound == true){
            playerY += 0.5f * jumpTimer;
        }else {
            playerY -= 0.5f * jumpTimer;
        }
        jumpTimer--;
        if(jumpTimer == 0) groundPound = false;
    }

    if (playerY < 140.0f) // Player is in the air
    {
        canJump = false; 
        playerY += gravity; 
        if (playerY >= 140.0f) 
        {
            playerY = 140.0f; // Snap player to ground
            gravity = 0.0f; 
            canJump = true; 
        }
    }

    if(playerY >= 140.0f) canJump = true;

    sprite = { playerX, playerY + height, 20.0f, 20.0f - height };
    position = { playerX, playerY + height };

    // Collision
    hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        if (ei->blocking &&
            playerX < ei->rect.x + ei->rect.width &&
            playerX + 20 > ei->rect.x &&
            playerY + sprite.height > ei->rect.y &&
            playerY < ei->rect.y + ei->rect.height) {
            hitObstacle = 1;
            speed = 0.0f;
            playerY = ei->rect.y - sprite.height;
        }
    }

    if (!hitObstacle)
    {
        playerY += speed*deltaTime;
        speed += gravity*deltaTime;
    }
    else canJump = true;
}

void Player::Draw()
{

}