#pragma once

#include <Connection.h>
#include <vector>

class Player
{
public:
	Player(int playerId, char* name);
	~Player();

	void SetPos(int x, int y, int z);
	void Draw();

public:
	int playerId;

private:

	char* name;
	int x, y, z;
};