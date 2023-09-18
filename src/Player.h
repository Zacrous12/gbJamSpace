#pragma once
#include <raylib.h>
#include "raymath.h"

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

enum Weapon { PISTOL, SHOTGUN, MACHINEGUN, ROCKETLAUNCHER };

class Player
{
public:
    Player();
    void Draw();
    void Update(float deltaTime, EnvItem *envItems, int envItemsLength);

    // POSITION
    float playerX = 10.0f;
    float playerY = 140.0f;
    float spriteWidth = 20.0f;
    Rectangle sprite = { playerX, playerY, spriteWidth,spriteWidth};
    bool facingRight = true;
    bool hitObstacle = false;
    Vector2 position = { playerX, playerY };

    // MOVEMENT
    float jumpHeight = 20.0f;
    float speed = 2.0f;
    float gravity = 0.5f;
    int jumpTimer = 0;
    bool groundPound = false;
    bool canJump = true;
    bool isDucking = false;
    bool canMoveRight = true;
    bool canMoveLeft = true;
    bool wallJump = false;
    float height = 20.0f;
    int sprintTimeDefault = 20;
    int sprintTimerLeft = 0;
    int sprintTimerRight = 0;
    bool isSprinting = false;
    int doubleTapRight = 0;
    int doubleTapLeft = 0;

    // INVENTORY
    int currentHealth = 100;
    int maxHealth = 100;
    int currentSpecial = 0;
    int maxSpecial = 100;
    Weapon currentWeapon = PISTOL;
    int boosts = 0;
};