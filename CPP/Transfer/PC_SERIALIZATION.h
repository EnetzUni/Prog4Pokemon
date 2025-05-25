#ifndef PC_SERIALIZATION_H
#define PC_SERIALIZATION_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pc.h"
#include "pokemon.h"

// Forward declarations
size_t size_pokemon_player(PokemonPlayer* p);
void serialize_pokemon_player(uint8_t** buffer, PokemonPlayer* p);
void deserialize_pokemon_player(const uint8_t** buffer, PokemonPlayer* p);

static inline void write_bytes(uint8_t** buf, const void* data, size_t len) {
    memcpy(*buf, data, len);
    *buf += len;
}

static inline void read_bytes(const uint8_t** buf, void* data, size_t len) {
    memcpy(data, *buf, len);
    *buf += len;
}

static inline void serialize_pc(uint8_t** buffer, PC* pc) {
    // Serialize nickname
    uint32_t nick_len = (uint32_t)strnlen(pc->nickname, 255);
    write_bytes(buffer, &nick_len, sizeof(uint32_t));
    write_bytes(buffer, pc->nickname, nick_len);

    // Serialize pcListSize
    write_bytes(buffer, &pc->pcListSize, sizeof(int));

    // Serialize each PokemonPlayer in pcList
    for (int i = 0; i < pc->pcListSize; i++) {
        serialize_pokemon_player(buffer, pc->pcList[i]);
    }
}

static inline void deserialize_pc(const uint8_t** buffer, PC* pc) {
    uint32_t nick_len;
    read_bytes(buffer, &nick_len, sizeof(uint32_t));
    memcpy(pc->nickname, *buffer, nick_len);
    pc->nickname[nick_len] = '\0';
    *buffer += nick_len;

    read_bytes(buffer, &pc->pcListSize, sizeof(int));

    pc->pcList = (PokemonPlayer**)malloc(sizeof(PokemonPlayer*) * pc->pcListSize);
    for (int i = 0; i < pc->pcListSize; i++) {
        pc->pcList[i] = (PokemonPlayer*)malloc(sizeof(PokemonPlayer));
        deserialize_pokemon_player(buffer, pc->pcList[i]);
    }
}

static inline size_t size_pc(PC* pc) {
    size_t size = 0;

    size += sizeof(uint32_t); // nickname length
    size += strnlen(pc->nickname, 255);

    size += sizeof(int); // pcListSize

    for (int i = 0; i < pc->pcListSize; i++) {
        size += size_pokemon_player(pc->pcList[i]);
    }

    return size;
}

#endif // PC_SERIALIZATION_H
