#pragma once

#include <Connection.h>
#include <vector>

class Player
{
public:
	Player(int playerId, Connection* connection, char* name);
	~Player();

	void SetPos(float x, float y, float z);

public:
	int playerId;
	char* name;
	float x, y, z;
	Connection* connection;

private:


};