#include "raylib.h"
#include "Boss.h"
#include "Player.h"
#include "Textures.h"

Boss::Boss(Vector2 pos){
    position=pos;
    spritePos={0.0f, 0.0f};
    
    boss = LoadTexture("src/_resources/sprites/BOSS.png"); 
    bossHurt = LoadSound("src/_resources/sounds/bossHurt.wav");
    bossDeath = LoadSound("src/_resources/sounds/bossDeath.wav");
    bossHit = LoadSound("src/_resources/sounds/bossHit.wav");
    bossRoll = LoadSound("src/_resources/sounds/bossRoll.wav");
}

Boss::~Boss(){
    UnloadTexture(boss);
    UnloadSound(bossHurt);
    UnloadSound(bossDeath);
    UnloadSound(bossHit);
    UnloadSound(bossRoll);
}

void Boss::Update(Player player){
    slamRange.x=position.x-30;
    slamRange.y=position.y;
    slamRange.height=spriteWidth;
    slamRange.width=60+spriteWidth;

    hitBox.x=position.x;
    hitBox.y=position.y;
    hitBox.height=spriteWidth;
    hitBox.width=spriteWidth;
    
    
    if(player.position.x>=30)bossFight=true;
    
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
            if(CheckCollisionCircles({player.bullets[k].position.x,player.bullets[k].position.y}, 
                                    player.bullets[k].radius, 
                                    {position.x,position.y}, 10.0f))
                                    {
                                        player.bullets[k].position = {0,0};
                                        if(!isRolling)health -= player.bullets[k].damage;
                                        player.bullets[k].range = 0;
                                        //if(!IsSoundPlaying(bossHurt)) PlaySound(bossHurt);
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
            
        }
        trig.x-=10;
        trig.y-=14;
        
        bulletPos = {position.x+spriteWidth/2,position.y+spriteWidth/2};
        bullet2Pos={position.x+spriteWidth/2,position.y+spriteWidth/2};
        bullet3Pos={position.x+spriteWidth/2,position.y+spriteWidth/2};
        ratio=trig.y/trig.x;
        shouldFire=true;

}

void Boss::Roll(Player player){
    isRolling=true;
    //if(!IsSoundPlaying(bossRoll)) PlaySound(bossRoll);
    
    if(player.position.x+player.spriteWidth<position.x){
        currentSpeed=-rollSpeed;
    }else if(player.position.x>position.x+spriteWidth){
        currentSpeed=rollSpeed;
    }else {
        currentSpeed=0;
    }

}

void Boss::Slam(Player &player){
    player.currentHealth -= slamDmg;
    if(!IsSoundPlaying(bossHit)) PlaySound(bossHit);
}

void Boss::Draw(Player &player,Color c){
    if(health>0){
        DrawTexturePro(boss, {spritePos.x,spritePos.y,spriteWidth,spriteWidth}, {position.x,position.y,spriteWidth,spriteWidth}, {0,0}, 0, WHITE);
        
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
            Vector2 bullets[3]={bulletPos,bullet2Pos,bullet3Pos};
            DrawCircleV(bulletPos,5,BLACK);
            for(int i=0;i<=3;i++){
                if(CheckCollisionCircleRec(bullets[i],5,player.sprite)){
                player.currentHealth-=bulletDmg;
                shouldFire=false;
                isAttacking=false;

                }
            }
            DrawCircleV(bullet2Pos,5,BLACK);
            DrawCircleV(bullet3Pos,5,BLACK);
        }else{
            
            bulletPos=position;
            bullet2Pos=position;
            bullet3Pos=position;
        
        }

        //rolling
        if(isRolling){
            if(CheckCollisionRecs(player.sprite,hitBox)  && player.groundPound)shouldRoll=false, spritePos.x = 0.0f;
            else shouldRoll=true;
            if(travelDis<rollDistance && shouldRoll){
                position.x+=currentSpeed*GetFrameTime();
                travelDis+=rollSpeed*GetFrameTime();
                if(rollTimer>7){
                    spritePos.y = 420.0f;
                    spritePos.x += 140.0f;
                }
                rollTimer++;

            }else if(travelDis>=rollDistance || !shouldRoll){
                spritePos.y = 0.0f;
                currentSpeed=0;
                isRolling=false;
                isAttacking=false;
                travelDis=0;
            }
        }
    } else {
        if(!IsSoundPlaying(bossDeath)) PlaySound(bossDeath), UnloadSound(bossDeath);
        if(rollTimer > 7){
            rollTimer = 0;
            spritePos.y = 700.0f;
            spritePos.x += 140.0f;
        }
        rollTimer++;
        //KillBoss();
    }
}