#pragma once

#include <Connection.h>
#include <vector>

class Player
{
public:
	Player(int playerId, char* name);
	~Player();

	void SetPos(int x, int y, int z);
	void Translate(int x, int y, int z);
	void Draw();

public:

	static int clientPlayerId;
	int playerId;
	bool hasMoved;
	int x, y, z;

private:

	char* name;
};