#include "Paddle.hpp"

void Paddle::Draw()
{
    DrawRectangleRec(
        Rectangle{ x, y, width, height },
        WHITE
    );
}

void Paddle::Update(float dt)
{
    if (IsKeyDown(KEY_UP))
        y -= speed * dt;

    if (IsKeyDown(KEY_DOWN))
        y += speed * dt;

    LimitMovement();
}

void Paddle::LimitMovement()
{
    if (y < 0)
        y = 0;

    if (y + height > GetScreenHeight())
        y = GetScreenHeight() - height;
}

void CpuPaddle::Update(float ballY, float dt)
{
    float center = y + height / 2;
    const float tolerance = 8.0f;

    if (center < ballY - tolerance)
        y += speed * dt;
    else if (center > ballY + tolerance)
        y -= speed * dt;


    LimitMovement();
}