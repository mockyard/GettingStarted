#pragma once
#include <raylib.h>

class Ball
{
public:
	float x, y;
	float speed_x, speed_y;
	int radius;

	void Draw();
	void Update(float dt);
	void ResetBall();
};