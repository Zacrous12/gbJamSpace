#include "raylib.h"
#include "Boss.h"
#include "Player.h"

Boss::Boss(Vector2 pos){
    position=pos;
    
    
}

void Boss::Update(Player player){
    slamRange.x=position.x-30;
    slamRange.y=position.y;
    slamRange.height=spriteWidth;
    slamRange.width=60+spriteWidth;
    
    
    if(player.position.x>=600)bossFight=true;
    
    if(bossFight){    
        if(decTime<decTimer && !isAttacking)decTime += 5*GetFrameTime();
        else if(decTime>= decTimer){
            if (!isAttacking){
                decTime=0;
                switch (GetRandomValue(1,3)){
                case 1||2:
                        Bullets(player);  
                        isAttacking=true;
                break;
                case 3:
                    Roll(player);
                    isAttacking=true;
                break;
                }
                if(CheckCollisionRecs(player.sprite,slamRange)){
                    Slam(player);
                }
            }
        }
    }
    int bulletCount = sizeof(player.bullets)/sizeof(player.bullets[0]);

    for (int k = 0; k < bulletCount; k++)
        {
            if(CheckCollisionCircles({player.bullets[k].position.x,player.bullets[k].position.y}, 1.5f, 
                                    {position.x,position.y}, 10.0f))
                                    {
                                        player.bullets[k].position = {0,0};
                                        health -= 1;
                                        player.bullets[k].range = 0;
                                    }
        }
    

}

void Boss::Bullets(Player player){
    targetPos={player.playerX+10,player.playerY+10};
        trig.x = targetPos.x-position.x;
        trig.y = targetPos.y-position.y;
        
    
        if (targetPos.x > position.x )flipX = 1;
        else if (targetPos.x < position.x)  {
            flipX = -1;
            trig.x-=10;
            trig.y-=8;
        }
        
        bulletPos = {position.x+spriteWidth/2,position.y+spriteWidth/2};
        bullet2Pos={position.x+spriteWidth/2,position.y+spriteWidth/2};
        bullet3Pos={position.x+spriteWidth/2,position.y+spriteWidth/2};
        ratio=trig.y/trig.x;
        shouldFire=true;

}

void Boss::Roll(Player player){
    isRolling=true;
    if(player.position.x+player.spriteWidth<position.x){
        currentSpeed=-rollSpeed;
    }else if(player.position.x>position.x+spriteWidth){
        currentSpeed=rollSpeed;
    }else {
        currentSpeed=0;
    }

}

void Boss::Slam(Player player){
    //play animation
    //dmg player
}

void Boss::Draw(Player player,Color c){
    if(health>0){
        DrawRectangleV(position,{spriteWidth,spriteWidth},c);
        
        Update(player);
        if (shouldFire && isAttacking){
            
            if (flipX==1){
                if (bulletPos.x < targetPos.x ){
                bulletPos.x+=bulletSpeed*flipX*GetFrameTime();
                bullet2Pos.x+=bulletSpeed*flipX*GetFrameTime();
                bullet3Pos.x+=bulletSpeed*flipX*GetFrameTime();
                bulletPos.y+=bulletSpeed*ratio*GetFrameTime();
                bullet2Pos.y+=bulletSpeed*ratio*5*GetFrameTime();
                bullet3Pos.y+=bulletSpeed*ratio*-5*GetFrameTime();
                }else {
                    shouldFire = false;
                    isAttacking=false;
                }
            }else if (flipX==-1){
                if (bulletPos.x > targetPos.x ){
                bulletPos.x+=bulletSpeed*flipX*GetFrameTime();
                bullet2Pos.x+=bulletSpeed*flipX*GetFrameTime();
                bullet3Pos.x+=bulletSpeed*flipX*GetFrameTime();
                bulletPos.y+=bulletSpeed*-1*ratio*GetFrameTime();
                bullet2Pos.y+=bulletSpeed*-1*ratio*5*GetFrameTime();
                bullet3Pos.y+=bulletSpeed*-1*ratio*-5*GetFrameTime();
                }else {
                    shouldFire = false;
                    isAttacking=false;
                    
                }
            }
            
            DrawCircleV(bulletPos,5,BLACK);
            DrawCircleV(bullet2Pos,5,BLACK);
            DrawCircleV(bullet3Pos,5,BLACK);
        }else{
            
            bulletPos=position;
        
        }

        //rolling
        if(isRolling){
            if(travelDis<rollDistance){
                position.x+=currentSpeed*GetFrameTime();
                travelDis+=rollSpeed*GetFrameTime();
            }else if(travelDis>=rollDistance){
                currentSpeed=0;
                isRolling=false;
                isAttacking=false;
                travelDis=0;
            }
        }
    }
}