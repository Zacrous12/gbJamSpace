#include "Player.h"
#include <raylib.h>

Player::Player()
{
    float playerX = 10.0f;
    float playerY = 140.0f;
    Rectangle player = { playerX, playerY, 20.0f, 20.0f };
    float jumpHeight = 20.0f;
    float speed = 2.0f;
    float gravity = 0.5f;
    int jumpTimer = 0;
    bool canJump = true;
}

void Player::Update()
{
    if (x + radius >= GetScreenWidth() || x - radius <= 0)
        speedX *= -1;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
        speedY *= -1;
}

void Player::Draw()
{

}