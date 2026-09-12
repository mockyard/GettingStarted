#include "Ball.hpp"

void Ball::Draw()
{
	DrawCircleV(
		Vector2{x, y}, radius, WHITE
	);
}

void Ball::Update(float dt)
{
	x += speed_x * dt;
	y += speed_y * dt;

	if (y + radius >= GetScreenHeight() || y - radius <= 0)
		speed_y *= -1;
}

void Ball::ResetBall()
{
	x = GetScreenWidth() / 2;
	y = GetScreenHeight() / 2;

	int direction[2] = { -1, 1 };

	speed_x = 500 * direction[GetRandomValue(0, 1)];
	speed_y = 500 * direction[GetRandomValue(0, 1)];
}
