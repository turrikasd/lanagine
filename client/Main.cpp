#define PORT 54545

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
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f); // RED

		// Draw all players
		for (std::vector<Player>::iterator it = world.players.begin(); it != world.players.end(); ++it)
		{
			it->Draw();
		}

		glEnd(); // triangles

		window.display();
	}
}

void HandlePacket(CompressedPacket packet)
{
	sf::Int16 net_code;
	packet >> net_code;

	if (net_code == NC_NEW_PLAYER)
	{
		int playerId;
		char name[32];
		int x, y, z;
		packet >> playerId >> name >> x >> y >> z;

		world.NewPlayer(playerId, name); // checks if player already exists
		world.MovePlayer(playerId, x, y, z);
		return;
	}

	if (net_code == NC_MOVEMENT)
	{
		int playerID;
		int x, y, z;
		packet >> playerID >> x >> y >> z;

		world.MovePlayer(playerID, x, y, z);
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
	sf::IpAddress serverIp = "85.23.150.216";
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
		namePacket << (sf::Int16)NC_LOGIN << name;

		socket.send(namePacket, serverIp, PORT);
	}

	while (true)
	{
		int a, b, c, d;
		CompressedPacket packet;
		std::cin >> a;
		std::cin >> b;
		std::cin >> c;
		std::cin >> d;
		packet << (sf::Int16)NC_MOVEMENT << a << b << c << d;

		if (socket.send(packet, serverIp, PORT))
		{
			// error
		}
	}

	socket.unbind();
	return EXIT_SUCCESS;
}

