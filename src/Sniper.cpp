#include "raylib.h"
#include "Sniper.h"
#include "Player.h"
#include "math.h"
#include <stdio.h>




Sniper::Sniper(Vector2 pos,float blindR,float sightR){
    dmg=12.0f;
    shootSpeed=1.5f;
    health=20;
    position=pos;
    bulletSpeed=70;
    shouldFire = false;
    spriteWidth=32;
    sniperRec.height=spriteWidth;
    sniperRec.width=spriteWidth;
    sniperRec.x=position.x;
    sniperRec.y=position.y;
    blindRadius = blindR;
    sightRadius=sightR;
    isShooting = false;
    shootTimer=0;
    shootDelay=10;
    blinkCounter=8;
    blinking=false;
    
    blink = LoadSound("src/_resources/sounds/blink.wav");    
    sniperDeath = LoadSound("src/_resources/sounds/sniperDeath.wav");

}



void Sniper::CalcShoot(Player player){
    //targetPos={player.playerX+(player.height/2),player.playerY+(player.height/2)};
    if (!CheckCollisionCircles({player.playerX+10,player.playerY+10},10,{position.x+spriteWidth/2,position.y+spriteWidth/2},blindRadius) && !shouldFire){
        targetPos={player.playerX+10,player.playerY+10};
        trig.x = targetPos.x-position.x;
        trig.y = targetPos.y-position.y;
        
    
        if (targetPos.x > position.x )flipX = 1;
        else if (targetPos.x < position.x)  {
            flipX = -1;
            trig.x-=10;
            trig.y-=8;
        }
        

        ratio=trig.y/trig.x;
        //bulletDistance = sqrtf(powf(trig.x,2)+powf(trig.y,2));
        
        
        shouldFire=true;
        bulletPos = {position.x+spriteWidth/2,position.y+spriteWidth/2};
        
    }
    
    


};

void Sniper::DrawSniper(Texture2D t,Player &player){
    if(health >= 1) {
        //ANIMATION
        if(blinkCounter > 8) 
        {
            if(sniperRec.x >= 320.0f) blinking = true;
            if(sniperRec.x <= 0.0f) blinking = false; 
            if(blinking) sniperRec.x -= 32.0f;
            else sniperRec.x += 32.0f;

            blinkCounter = 0;
        }
        blinkCounter++;

        DrawTextureRec(t,sniperRec,position,WHITE);
        UpdateSniper(player);
    }


//draw Bullet---------------------------------    
    if (shouldFire){
        if(!IsSoundPlaying(blink)) PlaySound(blink);
        
        if (flipX==1){
            if (bulletPos.x < targetPos.x ){
            bulletPos.x+=bulletSpeed*flipX*GetFrameTime();
            bulletPos.y+=bulletSpeed*ratio*GetFrameTime();
            }else {
                shouldFire = false;
            }
        }else if (flipX==-1){
            if (bulletPos.x > targetPos.x ){
            bulletPos.x+=bulletSpeed*flipX*GetFrameTime();
            bulletPos.y+=bulletSpeed*-1*ratio*GetFrameTime();
            }else {
                shouldFire = false;
                
            }
        }
        
        DrawCircleV(bulletPos,3,BLACK);
        if(CheckCollisionCircles({player.playerX+10,player.playerY+10},10,bulletPos,3)){
            player.currentHealth -=dmg;
            shouldFire = false;
        
        }
    }else {
        
        bulletPos=position;

    }

};

void Sniper::UpdateSniper(Player player){

        int bulletCount = sizeof(player.bullets)/sizeof(player.bullets[0]);

        // Collision Check
        for (int k = 0; k < bulletCount; k++)
        {
            if(CheckCollisionCircles({player.bullets[k].position.x,player.bullets[k].position.y}, 
                                    player.bullets[k].radius, 
                                    {sniperRec.x,sniperRec.y}, 16.f))
                                    {
                                        player.bullets[k].position = {0,0};
                                        this->health -= player.bullets[k].damage;
                                        player.bullets[k].range = 0;
                                        player.bullets[k].damage = 0;
                                    }
        }

        if(health <= 0){
            //killSniper()
            if(!IsSoundPlaying(sniperDeath)) PlaySound(sniperDeath);
        }
    
        if (shootTimer < shootDelay) shootTimer+=5*GetFrameTime();
        else if(shootTimer >= shootDelay) {
            if(CheckCollisionCircles({player.playerX+10,player.playerY+10},10,{position.x+spriteWidth/2,position.y+spriteWidth/2},sightRadius))
            CalcShoot(player);
            shootTimer=0;
        }
    
}