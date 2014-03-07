#pragma once

#include <Connection.h>
#include <vector>

class Player
{
public:
	Player(int playerId, Connection* connection, char* name);
	~Player();

	void SetPos(int x, int y, int z);

public:
	int playerId;
	char* name;
	int x, y, z;

private:

	Connection* connection;
};