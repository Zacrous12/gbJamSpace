#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include "raymath.h"
#include "Player.h"
#include "Sniper.h"
#include "Crusty.h"
#include "Textures.h"

const int screenWidth = 640;
const int screenHeight = 576;

const int virtualScreenWidth = 160;
const int virtualScreenHeight = 144;

const float virtualRatio = (float)screenWidth/(float)virtualScreenWidth;

Color palette[] = { GetColor(0x622e4cff), GetColor(0x7550e8ff), GetColor(0x608fcfff), GetColor(0x8be5ffff)};

enum class GameScreen { TITLE, GAMEPLAY, BOSS, PAUSE };

class GameOverScreen
{
    public:
    void Draw() {
        if(aWinnerIsYou)
        {
            DrawText("Congratulations!", virtualScreenWidth/2, virtualScreenHeight/2, 20, palette[3]);
        } else 
        {
            DrawText("GAME OVER", virtualScreenWidth/2, virtualScreenHeight/2, 20, palette[3]);
            DrawText("RESTART", virtualScreenWidth/2, virtualScreenHeight/2 + 20, 8, palette[3]);
            DrawText("Quit to Main Menu", virtualScreenWidth/2, virtualScreenHeight/2 + 40, 8, palette[3]);
            if(selectRestart) DrawRectangleLines(virtualScreenWidth/2 - 50, virtualScreenHeight/2 + 20, 100, 10, palette[3]);
            else DrawRectangleLines(virtualScreenWidth/2 - 50, virtualScreenHeight/2 + 40, 100, 10, palette[3]);
        }
    //    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) selectRestart = !selectRestart, PlaySound(menuBlip);

    }

    bool aWinnerIsYou = false;
    bool selectRestart = true;
};
GameOverScreen gameOver;

