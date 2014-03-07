#include "World.h"


int World::NewPlayer(Connection* connection, char* name)
{
	int id = std::distance(players.begin(), players.end());

	Player player = Player(id, connection, name); // Create new player

	std::vector<Player>::iterator it;
	it = players.end();
	players.insert(it, player);

	return id;
}

void World::MovePlayer(int playerId, int x, int y, int z)
{
	players[playerId].SetPos(x, y, z);
}

Player* World::GetPlayer(int id)
{
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if (it->playerId == id)
			return &(*it);
	}

	return NULL;
}