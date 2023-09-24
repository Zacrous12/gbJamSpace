#pragma once
#include <raylib.h>
#include "raymath.h"
#include <vector>

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

typedef struct Bullet {
    bool isRight;
    float speed;
    Vector2 position;
    Color color;
    float radius;
    float range;
} Bullet;

enum Weapon { PISTOL, LASER, FLAMETHROWER, SPACE };

class Player
{
public:
    Player(float x, float y);
    void Draw();
    void Update(float deltaTime, std::vector<EnvItem> *envItems, int envItemsLength);
    void Shoot(bool isRight, float speed, Vector2 pos, Color col, float rad, float range);

    // POSITION
    float playerX;
    float playerY;
    float spriteWidth;
    float spriteHeight;
    Rectangle sprite;
    bool facingRight;
    bool hitObstacle;
    Vector2 position; 
    float flipWidth;

    // MOVEMENT
    float jumpHeight;
    float speed;
    float gravity;
    int jumpTimer;
    bool groundPound;
    bool canJump;
    bool isDucking;
    bool canMoveRight;
    bool canMoveLeft;
    bool wallJump;
    float height;
    int sprintTimeDefault;
    int sprintTimerLeft;
    int sprintTimerRight;
    bool isSprinting;
    int doubleTapRight;
    int doubleTapLeft;

    // INVENTORY
    int currentHealth ;
    int maxHealth ;
    int currentSpecial;
    int maxSpecial ;
    Weapon currentWeapon;
    int boosts ;
    Bullet bullets[100];
    int shotCounter;

    // ANIMATION
    Vector2 spritePos;
    int walkSpeed;
    int sprintSpeed;
    int jumpSpeed;
    int poundCounter;
    int walkCounter;
    int jumpCounter;
    int sprintCounter;

};