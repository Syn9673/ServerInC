#include <stdio.h>
#include "src/utils.h"
#include "src/GamePacket.h"
#include "lib/enet/enet.h"

ENetHost* server;

int main()
{
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 17091;

	if (enet_initialize()) {
		printf("ENet failed to initialize.");
		return 0;
	} else {
		// ENet initialized
		server = enet_host_create(
			&address,
			1024,
			2,
			0,
			0
		);

		server->checksum = enet_crc32;
		enet_host_compress_with_range_coder(server);

		ENetEvent event;
		while (1) {
			while(enet_host_service(server, &event, 0) > 0) {
				switch(event.type) {
					case ENET_EVENT_TYPE_CONNECT: {
						TextPacket textPacket = { 0x3, "action|log\nmsg|Hello World." };

						unsigned char* buffer;
						int size = text_packet_to_bytes(&buffer, &textPacket);

						ENetPacket* packet = enet_packet_create(
							buffer,
							size,
							ENET_PACKET_FLAG_RELIABLE
						);

						enet_peer_send(
							event.peer,
							0,
							packet
						);

						// free the buffer to avoid mem leaks
						destroy_packet(&buffer);
						break;
					}
				}
			}
		}
	}
}