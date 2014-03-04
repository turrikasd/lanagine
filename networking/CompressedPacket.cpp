#include "CompressedPacket.h"
#include <EZLIB\easyzlib.h>
#include <iostream>

const int MAX_DATA_SIZE = 1024;
const int MAX_COMPRESSED_SIZE = EZ_COMPRESSMAXDESTLENGTH(MAX_DATA_SIZE);

const void* CompressedPacket::onSend(std::size_t& size)
{
	const unsigned char* sourceData = (unsigned char*)getData();
	long sourceLength = getDataSize();

	unsigned char destinationData[MAX_COMPRESSED_SIZE];
	long destinationLength;


	ezcompress(destinationData, &destinationLength, sourceData, sourceLength);
	std::cout << "Sending compressed data of size: " << destinationLength << " bytes. Original was: " << sourceLength << " bytes." << std::endl;

	size = destinationLength;
	free(finalData);
	finalData = (char*)malloc(destinationLength);
	
	for (long l = 0; l < destinationLength; l++)
		finalData[l] = destinationData[l];

	return finalData;
	// return Packet::onSend(size);
}

void CompressedPacket::onReceive(const void* data, std::size_t size)
{
	unsigned char* sourceData = (unsigned char*)data;
	long sourceLength = size;

	unsigned char destinationData[MAX_DATA_SIZE];
	long destinationLength;

	ezuncompress(destinationData, &destinationLength, sourceData, sourceLength);
	std::cout << "Received compressed data of size: " << sourceLength << " bytes. Uncompressed size: " << destinationLength << " bytes." << std::endl;

	append(destinationData, destinationLength);

	// Packet::onReceive(data, size);
}
