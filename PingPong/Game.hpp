#pragma once

#include <raylib.h>
#include "Ball.hpp"
#include "Paddle.hpp"

class Game
{
public:
	Game();
	
	void Run();

private:
	void Update(float dt);

	void Draw();

	void CheckCollision();
	
private:
	Ball ball;
	Paddle player;
	CpuPaddle cpu;

	int playerScore;
	int cpuScore;

	const int screen_width = 1280;
	const int screen_height = 800;
};