#include "ErrorReporter.h"
#include <map>
#include <string>
#include <iostream>

bool initialized = false;
std::map<int, std::string> ErrorMap;

void Initialize()
{
	ErrorMap[NETWORK_NO_ERROR] = "NETWORK_NO_ERROR";
	ErrorMap[NETWORK_ERROR_INVALID_PORT] = "NETWORK_ERROR_INVALID_PORT";
	ErrorMap[NETWORK_ERROR_SOCKET_NOT_BOUND] = "NETWORK_ERROR_SOCKET_NOT_BOUND";
	ErrorMap[NETWORK_ERROR_UDP_PACKET_FAULT] = "NETWORK_ERROR_UDP_PACKET_FAULT";
}

void nw::Report(int err)
{
	if (!initialized)
	{
		Initialize();
		initialized = true;
	}

	std::cout << "Error " << err << ": " << ErrorMap[err] << std::endl;
}