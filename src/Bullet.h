#pragma once
#include <raylib.h>

class Bullet
{
public:
    Bullet();
    void Update();
    void Draw();

    Vector2 velocity;
    Vector2 position;
    Color color;
    float radius;
    bool isActive;
    bool isOwnedByPlayer;
};
