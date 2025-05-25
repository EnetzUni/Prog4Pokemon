// client.cpp
#include <iostream>
#include <winsock2.h>
extern "C" {
    #include "send_receive_structs.h"
    #include "player.h"
}

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 12345

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    std::cout << "[Client] Initializing Winsock..." << std::endl;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    std::cout << "[Client] Connecting to server..." << std::endl;
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        closesocket(sock);
        return 1;
    }

    std::cout << "[Client] Connected!" << std::endl;

    // Create a sample player
    Player p = {
        .nickname = "Ash",
        .password = "pikachu",
        .gender = true,
        .listPokemon = nullptr,
        .listPokemonSize = 0,
        .maxLvL = 10,
        .story = 1
    };

    if (send_player(sock, &p) == 0) {
        std::cout << "[Client] Sent player successfully." << std::endl;
    } else {
        std::cerr << "[Client] Failed to send player." << std::endl;
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}
