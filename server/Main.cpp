// Server.cpp : Defines the entry point for the console application.
//

#define PORT 54545

#include <iostream>
#include <UDPServer.h>
#include <ErrorReporter.h>


int main(int argc, char* argv[])
{
	int err;
	nw::UDPServer udpServer;

	err = udpServer.ServerRegisterSocket(PORT);
	if (err)
	{
		nw::Report(err);
		return EXIT_FAILURE;
	}

	udpServer.ServerEnterListenMode();

	int a;
	std::cin >> a;

	return EXIT_SUCCESS;
}

