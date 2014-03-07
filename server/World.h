#pragma once

#include <Connection.h>
#include "Player.h"
#include <map>

class World
{
public:
	int NewPlayer(Connection* connection, char* name);
	void MovePlayer(int playerId, float x, float y, float z);
	Player* GetPlayer(int id);

public:
	std::vector<Player> players;
};

