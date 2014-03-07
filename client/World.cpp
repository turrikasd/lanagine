#include "World.h"


void World::NewPlayer(int playerId, char* name)
{
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if (it->playerId == playerId)
			return;
	}

	Player player = Player(playerId, name); // Create new player

	std::vector<Player>::iterator it;
	it = players.end();
	players.insert(it, player);
}

void World::MovePlayer(int playerId, int x, int y, int z)
{
	players[playerId].SetPos(x, y, z);
}