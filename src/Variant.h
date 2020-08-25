//
// Created by alexander on 8/24/2020.
//

#ifndef C_VARIANT_H
#define C_VARIANT_H

#include "./src/TankPacket.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void variant_init(TankHeader* header)
{
	// malloc them for the arg count
	header->tankDataSize = 0;
	header->tankData = malloc(0);
}

void variant_push(TankHeader* header, uint8_t* index, char* str)
{
	const int STR_LEN = strlen(str);
	int SIZE_TO_ADD = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int) + STR_LEN;

	if (header->tankDataSize > 0) // -1 for every arg that is not the first cause we did a +1 to remove the bytes from malloc
		header->tankDataSize -= 1;

	uint8_t currentIndex = (*index)++;
	uint8_t type = 0x2;
	header->tankData = realloc(header->tankData, header->tankDataSize + SIZE_TO_ADD + 1);

	// add the necessary data
	memcpy(header->tankData, index, sizeof(uint8_t));
	memcpy(header->tankData + header->tankDataSize + sizeof(uint8_t), &currentIndex, sizeof(uint8_t));
	memcpy(header->tankData + header->tankDataSize + sizeof(uint16_t), &type, sizeof(uint8_t));
	memcpy(header->tankData + header->tankDataSize + sizeof(uint16_t) + sizeof(uint8_t), &STR_LEN, sizeof(int));
	memcpy(header->tankData + header->tankDataSize + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(int), str, STR_LEN);

	header->tankDataSize += SIZE_TO_ADD + 1;
}

#endif //C_VARIANT_H
