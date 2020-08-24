//
// Created by alexander on 8/24/2020.
//

#ifndef C_VARIANT_H
#define C_VARIANT_H

#include "./src/TankPacket.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	VARIANT_FLOAT_1 = 0x1,
	VARIANT_STRING  = 0x2
} VariantArgTypes;

typedef struct
{
	uint8_t count;
	char* data;
	int size;
} Variant;

void variant_init(TankHeader* header, Variant* variant)
{
	header->tankDataSize = 1;
	header->tankData = malloc(0);

	variant->data = malloc(0);
}

void variant_insert(TankHeader* header, Variant* variant, char* str)
{
	// do some re-allocation
	const int SIZE_TO_ADD = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int) + strlen(str);
	variant->data = realloc(variant->data, variant->size + SIZE_TO_ADD + 1);

	uint8_t count = ++variant->count;
	uint8_t index = variant->count - 1;
	uint8_t type = VARIANT_STRING;
	int len = strlen(str);

	// change arg count
	memcpy(variant->data, &count, sizeof(uint8_t)); // offset 0
	memcpy(variant->data + variant->size + sizeof(uint8_t), &index, sizeof(uint8_t)); // offset 1
	memcpy(variant->data + variant->size + sizeof(uint16_t), &type, sizeof(uint8_t)); // offset 2
	memcpy(variant->data + variant->size + sizeof(uint16_t) + sizeof(uint8_t), &len, sizeof(int)); // offset 3
	memcpy(variant->data + variant->size + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(int), str, strlen(str));

	header->tankDataSize += SIZE_TO_ADD;
	variant->size += SIZE_TO_ADD;
}

#endif //C_VARIANT_H
