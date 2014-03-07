#pragma once

#include <Connection.h>
#include "Player.h"
#include <map>
#include <mutex>

class World
{
public:
	void NewPlayer(int playerId, char* name, bool isYou);
	void NewPlayer(int playerId, char* name) { NewPlayer(playerId, name, false); } // Calls NewPlayer with false
	void MovePlayer(int playerId, int x, int y, int z);
	Player* GetPlayer(int id);
	Player* GetClient() { return GetPlayer(Player::clientPlayerId); }
	void DrawPlayers();

public:
	std::vector<Player> players;
	std::mutex playersMutex;

private:
	
};

