#include <raylib.h>
#include <math.h>
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

    char *text = "Health: ";
    int currentHealth = 100;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

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

        player.Update();

        BeginTextureMode(target);
            ClearBackground(palette[0]);

            BeginMode2D(worldSpaceCamera);
                for (int i = 50; i > 0; --i)
                {
                    int c = i % 4;
                    DrawCircle(0, 100, i, palette[c]);
                }
                for (int i = 50; i > 0; --i)
                {
                    int c = (i % 4) + 1;
                    DrawCircle(100, 100, i, palette[c]);
                }
                for (int i = 50; i > 0; --i)
                {
                    int c = (i % 4) + 2;
                    DrawCircle(200, 100, i, palette[c]);
                }
                for (int i = 50; i > 0; --i)
                {
                    int c = (i % 4) + 3;
                    DrawCircle(300, 100, i, palette[c]);
                }
                
                DrawRectanglePro(player.position, origin, rotation, palette[1]);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(palette[0]);

            BeginMode2D(screenSpaceCamera);
                DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, palette[0]);
            EndMode2D();

            DrawFPS(GetScreenWidth() - 95, 10);
            DrawText(text, 20, 10, 20, palette[3]);
            DrawText(TextFormat("Sprint Left: %i", player.sprintTimerLeft), 100, 10, 20, palette[3]);
            DrawText(TextFormat("Sprint Rght: %i", player.sprintTimerRight), 100, 30, 20, palette[3]);
        EndDrawing();
    }

    UnloadMusicStream(track);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}