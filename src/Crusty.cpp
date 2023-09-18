#include "Crusty.h"

Crusty::Crusty(Vector2 pos){
    position=pos;
    
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

void Crusty::Draw(Color c, Player player){
    DrawRectangleV(position,{spriteWidth,spriteWidth},c);
    Update(player);
    
}

void Crusty::Damage(Player player) {
    if(!hasShell){
    //deal damage to player
    }
}
