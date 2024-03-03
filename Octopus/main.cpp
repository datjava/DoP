//Using SDL and standard IO
#include "Play_game.h"
Game* game = NULL;
int main(int argc, char* args[])
{
	game = new Game();
	if(game->init())std::cout << "Game init success" << std::endl;
	else std::cout << "Game init failed" << std::endl;
	while (game->isRunning())
	{
		game->MediaLoad();
		game->handleInput();
		//std::cout << "Game is running" << std::endl;
	}
	return 0;
}