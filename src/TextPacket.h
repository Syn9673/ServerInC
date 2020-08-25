//
// Created by alexander on 8/24/2020.
//

#ifndef C_TEXTPACKET_H
#define C_TEXTPACKET_H

#include <string.h>
#include <stdlib.h>

typedef struct
{
	int type;
	char* data;
} TextPacket;

int text_packet_to_bytes(unsigned char** buffer, const TextPacket* packet)
{
	int size = sizeof(int) + strlen(packet->data) + 1;
	*buffer = malloc(size);

	memcpy(*buffer, &packet->type, sizeof(int));
	memcpy((*buffer) + 4, packet->data, strlen(packet->data) + 1);

	return size;
}

void to_text_packet(TextPacket* packet, const unsigned char* buffer)
{
	memcpy(&packet->type, buffer, sizeof(int));
	packet->data = malloc(strlen(buffer + 4) + 1);

	memcpy(packet->data, buffer + 4, strlen(buffer + 4) + 1);
}

void destroy_text_packet(TextPacket* packet)
{
	free(packet->data);
}

void destroy_packet(unsigned char** buffer)
{
	free(*buffer);
}

#endif //C_TEXTPACKET_H
