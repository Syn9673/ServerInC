//
// Created by alexander on 8/24/2020.
//

#ifndef C_TANKPACKET_H
#define C_TANKPACKET_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int type;
	int message;
	int netID;
	uint32_t padding1;
	uint32_t state;
	uint32_t padding2;
	uint32_t delay;
	float playerX;
	float playerY;
	float playerSpeedX;
	float playerSpeedY;
	uint32_t padding3;
	int punchLocationX;
	int punchLocationY;
	uint32_t tankDataSize;
	char* tankData;
} TankHeader;

// convert the header to a valid tank packet, make sure that you add the data before calling this func.
int tankheader_parse(unsigned char** bytes, TankHeader* header)
{
	const int MAX_SIZE = 60;
	*bytes = malloc(MAX_SIZE + header->tankDataSize + 1);

	memcpy(*bytes, header, MAX_SIZE);
	memcpy((*bytes) + MAX_SIZE, header->tankData, header->tankDataSize);

	return MAX_SIZE + header->tankDataSize + 1;
};

// set tank data, this will free the data after use
void tankdata_set(TankHeader* header, int size, unsigned char** data)
{
	if (header->tankData == NULL || !header->tankData)
	{
		printf("Malloc tankdata\n");
		header->tankData = malloc(0);
	}

	// reallocate data
	header->tankData = realloc(header->tankData, size + 1);
	memcpy(header->tankData, *data, size + 1);

	free(*data);
}

#endif //C_TANKPACKET_H
