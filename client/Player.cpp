#include "Player.h"
#include <SFML\OpenGL.hpp>

Player::Player(int playerId, char* name)
{
	this->playerId = playerId;
	this->name = name;

	this->x = 0;
	this->y = 0;
	this->z = 0;
}

void Player::SetPos(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Player::Draw()
{
	glVertex3i(x - 1, y - 1, z - 5);
	glVertex3i(x + 1, y - 1, z - 5);
	glVertex3i(x, y + 1, z - 5);
}


Player::~Player()
{
}
