#pragma once
#include "raylib.h"
#include "Player.h"

// include enemy.h and create sniper object to call DrawSniper in drawloop 




class Sniper{
    public:
    float health;
    float shootSpeed;
    float dmg;
    float bulletSpeed;
    float ratio;
    bool shouldFire;
    bool isShooting;
    int flipY;
    int flipX;
    float bulletDistance;
    float spriteWidth;
    float blindRadius;
    float sightRadius;
    float shootTimer;
    float shootDelay;
    Vector2 bulletPos;
    Vector2 trig;
    Vector2 position;
    Vector2 targetPos;
    Rectangle sniperRec;
    Sniper(Vector2 pos,float blindR,float sightR);
    void CalcShoot(Player player);
    void UpdateSniper(Player player);
    void DrawSniper(Texture2D t,Player &player);
    

};



