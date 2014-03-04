#pragma once
#include <SFML\Network.hpp>

class CompressedPacket : public sf::Packet
{
public:
	virtual const void* onSend(std::size_t& size);
	virtual void onReceive(const void* data, std::size_t size);

private:
	char* finalData;
};

