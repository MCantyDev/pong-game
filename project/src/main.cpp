#include "Game.h"

#include <memory>

int main()
{
	std::unique_ptr<Game> game = std::make_unique<Game>();;
	game->run();
}