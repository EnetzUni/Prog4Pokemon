#ifndef PLAYER_SERIALIZATION_H
#define PLAYER_SERIALIZATION_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "player.h"
#include "pokemon.h"
#include <cstdlib>

// Forward declarations for PokemonPlayer serialization
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

// Serialize Player
static inline void serialize_player(uint8_t** buffer, Player* p) {
    uint32_t nick_len = (uint32_t)strnlen(p->nickname, 255);
    write_bytes(buffer, &nick_len, sizeof(uint32_t));
    write_bytes(buffer, p->nickname, nick_len);

    uint32_t pass_len = (uint32_t)strnlen(p->password, 255);
    write_bytes(buffer, &pass_len, sizeof(uint32_t));
    write_bytes(buffer, p->password, pass_len);

    write_bytes(buffer, &p->gender, sizeof(bool));

    // Write listPokemonSize
    write_bytes(buffer, &p->listPokemonSize, sizeof(int));

    // Serialize each PokemonPlayer in list
    for (int i = 0; i < p->listPokemonSize; i++) {
        serialize_pokemon_player(buffer, p->listPokemon[i]);
    }

    write_bytes(buffer, &p->maxLvL, sizeof(int));
    write_bytes(buffer, &p->story, sizeof(int));
}

// Deserialize Player
static inline void deserialize_player(const uint8_t** buffer, Player* p) {
    uint32_t nick_len;
    read_bytes(buffer, &nick_len, sizeof(uint32_t));
    memcpy(p->nickname, *buffer, nick_len);
    p->nickname[nick_len] = '\0';
    *buffer += nick_len;

    uint32_t pass_len;
    read_bytes(buffer, &pass_len, sizeof(uint32_t));
    memcpy(p->password, *buffer, pass_len);
    p->password[pass_len] = '\0';
    *buffer += pass_len;

    read_bytes(buffer, &p->gender, sizeof(bool));

    read_bytes(buffer, &p->listPokemonSize, sizeof(int));
    p->listPokemon = (PokemonPlayer**)malloc(sizeof(PokemonPlayer*) * p->listPokemonSize);
    for (int i = 0; i < p->listPokemonSize; i++) {
        p->listPokemon[i] = (PokemonPlayer*)malloc(sizeof(PokemonPlayer));
        deserialize_pokemon_player(buffer, p->listPokemon[i]);
    }

    read_bytes(buffer, &p->maxLvL, sizeof(int));
    read_bytes(buffer, &p->story, sizeof(int));
}

// Calculate Player size for serialization
static inline size_t size_player(Player* p) {
    size_t size = 0;
    size += sizeof(uint32_t) + strnlen(p->nickname, 255);
    size += sizeof(uint32_t) + strnlen(p->password, 255);
    size += sizeof(bool);
    size += sizeof(int); // listPokemonSize
    for (int i = 0; i < p->listPokemonSize; i++) {
        size += size_pokemon_player(p->listPokemon[i]);
    }
    size += sizeof(int); // maxLvL
    size += sizeof(int); // story
    return size;
}

#endif // PLAYER_SERIALIZATION_H
