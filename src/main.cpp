#include <raylib.h>
#include <math.h>
#include "raymath.h"
#include "Player.h"
#include <stdio.h>

int main()
{

    const int screenWidth = 640;
    const int screenHeight = 576;

    const int virtualScreenWidth = 160;
    const int virtualScreenHeight = 144;

    const float virtualRatio = (float)screenWidth/(float)virtualScreenWidth;


    InitWindow(screenWidth, screenHeight, "Untitled");
    InitAudioDevice();
    Music track = LoadMusicStream("C:/Users/zrouh/Music/Projects/roshe.mp3");
    //PlayMusicStream(track);
    track.looping = true;

    SetTargetFPS(60);

    // HOW TO ADD SPRITES:
    // Texture2D mySprite = LoadTexture("C:/Users/zrouh/OneDrive/Pictures/Untitled.png");
    // THEN CALL DrawTexture(mySprite, 0(posX), 0(posY), WHITE(tint));

    // TODO: MAKE BLOCKS COLLIDE WITH PLAYER
    EnvItem envItems[] = {
        {{ 0, 0, 10, 4 }, 0, GRAY },
        {{ 0, 120, 10, 20 }, 1, GRAY },
        {{ 300, 120, 40, 10 }, 1, GRAY },
        {{ 250, 130, 10, 10 }, 1, GRAY },
        {{ 650, 130, 10, 10 }, 1, GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    Camera2D worldSpaceCamera = { 0 };  // Game world camera
    worldSpaceCamera.zoom = 1.0f;

    Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    Player player = Player();

    Color palette[] = { GetColor(0x622e4cff), GetColor(0x7550e8ff), GetColor(0x608fcfff), GetColor(0x8be5ffff)};

    Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    Rectangle destRec = { -virtualRatio, -virtualRatio, screenWidth + (virtualRatio*2), screenHeight + (virtualRatio*2) };

    Vector2 origin = { 0.0f, 0.0f };

    float rotation = 0.0f;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime, envItems, envItemsLength);

        int hitObstacle = 0;
        for (int i = 0; i < envItemsLength; i++)
        {
            EnvItem *ei = envItems + i;
            if (ei->blocking &&
                player.playerX < ei->rect.x + ei->rect.width &&
                player.playerX + 20 > ei->rect.x &&
                player.playerY + player.sprite.height > ei->rect.y &&
                player.playerY < ei->rect.y + ei->rect.height) {
                hitObstacle = 1;
                player.speed = 0.0f;
                player.playerY = ei->rect.y - player.sprite.height;
            }
        }

        if (!hitObstacle)
        {
            player.playerY += player.speed*deltaTime;
            player.speed += player.gravity*deltaTime;
        }
        else player.canJump = true;

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
                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, palette[3]);

                DrawRectanglePro(player.sprite, origin, rotation, palette[1]);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(palette[3]);

            BeginMode2D(screenSpaceCamera);
                DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, palette[0]);
            EndMode2D();

            // UI
            DrawFPS(GetScreenWidth() - 95, 10);
            DrawText(TextFormat("%i", player.currentHealth), 10, 10, 20, palette[3]);
            DrawText(TextFormat("%i", player.currentSpecial), 10, 30, 20, palette[3]);
            DrawText(TextFormat("%f", player.playerX), 100, 30, 20, palette[3]);
            DrawRectangle(50, 14, player.currentHealth/player.maxHealth * 100, 10, palette[2]);
            DrawRectangle(45, 34, player.currentSpecial/player.maxSpecial * 100, 10, palette[3]);
            
        EndDrawing();
    }

    UnloadMusicStream(track);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}