int main()
{

    InitWindow(screenWidth, screenHeight, "Florida Man");
    InitAudioDevice();
    Music mainMenu = LoadMusicStream("src/_resources/sounds/d1.mp3");
    Music gameplay = LoadMusicStream("src/_resources/sounds/theLifeNeurotic.mp3");
    PlayMusicStream(mainMenu);
    mainMenu.looping = true;
    Sound menuBlip = LoadSound("src/_resources/sounds/menuBlip.wav");
    Sound ouch = LoadSound("src/_resources/sounds/hurt.wav");

    GameScreen currentScreen = GameScreen::TITLE;

    std::vector<int> myVector;

    SetTargetFPS(60);

    // Image icon = LoadImage("icons/Pictures/Untitled.png"); WINDOW ICON
    // ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    // SetWindowIcon(icon);
    // UnloadImage(icon);

    Player player = Player(0.0f,0.0f);
    std::vector<Sniper> snipers;
    std::vector<Crusty> crusties;
    //std::vector<Vector2> ground;
        

    // Texture2D backTile1 = LoadTexture("src/_resources/textures/backTile1.png");
    // Texture2D backTile2 = LoadTexture("src/_resources/textures/backTile2.png");
    // Texture2D backTile3 = LoadTexture("src/_resources/textures/backTile3.png");
    // Texture2D backTile4 = LoadTexture("src/_resources/textures/backTile4.png");
    // Texture2D backTile5 = LoadTexture("src/_resources/textures/backTile5.png");
    // Texture2D backTile6 = LoadTexture("src/_resources/textures/backTile6.png");
    // Texture2D backTile7 = LoadTexture("src/_resources/textures/backTile7.png");
    // Texture2D backTile8 = LoadTexture("src/_resources/textures/backTile8.png");
    // Texture2D backTile9 = LoadTexture("src/_resources/textures/backTile9.png");
    // Texture2D floor32 = LoadTexture("src/_resources/textures/32x32_floor.png");
    // Texture2D nullWpn = LoadTexture("src/_resources/textures/null_weapon_icon.png");
    // Texture2D defaultWpn = LoadTexture("src/_resources/textures/default_weapon_icon.png");
    // Texture2D flameWpn = LoadTexture("src/_resources/textures/flamethrower_weapon_icon.png");
    // Texture2D laserWpn = LoadTexture("src/_resources/textures/laser_weapon_icon.png");
    // Texture2D spaceWpn = LoadTexture("src/_resources/textures/spaceshot_weapon_icon.png");

    // THEN CALL DrawTexture(backtile1, 0(posX), 0(posY), WHITE(tint));

    // MAP VARIABLES
    int mapWidth = 64;
    int mapHeight = 10;
    float cellSize = 16;
    float mapX = 0.0f;
    float mapY = 0.0f;
    int tileMap[] = {
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,3,0,0,0,0,3,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    // BLOCKS ** Height and width will always be 32 pixels **
    std::vector<EnvItem> envItems;

    for (float y = 0; y < mapHeight; ++y)
    {
        for (float x = 0; x < mapWidth; ++x)
        {
            int i = x + y * mapWidth;
            int tile = tileMap[i];
            
            if(tile){
                float cellX = (mapX + cellSize * x);
                float cellY = (mapY + cellSize * y);
                if(tile == 1){
                    Color c = (i - mapWidth >= 0 && tileMap[i - mapWidth] == 1) ? palette[3] : palette[2]; // Checks for block above
                    envItems.push_back(EnvItem({{cellX, cellY, cellSize, cellSize}, 1, c}));
                }
                else if(tile == 2){
                    player.playerX = x*cellSize;
                    player.playerY = y*cellSize;
                }
                
                else if(tile == 3){
                    snipers.push_back(Sniper({x*cellSize, y*cellSize + 0.5f},25,100));
                }

                else if(tile == 4){
                    crusties.push_back(Crusty({x*cellSize, y*cellSize}));
                    break;
                }
            } 
        }
    }
    
    std::vector<EnvItem> *envItemsPtr = &envItems;
    int envItemsLength = envItems.size();
    int sniperLength = snipers.size();
    int crustyLength = crusties.size();
    Player *p = &player;

    Camera2D worldSpaceCamera = { 0 };  // Game world camera
    worldSpaceCamera.zoom = 1.0f;

    Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    Rectangle destRec = { -virtualRatio, -virtualRatio, screenWidth + (virtualRatio*2), screenHeight + (virtualRatio*2) };

    Vector2 origin = { 0.0f, 0.0f };

    float rotation = 0.0f;
    float cameraX = 0.0f;
    float cameraY = 0.0f;

    int textOffsetX = 0;
    int textOffsetY = 0;
    int textTimer = 0;
    int backTimer = 0;

    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
        case GameScreen::TITLE:
        {
            cameraX = 60.0f;
            cameraY = 60.0f;

            // Set the camera's target to the values computed above
            screenSpaceCamera.target = (Vector2){ cameraX, cameraY };

            // Round worldSpace coordinates, keep decimals into screenSpace coordinates
            worldSpaceCamera.target.x = (int)screenSpaceCamera.target.x;
            screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
            screenSpaceCamera.target.x *= virtualRatio;

            worldSpaceCamera.target.y = (int)screenSpaceCamera.target.y;
            screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
            screenSpaceCamera.target.y *= virtualRatio;

            textOffsetX = (int)(sin(GetTime()) * 10.0f);
            textOffsetY = (int)(cos(GetTime()) * 10.0f);

            if(IsKeyPressed(KEY_ENTER)) 
            {
                currentScreen = GameScreen::GAMEPLAY;
                StopMusicStream(mainMenu);
                PlayMusicStream(gameplay);
            }

            BeginTextureMode(target);
                ClearBackground(palette[0]);

                BeginMode2D(worldSpaceCamera);

                    if(backTimer > 70) DrawRectangle(0, 0, virtualScreenWidth, 20, palette[3]), DrawRectangle(0, 20, virtualScreenWidth, 20, palette[2]);
                    else DrawRectangle(0, 0, virtualScreenWidth, 20, palette[2]), DrawRectangle(0, 20, virtualScreenWidth, 20, palette[3]);
                    if(backTimer > 140) backTimer = 0;
                    else backTimer++;
                    
                    // UI
                    DrawText("Florida Man", virtualScreenWidth / 2 + 1 + textOffsetX, virtualScreenHeight / 2 + 30 + textOffsetY, 18, palette[1]);
                    DrawText("Florida Man", virtualScreenWidth / 2 + 2 + textOffsetX, virtualScreenHeight / 2 + 31 + textOffsetY, 18, palette[2]);
                    DrawText("Florida Man", virtualScreenWidth / 2 + 3 + textOffsetX, virtualScreenHeight / 2 + 32 + textOffsetY, 18, palette[3]);

                    if(textTimer > 40) DrawText("PRESS ENTER TO START", virtualScreenWidth / 2 - 6, virtualScreenHeight / 2 + 80, 4, palette[3]);
                    if(textTimer > 80) textTimer = 0;
                    else textTimer++;
                    
                EndMode2D();
            EndTextureMode();

            BeginDrawing();
                BeginMode2D(screenSpaceCamera);
                    DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
                EndMode2D();
            EndDrawing();

        }
        break;
        
        case GameScreen::GAMEPLAY:
        {
            if(IsKeyPressed(KEY_ENTER)) currentScreen = GameScreen::PAUSE;
                
            float deltaTime = GetFrameTime();

            player.Update(deltaTime, envItemsPtr, envItemsLength);

            cameraX = player.playerX - 70.0f;
            cameraY = 32.0f;

            // Set the camera's target to the values computed above
            screenSpaceCamera.target = (Vector2){ cameraX, cameraY };

            // Round worldSpace coordinates, keep decimals into screenSpace coordinates
            worldSpaceCamera.target.x = (int)screenSpaceCamera.target.x;
            screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
            screenSpaceCamera.target.x *= virtualRatio;

            worldSpaceCamera.target.y = (int)screenSpaceCamera.target.y;
            screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
            screenSpaceCamera.target.y *= virtualRatio;

            BeginTextureMode(target);
                ClearBackground(palette[0]);

                BeginMode2D(worldSpaceCamera);
                    for (int x = 0; x < mapWidth; ++x){
                        for (int i = 0; i < mapHeight; ++i) DrawTexture(backTile9, x*16, i*16, WHITE);
                    }

                    for (int i = 0; i < envItemsLength; i++) DrawTextureRec(floor32, envItems[i].rect, {envItems[i].rect.x, envItems[i].rect.y}, WHITE);

                    for (int i = 0; i < sniperLength; ++i) snipers[i].DrawSniper(palette[2], *p);

                    for (int i = 0; i < crustyLength; ++i) crusties[i].Draw(palette[2], *p);
                    player.Draw();
                    
                    DrawRectanglePro(player.sprite, origin, rotation, palette[1]);

                    // UI
                    DrawRectangle(player.playerX - 62, 35, 24.0f, 4, palette[1]);
                    DrawRectangle(player.playerX - 60, 36, (float)player.currentHealth/ (float)player.maxHealth * 20.0f, 2, palette[3]);
                    switch (player.currentWeapon)
                    {
                    case Weapon::PISTOL:
                        DrawTexture(defaultWpn, player.playerX + 72, 34, WHITE);
                        break;
                    
                    case Weapon::FLAMETHROWER:
                        DrawTexture(flameWpn, player.playerX + 72, 34, WHITE);
                        break;

                    case Weapon::LASER:
                        DrawTexture(laserWpn, player.playerX + 72, 34, WHITE);
                        break;

                    case Weapon::SPACE:
                        DrawTexture(spaceWpn, player.playerX + 72, 34, WHITE);
                        break;

                    default:
                        DrawTexture(nullWpn, player.playerX + 72, 34, WHITE);
                        break;
                    }
                    

                EndMode2D();
            EndTextureMode();

            BeginDrawing();
                ClearBackground(palette[0]);

                BeginMode2D(screenSpaceCamera);
                    DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
                EndMode2D();
                
                
            EndDrawing();
        }
        break;

        case GameScreen::BOSS:
        {

        }
        break;

        case GameScreen::PAUSE:
        {
            if(IsKeyPressed(KEY_ENTER)) currentScreen = GameScreen::GAMEPLAY;
            BeginDrawing();
                ClearBackground(palette[0]);

                BeginMode2D(screenSpaceCamera);
                    DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, palette[0]);
                EndMode2D();
                
                // UI
                DrawFPS(GetScreenWidth() - 95, 10);
                DrawText("PAUSED", GetScreenWidth() / 2 - 20, GetScreenHeight() / 2, 12, palette[3]);
            
            EndDrawing();
        }
        break;

        default:{}
        break;

        }

    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}