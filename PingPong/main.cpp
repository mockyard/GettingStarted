#include <iostream>
#include <raylib.h>
#include "Game.hpp"

int main()
{
	Game game;
	game.Run();
	
	return 0;
}

/*
* Game works on 3 things
* 1. Check for events
* 2. Update as per action
* 3. Draw
*/