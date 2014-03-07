#include "Player.h"

Player::Player(int playerId, Connection* connection, char* name)
{
	this->playerId = playerId;
	this->connection = connection;
	this->name = name;

	this->x = 0;
	this->y = 0;
	this->z = 0;
}

void Player::SetPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Player::~Player()
{
}
