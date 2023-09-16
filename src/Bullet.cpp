#include "Bullet.h"
#include <raylib.h>

Bullet::Bullet()
{

}

void Bullet::Update()
{
    position.x += velocity.x;
    position.y += velocity.y;
}

void Bullet::Draw()
{
}