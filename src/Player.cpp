#include "Player.h"
#include <raylib.h>

Player::Player()
{

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
        bool canMoveRight = true;
        for (int i = 0; i < envItemsLength; i++) {
        EnvItem *ei = envItems + i;
        if (ei->blocking &&
            playerX + speed < ei->rect.x + ei->rect.width &&
            playerX + 20 + speed > ei->rect.x &&
            playerY + sprite.height > ei->rect.y &&
            playerY < ei->rect.y + ei->rect.height) {
            canMoveRight = false;
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
        bool canMoveLeft = true;
        for (int i = 0; i < envItemsLength; i++) {
            EnvItem *ei = envItems + i;
            if (ei->blocking &&
                playerX - speed < ei->rect.x + ei->rect.width &&
                playerX + 20 - speed > ei->rect.x &&
                playerY + sprite.height > ei->rect.y &&
                playerY < ei->rect.y + ei->rect.height) {
                canMoveLeft = false;
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
        canJump = false;
        jumpTimer = 15;
        gravity = 0.5f;
    } else if(!canJump && jumpTimer < 2 && playerY < 140.0f) {
        playerY += 3.0f * gravity;
        gravity += 0.1f;
    }

    if (IsKeyPressed(KEY_SPACE) && !canJump && playerY < 95.0f){
        jumpTimer = 0;
        gravity = 5.5f;
        groundPound = true;
    }

    if ((groundPound && IsKeyReleased(KEY_SPACE)) || playerY > 138.0f){
        playerY = 140.0f;
        groundPound = false;
    } 

    if(jumpTimer > 0 && !canJump)
    {
        playerY -= 0.5f * jumpTimer;
        jumpTimer--;
    }

    if (playerY < 140.0f) // Player is in the air
    {
        canJump = false; // Player can't jump while in the air
        playerY += gravity; // Apply gravity to player's position
        if (playerY >= 140.0f) // If player hits the ground...
        {
            playerY = 140.0f; // Snap player to ground
            gravity = 0.0f; // Reset gravity
            canJump = true; // Allow jumping
        }
    }

    if(playerY >= 140.0f) canJump = true;

    sprite = { playerX, playerY + height, 20.0f, 20.0f - height };
    position = { playerX, playerY + height };
}

void Player::Draw()
{

}