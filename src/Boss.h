#pragma once
#include "raylib.h"
#include "Player.h"
#include "Textures.h"

class Boss {
    public:
    Boss(Vector2);
    void Draw(Player,Color);
    void Update(Player);
    //attacks
    void Bullets(Player);
    Vector2 targetPos;
    Vector2 trig;
    Vector2 bulletPos;
    Vector2 bullet2Pos;
    Vector2 bullet3Pos;
    float ratio;
    float bulletSpeed=15;
    int flipX;
    bool shouldFire=false;
    void Slam(Player &player);
    Rectangle slamRange;
    float slamDmg=30;
    void Roll(Player);
    float rollSpeed=130;
    float rollDistance=200;
    float travelDis=0;
    bool isRolling=false;
    bool shouldRoll=true;

    float currentSpeed=0;
    float spriteWidth=140;
    bool isAttacking=false;
    float health=50;
    int attack=0;
    float decTime;
    float decTimer=7;
    bool bossFight=false;
    Rectangle hitBox;
    Vector2 position;
    Rectangle spritePos;

    Sound bossHurt;
    Sound bossDeath;
    Sound bossRoll;
    Sound bossHit;
    int rollTimer=8;

    Texture2D boss;
};