// send_receive_structs.h
#ifndef SEND_RECEIVE_STRUCTS_H
#define SEND_RECEIVE_STRUCTS_H

#include <winsock2.h>
#include <stdlib.h>
#include <stdint.h>
#include "socket_helpers.h"
#include "message_type.h"
#include "player.h"
#include "pc.h"
#include "pokemon.h"
#include "movement.h"

static inline int send_struct_with_type(SOCKET sock, MessageType type, uint8_t* buffer, int buffer_len) {
    // Prefix the message with a 4-byte type
    uint32_t total_len = buffer_len + sizeof(uint32_t);
    uint8_t* full_buffer = (uint8_t*)malloc(total_len);
    if (!full_buffer) return SOCKET_ERROR;

    uint32_t net_type = htonl((uint32_t)type);
    memcpy(full_buffer, &net_type, sizeof(net_type));
    memcpy(full_buffer + sizeof(net_type), buffer, buffer_len);

    int result = send_message(sock, full_buffer, total_len);
    free(full_buffer);
    return result;
}

static inline int recv_struct_with_type(SOCKET sock, MessageType* type_out, uint8_t** buffer, int* buffer_len) {
    uint8_t* full_buffer = NULL;
    int full_len = 0;

    if (recv_message(sock, &full_buffer, &full_len) == SOCKET_ERROR) return SOCKET_ERROR;
    if (full_len < sizeof(uint32_t)) {
        free(full_buffer);
        return SOCKET_ERROR;
    }

    uint32_t net_type;
    memcpy(&net_type, full_buffer, sizeof(net_type));
    *type_out = (MessageType)ntohl(net_type);

    int payload_len = full_len - sizeof(uint32_t);
    *buffer = (uint8_t*)malloc(payload_len);
    if (!*buffer) {
        free(full_buffer);
        return SOCKET_ERROR;
    }

    memcpy(*buffer, full_buffer + sizeof(uint32_t), payload_len);
    *buffer_len = payload_len;

    free(full_buffer);
    return 0;
}

// Macros to generate send/recv for each type
#define DEFINE_SEND_RECV_STRUCT(NAME, STRUCT_TYPE, ENUM_TYPE, SERIALIZE, DESERIALIZE, SIZE_FN) \
static inline int send_##NAME(SOCKET sock, STRUCT_TYPE* obj) { \
    int size = (int)SIZE_FN(obj); \
    uint8_t* buffer = (uint8_t*)malloc(size); \
    if (!buffer) return SOCKET_ERROR; \
    uint8_t* ptr = buffer; \
    SERIALIZE(&ptr, obj); \
    int res = send_struct_with_type(sock, ENUM_TYPE, buffer, size); \
    free(buffer); \
    return res; \
} \
static inline int recv_##NAME(SOCKET sock, STRUCT_TYPE* obj) { \
    MessageType msg_type; \
    uint8_t* buffer = NULL; \
    int size = 0; \
    if (recv_struct_with_type(sock, &msg_type, &buffer, &size) == SOCKET_ERROR || msg_type != ENUM_TYPE) return SOCKET_ERROR; \
    const uint8_t* ptr = buffer; \
    DESERIALIZE(&ptr, obj); \
    free(buffer); \
    return 0; \
}

// Now generate for all
DEFINE_SEND_RECV_STRUCT(player, Player, MSG_PLAYER, serialize_player, deserialize_player, size_player)
DEFINE_SEND_RECV_STRUCT(pc, PC, MSG_PC, serialize_pc, deserialize_pc, size_pc)
DEFINE_SEND_RECV_STRUCT(pokemon_player, PokemonPlayer, MSG_POKEMON_PLAYER, serialize_pokemon_player, deserialize_pokemon_player, size_pokemon_player)
DEFINE_SEND_RECV_STRUCT(pokemon_player_battle, PokemonPlayerBattle, MSG_POKEMON_PLAYER_BATTLE, serialize_pokemon_player_battle, deserialize_pokemon_player_battle, size_pokemon_player_battle)
DEFINE_SEND_RECV_STRUCT(movement, Movement, MSG_MOVEMENT, serialize_movement, deserialize_movement, size_movement)

#endif // SEND_RECEIVE_STRUCTS_H
