#ifndef SOCKET_HELPERS_H
#define SOCKET_HELPERS_H

#include <winsock2.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>  // for malloc, free

// Send all bytes in buffer over socket
// Returns true if all bytes sent, false on error
static inline bool send_all(SOCKET sock, const uint8_t* buffer, int length) {
    int total_sent = 0;
    while (total_sent < length) {
        int sent = send(sock, (const char*)(buffer + total_sent), length - total_sent, 0);
        if (sent == SOCKET_ERROR || sent == 0) {
            return false; // Error or connection closed
        }
        total_sent += sent;
    }
    return true;
}

// Receive all bytes requested over socket
// Returns true if all bytes received, false on error or disconnect
static inline bool recv_all(SOCKET sock, uint8_t* buffer, int length) {
    int total_received = 0;
    while (total_received < length) {
        int received = recv(sock, (char*)(buffer + total_received), length - total_received, 0);
        if (received == SOCKET_ERROR || received == 0) {
            return false; // Error or connection closed
        }
        total_received += received;
    }
    return true;
}

// Helper to send a serialized object with size prefix
static inline bool send_object(SOCKET sock, const uint8_t* buffer, int length) {
    // Send length prefix (4 bytes, network byte order)
    uint32_t net_len = htonl((uint32_t)length);
    if (!send_all(sock, (uint8_t*)&net_len, sizeof(net_len))) return false;

    // Send object bytes
    if (!send_all(sock, buffer, length)) return false;

    return true;
}

// Helper to receive a serialized object with size prefix
// Allocates *buffer_out, caller must free
static inline bool recv_object(SOCKET sock, uint8_t** buffer_out, int* length_out) {
    uint32_t net_len;
    if (!recv_all(sock, (uint8_t*)&net_len, sizeof(net_len))) return false;

    uint32_t length = ntohl(net_len);
    if (length == 0) return false;

    uint8_t* buffer = (uint8_t*)malloc(length);
    if (!buffer) return false;

    if (!recv_all(sock, buffer, length)) {
        free(buffer);
        return false;
    }

    *buffer_out = buffer;
    *length_out = (int)length;
    return true;
}

// Compatibility macros for send_receive_structs.h
#define send_message send_object
#define recv_message recv_object

#endif // SOCKET_HELPERS_H
