#include "raylib.h"
#include "Textures.h"

Textures::Textures(){
    backTile1 = LoadTexture("src/_resources/textures/backTile1.png");
    backTile2 = LoadTexture("src/_resources/textures/backTile2.png");
    backTile3 = LoadTexture("src/_resources/textures/backTile3.png");
    backTile4 = LoadTexture("src/_resources/textures/backTile4.png");
    backTile5 = LoadTexture("src/_resources/textures/backTile5.png");
    backTile6 = LoadTexture("src/_resources/textures/backTile6.png");
    backTile7 = LoadTexture("src/_resources/textures/backTile7.png");
    backTile8 = LoadTexture("src/_resources/textures/backTile8.png");
    backTile9 = LoadTexture("src/_resources/textures/backTile9.png");
    floor32 = LoadTexture("src/_resources/textures/32x32_floor.png");
    nullWpn = LoadTexture("src/_resources/textures/null_weapon_icon.png");
    defaultWpn = LoadTexture("src/_resources/textures/default_weapon_icon.png");
    flameWpn = LoadTexture("src/_resources/textures/flamethrower_weapon_icon.png");
    laserWpn = LoadTexture("src/_resources/textures/laser_weapon_icon.png");
    spaceWpn = LoadTexture("src/_resources/textures/spaceshot_weapon_icon.png");
    floor16 = LoadTexture("src/_resources/sprites/16x16_floor.png");
    grassyFloor = LoadTexture("src/_resources/textures/16x16_grassy_floor.png");
    grassyWall = LoadTexture("src/_resources/textures/16x32_grassy_wall.png");
    idle = LoadTexture("src/_resources/sprites/manSheet.png");
    sniper = LoadTexture("src/_resources/sprites/9axis-sniper_spritesheet.png"); 
    boss = LoadTexture("src/_resources/sprites/BOSS.png");
    death = LoadTexture("src/_resources/sprites/DED.png");
}