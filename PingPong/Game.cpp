#include "Game.hpp"

Game::Game()
{
	playerScore = 0;
	cpuScore = 0;

	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 500;
	ball.speed_y = 500;

	// player paddle
	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 600;

	// cpu paddle
	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height / 2 - cpu.height / 2;
	cpu.speed = 600;
}

void Game::Run()
{
	InitWindow(screen_width, screen_height, "Ping Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		Update(dt);
		CheckCollision();

		BeginDrawing();
		ClearBackground(BLACK);
		Draw();
		EndDrawing();
	}

	CloseWindow();
}

void Game::Update(float dt)
{
	ball.Update(dt);
	player.Update(dt);
	cpu.Update(ball.y, dt);
}

void Game::Draw()
{
	DrawLine(screen_width / 2, 0,
		screen_width / 2, screen_height, WHITE);

	ball.Draw();
	player.Draw();
	cpu.Draw();

	DrawText(TextFormat("%i", cpuScore),
		screen_width / 4 - 20, 20, 80, WHITE);

	DrawText(TextFormat("%i", playerScore),
		3 * screen_width / 4 - 20, 20, 80, WHITE);
}

void Game::CheckCollision()
{
	// Paddle collision
	if (CheckCollisionCircleRec(
		Vector2{ ball.x, ball.y },
		ball.radius,
		Rectangle{ player.x, player.y, player.width, player.height }))
	{
		ball.speed_x *= -1;
	}

	if (CheckCollisionCircleRec(
		Vector2{ ball.x, ball.y },
		ball.radius,
		Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
	{
		ball.speed_x *= -1;
	}

	// Right wall → CPU scores
	if (ball.x + ball.radius >= screen_width)
	{
		cpuScore++;
		ball.ResetBall();
	}

	// Left wall → Player scores
	if (ball.x - ball.radius <= 0)
	{
		playerScore++;
		ball.ResetBall();
	}
}