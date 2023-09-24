#pragma once
#include "raylib.h"
#include "Player.h"

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
    bool shouldFire=false;;
    void Slam(Player);
    Rectangle slamRange;
    float slamDmg=30;
    void Roll(Player);
    float rollSpeed=130;
    float rollDistance=200;
    float travelDis=0;
    bool isRolling=false;

    float currentSpeed=0;
    float spriteWidth=32;
    bool isAttacking=false;
    float health=50;
    int attack=0;
    float decTime;
    float decTimer=7;
    bool bossFight=false;
    Vector2 position;


};