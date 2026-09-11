#pragma once
#include <raylib.h>

class Paddle
{
public:
    float x, y;
    float width, height;
    float speed;

    void Draw();
    void Update(float dt);
protected:
    void LimitMovement();
};

class CpuPaddle : public Paddle
{
public:
    void Update(float ballY, float dt);
};