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

    //Player player = Player();

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

    // Player vars
    float playerX = 10.0f;
    float playerY = 140.0f;
    Rectangle player = { playerX, playerY, 20.0f, 20.0f };
    float speed = 2.0f;
    float gravity = 0.5f;
    int jumpTimer = 0;
    bool canJump = true;

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

        cameraX = playerX - 70.0f;
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

        if(IsKeyDown(KEY_D)) playerX += 2.0f;
        if(IsKeyDown(KEY_A)) playerX -= 2.0f;

        if (IsKeyDown(KEY_SPACE) && canJump)
        {
            speed -= 0.5f;
            canJump = false;
            jumpTimer = 15;
            gravity = 0.5f;
        } else if(!canJump && jumpTimer < 2) {
            playerY += 3.0f * gravity;
            gravity += 0.1f;
        }

        if(jumpTimer > 0 && !canJump)
        {
            playerY -= 0.5f * jumpTimer;
            jumpTimer--;
        }

        if(playerY > 140.0f)
        {
            canJump = true;
            speed = 2.0f;
            jumpTimer = 0;
        }

        player = { playerX, playerY, 20.0f, 20.0f };

        BeginTextureMode(target);
            ClearBackground(WHITE);

            BeginMode2D(worldSpaceCamera);
                DrawCircle(100, 100, 50, GREEN);
                DrawRectanglePro(player, origin, rotation, RED);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RED);

            BeginMode2D(screenSpaceCamera);
                DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
            EndMode2D();

            DrawFPS(GetScreenWidth() - 95, 10);
            DrawText(text, 20, 10, 20, BLACK);
            DrawText(TextFormat("%i", currentHealth), 100, 10, 20, RED);
        EndDrawing();


    }

    UnloadMusicStream(track);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}