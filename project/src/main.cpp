#include "Game.h"
#include <Windows.h>

int main()
{
	std::unique_ptr<Game> game = std::make_unique<Game>();
	game->run();
}

// Entry Point WinMain for When building in Release Mode on Windows
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	return main();
}