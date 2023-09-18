#pragma once 
#include "raylib.h"
#include "Player.h"

class Crusty {
    public:
    float health = 2;
    float dmg=2;
    Vector2 position;
    float spriteWidth=20;
    bool hasShell = true;
    bool canCharge = true;
    bool isCharging = false;
    bool moveRight = false;
    float chargeTimer=0;
    float speed = 1;
    float chargeTime=4;
    float currentSpeed=0;
    Rectangle range;
    Rectangle hitBox;

    Crusty(Vector2 pos);
    void Update(Player player);
    void Draw(Color c,Player player);
    void Damage(Player player);
};
