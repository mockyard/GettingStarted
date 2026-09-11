#include <iostream>
#include <raylib.h>

int player_score{ 0 };
int cpu_score{ 0 };

class Ball
{
public:
	float x, y;
	float speed_x, speed_y;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}

	void Update(float deltaTime)
	{

		x += speed_x * deltaTime;
		y += speed_y * deltaTime;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;
		}

		if (x + radius >= GetScreenWidth())
		{
			cpu_score++;
			ResetBall();
		};

		if (x - radius <= 0)
		{

			player_score++;
			ResetBall();
		};
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1,1 };
		speed_x = 300 * speed_choices[GetRandomValue(0, 1)];
		speed_y = 300 * speed_choices[GetRandomValue(0, 1)];
	}
};

class Paddle
{
public:
	float x, y;
	float width, height;
	float speed;

	void Draw()
	{
		DrawRectangle(x, y, width, height, WHITE);
	}

	void Update(float deltaTime)
	{


		if (IsKeyDown(KEY_UP))
		{
			y -= speed * deltaTime;
		}

		if (IsKeyDown(KEY_DOWN))
		{
			y += speed * deltaTime;
		}

		LimitMovement();
	}

protected:
	void LimitMovement()
	{
		if (y <= 0)
		{
			y = 0;
		}

		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}
	}
};

// inheritance
class CpuPaddle : public Paddle
{
public:

	void Update(int ball_y, float deltaTime)
	{

		if (y + height / 2 > ball_y)
		{
			y -= speed * deltaTime;
		}

		if (y + height / 2 <= ball_y)
		{
			y += speed * deltaTime;
		}

		LimitMovement();
	}
};



int main()
{
	Ball ball;
	Paddle player;
	CpuPaddle cpu;

	const int screen_width = 1280;
	const int screen_height = 800;

	InitWindow(screen_width, screen_height, "Ping Pong");
	SetTargetFPS(60);

	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 300;
	ball.speed_y = 300;

	// player paddle
	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 400;

	// cpu paddle
	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height / 2 - cpu.height / 2;
	cpu.speed = 400;

	while (!WindowShouldClose())
	{
		// delta time
		double dt = GetFrameTime();

		// update
		ball.Update(dt);
		player.Update(dt);
		cpu.Update(ball.y, dt);

		// check for collision
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
		{
			ball.speed_x *= -1;

		}

		// DRAW
		BeginDrawing();


		ClearBackground(BLACK);

		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

		ball.Draw();
		player.Draw();
		cpu.Draw();

		DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

		EndDrawing();

	}

	CloseWindow();

	return 0;
}

/*
* Game works on 3 things
* 1. Check for events
* 2. Update as per action
* 3. Draw
*/