#ifndef POKEMON_PLAYER_BATTLE_SERIALIZATION_H
#define POKEMON_PLAYER_BATTLE_SERIALIZATION_H

#include <stdint.h>
#include "pokemon.h"
#include <cstring>

// Helper functions
static inline void write_bytes(uint8_t** buf, const void* data, size_t len) {
    memcpy(*buf, data, len);
    *buf += len;
}

static inline void read_bytes(const uint8_t** buf, void* data, size_t len) {
    memcpy(data, *buf, len);
    *buf += len;
}

static inline size_t size_pokemon_player_battle(PokemonPlayerBattle* p) {
    return sizeof(PokemonPlayer*)  // pointer - do NOT send pointer! Instead, serialize contents separately or remove pointer from this struct for network serialization.
         + sizeof(int)*7;          // lvl, battleHp, battleAttack, battleDefense, battleSpattack, battleSpdefense, battleSpeed
}

// Because PokemonPlayerBattle contains a pointer, you need to serialize pointed struct fully or redesign.
// Here's an example serializing just the stats and NOT the pointer:

static inline void serialize_pokemon_player_battle(uint8_t** buffer, PokemonPlayerBattle* p) {
    // You probably want to serialize the contained PokemonPlayer fully or by reference.
    // Here, just serialize the int fields:
    write_bytes(buffer, &p->lvl, sizeof(int));
    write_bytes(buffer, &p->battleHp, sizeof(int));
    write_bytes(buffer, &p->battleAttack, sizeof(int));
    write_bytes(buffer, &p->battleDefense, sizeof(int));
    write_bytes(buffer, &p->battleSpattack, sizeof(int));
    write_bytes(buffer, &p->battleSpdefense, sizeof(int));
    write_bytes(buffer, &p->battleSpeed, sizeof(int));
}

static inline void deserialize_pokemon_player_battle(const uint8_t** buffer, PokemonPlayerBattle* p) {
    read_bytes(buffer, &p->lvl, sizeof(int));
    read_bytes(buffer, &p->battleHp, sizeof(int));
    read_bytes(buffer, &p->battleAttack, sizeof(int));
    read_bytes(buffer, &p->battleDefense, sizeof(int));
    read_bytes(buffer, &p->battleSpattack, sizeof(int));
    read_bytes(buffer, &p->battleSpdefense, sizeof(int));
    read_bytes(buffer, &p->battleSpeed, sizeof(int));
}

#endif // POKEMON_PLAYER_BATTLE_SERIALIZATION_H
