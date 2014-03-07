#pragma once

#include <Connection.h>
#include <vector>

class Player
{
public:
	Player(int playerId, char* name);
	~Player();

	void SetPos(float x, float y, float z);
	void Translate(float x, float y, float z);
	void Draw();

public:

	static int clientPlayerId;
	int playerId;
	bool hasMoved;
	float x, y, z;

private:

	char* name;
};