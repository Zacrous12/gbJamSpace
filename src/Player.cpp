#include "Player.h"
#include <raylib.h>
#include <stdio.h>
#include <vector>

Player::Player(float x, float y)
{
    playerX = x;
    playerY = y;
    spriteWidth = 20.0f;
    sprite = { playerX, playerY, spriteWidth, spriteWidth};
    facingRight = true;
    hitObstacle = false;
    position = { playerX, playerY };

    jumpHeight = 20.0f;
    speed = 2.0f;
    gravity = 0.5f;
    jumpTimer = 0;
    groundPound = false;
    canJump = true;
    isDucking = false;
    canMoveRight = true;
    canMoveLeft = true;
    wallJump = false;
    height = 0.0f;
    sprintTimeDefault = 20;
    sprintTimerLeft = 0;
    sprintTimerRight = 0;
    isSprinting = false;
    doubleTapRight = 0;
    doubleTapLeft = 0;

    currentHealth = 100;
    maxHealth = 100;
    currentSpecial = 0;
    maxSpecial = 100;
    currentWeapon = PISTOL;
    boosts = 0;
    shotCounter = 0;
}

void Player::Update(float deltaTime, std::vector<EnvItem> *envItems, int envItemsLength)
{
    if(IsKeyPressed(KEY_D)) {
        facingRight = true;
        if(sprintTimerRight > 0) {
            isSprinting = true;            
        }
        sprintTimerRight = sprintTimeDefault;

        doubleTapRight++;
    }

    if(IsKeyPressed(KEY_A)) {
        facingRight = false;
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
        EnvItem &ei = (*envItems)[i];
        if (ei.blocking &&
            playerX + speed < ei.rect.x + ei.rect.width &&
            playerX + 20 + speed > ei.rect.x &&
            playerY + sprite.height > ei.rect.y &&
            playerY < ei.rect.y + ei.rect.height) {
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
            EnvItem& ei = (*envItems)[i];
            if (ei.blocking &&
                playerX - speed < ei.rect.x + ei.rect.width &&
                playerX + 20 - speed > ei.rect.x &&
                playerY + sprite.height > ei.rect.y &&
                playerY < ei.rect.y + ei.rect.height) {
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
    } 
    if (IsKeyReleased(KEY_A)) {
        isSprinting = false;
    }

    // Ducking is bugged on platforms
    // if(IsKeyDown(KEY_S)) isDucking = true, height = 10.0f;
    // else isDucking = false, height = 0.0f;

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

    } else if(!canJump && jumpTimer < 2 && playerY < 140.0f) 
    {
        playerY += 3.0f * gravity;
        gravity += 0.1f;
    }

    if(IsKeyPressed(KEY_SPACE) && wallJump)
    {
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
    }

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

    if (playerY >= 140.0f) 
    {
        playerY = 140.0f;
        canJump = true;
        wallJump = false;
    }

    sprite = { playerX, playerY + height, 20.0f, 20.0f - height };
    position = { playerX, playerY + height };

    if (IsKeyPressed(KEY_K))
    {
        if(currentWeapon == PISTOL) currentWeapon = LASER;
        else if(currentWeapon == LASER) currentWeapon = FLAMETHROWER;
        else if(currentWeapon == FLAMETHROWER) currentWeapon = SPACE;
        else currentWeapon = PISTOL;
    }

    // Combat
    if (IsKeyPressed(KEY_J))
    {
        if(currentWeapon == PISTOL){
            Shoot(facingRight, 3.5f, position, GetColor(0x8be5ffff), 1.0f, 10.0f);
        }else if(currentWeapon == LASER){
            Shoot(facingRight, 5.0f, position, GetColor(0x8be5ffff), 2.0f, 25.0f);
        }else if(currentWeapon == FLAMETHROWER){
            Shoot(facingRight, 2.0f, position, GetColor(0x8be5ffff), 4.0f, 5.0f);
        }else if(currentWeapon == SPACE){
            Shoot(facingRight, 4.0f, position, GetColor(0x622e4cff), 3.0f, 40.0f);
        }
    }
    
    // Collision
    hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem& ei = (*envItems)[i];
        if (ei.blocking &&
            playerX < ei.rect.x + ei.rect.width &&
            playerX + 20 > ei.rect.x &&
            playerY + sprite.height > ei.rect.y &&
            playerY < ei.rect.y + ei.rect.height) {
            hitObstacle = 1;
            speed = 0.0f;
            playerY = ei.rect.y - sprite.height;
        }
    }

    if (!hitObstacle)
    {
        playerY += speed*deltaTime;
        speed += gravity*deltaTime;
        canMoveRight = true;
        canMoveLeft = true;
    }
    else canJump = true;

}

void Player::Draw()
{
    int bulletCount = sizeof(bullets)/sizeof(bullets[0]);
    
    for (int i = 0; i < bulletCount; i++)
    {
        if(bullets[i].range >= 0){
            DrawCircle(bullets[i].position.x, bullets[i].position.y, bullets[i].radius, bullets[i].color);
            bullets[i].position.x += bullets[i].speed;
            bullets[i].range -= 0.6f;
        } 
    }
    
}

void Player::Shoot(bool isRight, float speed, Vector2 pos, Color col, float rad, float range)
{
    if(isRight) pos = {pos.x + 20.0f, pos.y};
    else speed = -speed;

    pos.y += 9.0f;

    bullets[shotCounter] = {isRight, speed, pos, col, rad, range};
    shotCounter++;
    if(shotCounter > 9) shotCounter = 0;
}