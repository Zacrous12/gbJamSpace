#include "raylib.h"
#include "enemy.h"
#include "Player.h"
#include "math.h"




Sniper::Sniper(Vector2 pos,float width,float blindR,float sightR){
    dmg=1;
    shootSpeed=1;
    health=1;
    position=pos;
    bulletSpeed=70;
    shouldFire = false;
    spriteWidth=width;
    sniperRec.height=spriteWidth;
    sniperRec.width=spriteWidth;
    sniperRec.x=position.x;
    sniperRec.y=position.y;
    blindRadius = blindR;
    sightRadius=sightR;
    isShooting = false;
    shootTimer=0;
    shootDelay=10;
    
    

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

void Sniper::DrawSniper(Color c,Player player){
    DrawRectangleRec(sniperRec,c);
    UpdateSniper(player);
    
//draw Bullet---------------------------------    
    if (shouldFire){
        
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
            //damage player
            shouldFire = false;
            
        }
    }else {
        
        bulletPos=position;

    }

};

void Sniper::UpdateSniper(Player player){
    
    
        if (shootTimer < shootDelay) shootTimer+=5*GetFrameTime();
        else if(shootTimer >= shootDelay) {
            if(CheckCollisionCircles({player.playerX+10,player.playerY+10},10,{position.x+spriteWidth/2,position.y+spriteWidth/2},sightRadius))
            CalcShoot(player);
            shootTimer=0;
        }
    
}