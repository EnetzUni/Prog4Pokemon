// server.c
#include <stdio.h>
#include <winsock2.h>
#include "send_receive_structs.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 12345

int main() {
    WSADATA wsa;
    SOCKET server_sock, client_sock;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);

    printf("[Server] Initializing Winsock...\n");
    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_sock, (struct sockaddr*)&server, sizeof(server));
    listen(server_sock, 1);

    printf("[Server] Waiting for client connection...\n");
    client_sock = accept(server_sock, (struct sockaddr*)&client, &client_len);
    printf("[Server] Client connected!\n");

    Player receivedPlayer;
    if (recv_player(client_sock, &receivedPlayer) == 0) {
        printf("[Server] Received Player:\n");
        printPlayer(&receivedPlayer); // Assumes you implemented printPlayer
    } else {
        printf("[Server] Failed to receive player.\n");
    }

    closesocket(client_sock);
    closesocket(server_sock);
    WSACleanup();

    return 0;
}
