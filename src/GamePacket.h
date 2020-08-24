//
// Created by alexander on 8/24/2020.
//

#ifndef C_GAMEPACKET_H
#define C_GAMEPACKET_H

typedef struct {
	int type;
	char* text;
} TextPacket;

int text_packet_to_bytes(unsigned char** buffer, const TextPacket* packet)
{
	int size = sizeof(int) + strlen(packet->text) + 1;
	*buffer = malloc(size);

	memcpy(*buffer, &packet->type, sizeof(int));
	memcpy((*buffer) + 4, packet->text, strlen(packet->text) + 1);

	return size;
}

void to_text_packet(TextPacket* packet, const unsigned char* buffer)
{
	memcpy(&packet->type, buffer, sizeof(int));
	packet->text = malloc(strlen(buffer + 4) + 1);

	memcpy(packet->text, buffer + 4, strlen(buffer + 4) + 1);
}

void destroy_text_packet(TextPacket* packet)
{
	free(packet->text);
	packet->text = NULL;
}

void destroy_packet(unsigned char** buffer)
{
	free(*buffer);
	*buffer = NULL;
}

#endif //C_GAMEPACKET_H
