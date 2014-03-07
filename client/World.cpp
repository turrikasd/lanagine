#include "World.h"

Player* World::GetPlayer(int id)
{
	playersMutex.lock();

	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if (it->playerId == id)
		{
			playersMutex.unlock();
			return &(*it);
		}
	}

	playersMutex.unlock();

	return NULL;
}

void World::NewPlayer(int playerId, char* name, bool isYou)
{
	playersMutex.lock();

	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if (it->playerId == playerId)
		{
			playersMutex.unlock();
			return;
		}
	}

	Player player = Player(playerId, name); // Create new player

	std::vector<Player>::iterator it;
	it = players.end();
	players.insert(it, player);

	playersMutex.unlock();

	if (isYou)
		Player::clientPlayerId = playerId;
}

void World::MovePlayer(int playerId, float x, float y, float z)
{
	playersMutex.lock();

	players[playerId].SetPos(x, y, z);

	playersMutex.unlock();
}

void World::DrawPlayers()
{
	playersMutex.lock();

	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
	{
		it->Draw();
	}

	playersMutex.unlock();
}