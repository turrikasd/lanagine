#pragma once

#include <Connection.h>
#include "Player.h"
#include <map>

class World
{
public:
	void NewPlayer(int playerId, char* name);
	void MovePlayer(int playerId, int x, int y, int z);

public:
	std::vector<Player> players;
};

