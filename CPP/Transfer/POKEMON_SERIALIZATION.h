#ifndef POKEMON_SERIALIZATION_H
#define POKEMON_SERIALIZATION_H

#include <stdint.h>
#include <string.h>
#include "pokemon.h"
#include "movement.h"
#include <cstdlib>

// Forward declarations for Movement serialization
size_t size_movement(Movement* m);
void serialize_movement(uint8_t** buffer, Movement* m);
void deserialize_movement(const uint8_t** buffer, Movement* m);

static inline void write_bytes(uint8_t** buf, const void* data, size_t len) {
    memcpy(*buf, data, len);
    *buf += len;
}

static inline void read_bytes(const uint8_t** buf, void* data, size_t len) {
    memcpy(data, *buf, len);
    *buf += len;
}

// Serialize Pokemon
static inline void serialize_pokemon(uint8_t** buffer, Pokemon* p) {
    write_bytes(buffer, &p->id, sizeof(int));

    uint32_t name_len = (uint32_t)strnlen(p->name, 255);
    write_bytes(buffer, &name_len, sizeof(uint32_t));
    write_bytes(buffer, p->name, name_len);

    write_bytes(buffer, &p->hp, sizeof(int));
    write_bytes(buffer, &p->attack, sizeof(int));
    write_bytes(buffer, &p->defense, sizeof(int));
    write_bytes(buffer, &p->spattack, sizeof(int));
    write_bytes(buffer, &p->spdefense, sizeof(int));
    write_bytes(buffer, &p->speed, sizeof(int));

    // Serialize types (2)
    write_bytes(buffer, &p->type[0], sizeof(Type));
    write_bytes(buffer, &p->type[1], sizeof(Type));

    write_bytes(buffer, &p->evolvl, sizeof(int));
}

// Deserialize Pokemon
static inline void deserialize_pokemon(const uint8_t** buffer, Pokemon* p) {
    read_bytes(buffer, &p->id, sizeof(int));

    uint32_t name_len;
    read_bytes(buffer, &name_len, sizeof(uint32_t));
    memcpy(p->name, *buffer, name_len);
    p->name[name_len] = '\0';
    *buffer += name_len;

    read_bytes(buffer, &p->hp, sizeof(int));
    read_bytes(buffer, &p->attack, sizeof(int));
    read_bytes(buffer, &p->defense, sizeof(int));
    read_bytes(buffer, &p->spattack, sizeof(int));
    read_bytes(buffer, &p->spdefense, sizeof(int));
    read_bytes(buffer, &p->speed, sizeof(int));

    read_bytes(buffer, &p->type[0], sizeof(Type));
    read_bytes(buffer, &p->type[1], sizeof(Type));

    read_bytes(buffer, &p->evolvl, sizeof(int));
}

// Calculate Pokemon size
static inline size_t size_pokemon(Pokemon* p) {
    return sizeof(int)                              // id
         + sizeof(uint32_t) + strnlen(p->name, 255) // name
         + sizeof(int)*6                            // hp, attack, defense, spattack, spdefense, speed
         + sizeof(Type)*2                           // type[2]
         + sizeof(int);                             // evolvl
}

// -------------------- PokemonPlayer --------------------

size_t size_pokemon_player(PokemonPlayer* p);
void serialize_pokemon_player(uint8_t** buffer, PokemonPlayer* p);
void deserialize_pokemon_player(const uint8_t** buffer, PokemonPlayer* p);

static inline size_t size_pokemon_player(PokemonPlayer* p) {
    size_t size = 0;
    size += sizeof(int); // pokeid

    size += sizeof(uint32_t) + strnlen(p->nickname, 255);

    size += sizeof(int); // listMovementSize

    for (int i = 0; i < p->listMovementSize; i++) {
        size += size_movement(p->listMovement[i]);
    }

    size += sizeof(int); // xp
    size += sizeof(int); // curHp
    size += sizeof(Status); // status

    size += size_pokemon(p->pokemon);

    return size;
}

static inline void serialize_pokemon_player(uint8_t** buffer, PokemonPlayer* p) {
    write_bytes(buffer, &p->pokeid, sizeof(int));

    uint32_t nick_len = (uint32_t)strnlen(p->nickname, 255);
    write_bytes(buffer, &nick_len, sizeof(uint32_t));
    write_bytes(buffer, p->nickname, nick_len);

    write_bytes(buffer, &p->listMovementSize, sizeof(int));
    for (int i = 0; i < p->listMovementSize; i++) {
        serialize_movement(buffer, p->listMovement[i]);
    }

    write_bytes(buffer, &p->xp, sizeof(int));
    write_bytes(buffer, &p->curHp, sizeof(int));
    write_bytes(buffer, &p->status, sizeof(Status));

    serialize_pokemon(buffer, p->pokemon);
}

static inline void deserialize_pokemon_player(const uint8_t** buffer, PokemonPlayer* p) {
    read_bytes(buffer, &p->pokeid, sizeof(int));

    uint32_t nick_len;
    read_bytes(buffer, &nick_len, sizeof(uint32_t));
    memcpy(p->nickname, *buffer, nick_len);
    p->nickname[nick_len] = '\0';
    *buffer += nick_len;

    read_bytes(buffer, &p->listMovementSize, sizeof(int));
    p->listMovement = (Movement**)malloc(sizeof(Movement*) * p->listMovementSize);
    for (int i = 0; i < p->listMovementSize; i++) {
        p->listMovement[i] = (Movement*)malloc(sizeof(Movement));
        deserialize_movement(buffer, p->listMovement[i]);
    }

    read_bytes(buffer, &p->xp, sizeof(int));
    read_bytes(buffer, &p->curHp, sizeof(int));
    read_bytes(buffer, &p->status, sizeof(Status));

    p->pokemon = (Pokemon*)malloc(sizeof(Pokemon));
    deserialize_pokemon(buffer, p->pokemon);
}

#endif // POKEMON_SERIALIZATION_H
