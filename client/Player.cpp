#include "Player.h"
#include <SFML\OpenGL.hpp>

// static members
int Player::clientPlayerId;

Player::Player(int playerId, char* name)
{
	this->playerId = playerId;
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

void Player::Translate(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;

	this->hasMoved = true;
}

void Player::Draw()
{
	glVertex3f(x - 1, y - 1, z - 5);
	glVertex3f(x + 1, y - 1, z - 5);
	glVertex3f(x, y + 1, z - 5);
}


Player::~Player()
{
}
