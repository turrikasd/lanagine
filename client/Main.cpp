#define PORT 54545
#define MOVE_PACKET_INTERVAL 100 // milliseconds

#include <iostream>
#include <SFML\Network.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <CompressedPacket.h>
#include <thread>
#include "World.h"
#include <NET_CODES.h>

sf::Window window;
World world;
bool notReady = true;
bool isActive = true;
unsigned long lastMove = 0;


void DrawingFunction()
{
	window.create(sf::VideoMode(800, 600), "Client");
	//window.setFramerateLimit(60);

	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Setup a perspective projection
	gluPerspective(90.f, 1.f, 1.f, 500.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}

			else if (event.type == sf::Event::GainedFocus)
			{
				isActive = true;
			}

			else if (event.type == sf::Event::LostFocus)
			{
				isActive = false;
			}
		}

		// Input

		if (isActive)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				world.GetClient()->Translate(-0.1f, 0, 0);
				std::cout << "MOVING: " << world.GetClient()->playerId << std::endl;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				world.GetClient()->Translate(0.1f, 0, 0);
				std::cout << "MOVING: " << world.GetClient()->playerId << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				world.GetClient()->Translate(0.0f, 0.1f, 0);
				std::cout << "MOVING: " << world.GetClient()->playerId << std::endl;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				world.GetClient()->Translate(0.0f, -0.1f, 0);
				std::cout << "MOVING: " << world.GetClient()->playerId << std::endl;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f); // RED

		// Draw all players

		world.DrawPlayers();

		glEnd(); // triangles

		window.display();
	}
}

void HandlePacket(CompressedPacket packet)
{
	sf::Int16 net_code;
	packet >> net_code;

	if (net_code == NC_NEW_YOU)
	{
		int playerId;
		char name[32];
		float x, y, z;
		packet >> playerId >> name >> x >> y >> z;

		world.NewPlayer(playerId, name, true); // checks if player already exists
		world.MovePlayer(playerId, x, y, z);
		notReady = false;
		return;
	}

	else if (net_code == NC_NEW_PLAYER)
	{
		int playerId;
		char name[32];
		float x, y, z;
		packet >> playerId >> name >> x >> y >> z;

		world.NewPlayer(playerId, name); // checks if player already exists
		world.MovePlayer(playerId, x, y, z);
		return;
	}

	else if (net_code == NC_MOVEMENT)
	{
		int playerID;
		float x, y, z;
		packet >> playerID >> x >> y >> z;

		world.MovePlayer(playerID, x, y, z);
		return;
	}
}

void ListenForPackets(sf::UdpSocket* socket)
{
	while (true)
	{
		CompressedPacket packet;
		sf::IpAddress sender;
		unsigned short port;
		if (socket->receive(packet, sender, port) != sf::Socket::Done)
		{
			// err
		}

		std::thread msgThread = std::thread(&HandlePacket, packet);
		msgThread.detach();

		//std::cout << "Packet from server. Says: " << replyData << std::endl;
	}
}

int main(int argc, char* argv[])
{
	sf::IpAddress serverIp = "127.0.0.1";
	sf::UdpSocket socket;

	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		// err
		return EXIT_FAILURE;
	}

	std::thread DrawThread = std::thread(&DrawingFunction);
	DrawThread.detach();

	std::thread NetListenThread = std::thread(&ListenForPackets, &socket);
	NetListenThread.detach();

	{
		char name[32];
		std::cout << "Enter name: " << std::endl;
		std::cin >> name;

		CompressedPacket namePacket;
		namePacket << NC_LOGIN << name;

		socket.send(namePacket, serverIp, PORT);
	}

	while (true)
	{
		if (notReady || lastMove + MOVE_PACKET_INTERVAL > GetTickCount()) // Don't send if hasn't been MOVE_PACKET_INTERVAL since last update
			continue; // Don't try to access player if it's not set yet

		if (world.GetClient()->hasMoved)
		{
			lastMove = GetTickCount(); // Used to avoid updating too frequently

			CompressedPacket packet;

			packet << NC_MOVEMENT << world.GetClient()->playerId << world.GetClient()->x << world.GetClient()->y << world.GetClient()->z;

			world.GetClient()->hasMoved = false;

			if (socket.send(packet, serverIp, PORT))
			{
				// ERR
			}
		}


		/*
		int a, b, c, d;
		CompressedPacket packet;
		std::cin >> a;
		std::cin >> b;
		std::cin >> c;
		std::cin >> d;
		packet << NC_MOVEMENT << a << b << c << d;

		if (socket.send(packet, serverIp, PORT))
		{
			// error
		}
		*/
	}

	socket.unbind();
	return EXIT_SUCCESS;
}

