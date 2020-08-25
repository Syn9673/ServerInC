
#include <stdio.h>
#include "src/Utils.h"
#include "lib/enet/enet.h"
#include "./src/TankPacket.h"
#include "./src/Variant.h"

ENetHost* server;

int main()
{
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 17091;

	if (enet_initialize())
	{
		printf("ENet failed to initialize.");
		return 0;
	}

	server = enet_host_create(
			&address,
			1024,
			2,
			0,
			0
	);

	server->checksum = enet_crc32;
	enet_host_compress_with_range_coder(server);

	printf("ENet Server Finished setting up at port %i\n", address.port);

	while (1)
	{
		ENetEvent event;
		while (enet_host_service(server, &event, 0) > 0)
		{
			switch (event.type)
			{
				case ENET_EVENT_TYPE_CONNECT:
				{
					printf("User connected, connectID: %i\n", (uint32_t) event.peer->connectID);

					TankHeader header = { 0x4, 0x1, -1, 0x0, 0x8 };
					uint8_t index = 0;

					variant_init(&header);
					variant_push(&header, &index, "OnConsoleMessage");
					variant_push(&header, &index, "Hello World.");

					unsigned char* tank;
					int size = tankheader_parse(&tank, &header);

					ENetPacket* packet = enet_packet_create(
						tank,
						size,
						ENET_PACKET_FLAG_RELIABLE
					);

					enet_peer_send(
						event.peer,
						0,
						packet
					);

					free(tank);
					free(header.tankData);
					break;
				}
			}
		}
	}
}