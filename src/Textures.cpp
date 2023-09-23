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
    sniper = LoadTexture("src/_resources/sprites/9-axis_angel2.png");
    sniper2 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt1.png");
    sniper3 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt2.png");
    sniper4 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt3.png");
    sniper5 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt4.png");
    sniper6 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt5.png");
    sniper7 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt6.png");
    sniper8 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt7.png");
    sniper9 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt8.png");
    sniper10 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt9.png");
    sniper11 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt10.png");
    sniper12 = LoadTexture("src/_resources/sprites/9axis-sniper_blinkingt11.png");
}