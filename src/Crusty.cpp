#include "Crusty.h"
#include <stdio.h>

Crusty::Crusty(Vector2 pos){
    position=pos;
    health = 150.0f;
    
    crusty = LoadSound("src/_resources/sounds/crusty.wav");
    crustyDeath = LoadSound("src/_resources/sounds/crustyDeath.wav");
}

void Crusty::Update(Player player){
    //generic Updates-----------------
    range = {position.x-50,position.y,100+spriteWidth,spriteWidth};
    hitBox= {position.x,position.y,spriteWidth,spriteWidth};
    //shell logic

    if(CheckCollisionRecs(player.sprite,hitBox)&&player.groundPound){
        hasShell=false;
    }

    //movement---------------------------------------------------------------------
    
    if (player.playerX+player.spriteWidth<=position.x) moveRight = false;
        else if (player.playerX>position.x+spriteWidth) moveRight = true;
    
    if (CheckCollisionRecs(range,player.sprite)&&canCharge){
        isCharging = true;
        canCharge = false;
        
    }


    if (isCharging) {
        if(!IsSoundPlaying(crusty)) PlaySound(crusty);
        chargeTimer += 10*GetFrameTime();
        if(chargeTimer>=chargeTime){
            isCharging = false;
            chargeTimer=0;
            canCharge = false;
        }
        currentSpeed = 3.5*speed;
    }else if(!isCharging && canCharge ) currentSpeed = 0;
    else if (!isCharging && !canCharge) currentSpeed = speed;

    if(moveRight) position.x += currentSpeed;
    else position.x -= currentSpeed;
    
}

void Crusty::Draw(Color c, Player &player){
    if(health > 0){
        DrawRectangleV(position,{spriteWidth,spriteWidth},c);
        Update(player);
    }

    int bulletCount = sizeof(player.bullets)/sizeof(player.bullets[0]);
    if(hitTime<hitTimer)hitTime+=10*GetFrameTime();
    else if(hitTime>=hitTimer){
        if (CheckCollisionRecs(player.sprite,hitBox))Damage(player);
        hitTime=0;
    }
    

    // Collision Check
    for (int k = 0; k < bulletCount; k++)
        {
            if(CheckCollisionCircles({player.bullets[k].position.x,player.bullets[k].position.y}, 
                                    player.bullets[k].radius, 
                                    {position.x,position.y}, 10.0f))
                                    {
                                        player.bullets[k].position = {0,0};
                                        if(!hasShell) this->health -= player.bullets[k].damage;
                                        player.bullets[k].range = 0;
                                        player.bullets[k].damage = 0;
                                    }
        }

        if(health <= 0){
            //killCrusty()
            if(!IsSoundPlaying(crustyDeath)) PlaySound(crustyDeath);
        }
    
}

void Crusty::Damage(Player &player) {
    
    //if(!player.groundPound)    player.currentHealth-=dmg;
    
}
