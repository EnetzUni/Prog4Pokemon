#ifndef MOVEMENT_SERIALIZATION_H
#define MOVEMENT_SERIALIZATION_H

#include <stdint.h>
#include <string.h>
#include "movement.h"
#include "type.h"
#include "category.h"
#include "status.h"

// Helper to write data and advance pointer
static inline void write_bytes(uint8_t** buf, const void* data, size_t len) {
    memcpy(*buf, data, len);
    *buf += len;
}

static inline void read_bytes(const uint8_t** buf, void* data, size_t len) {
    memcpy(data, *buf, len);
    *buf += len;
}

// Serialize Movement
static inline void serialize_movement(uint8_t** buffer, Movement* m) {
    write_bytes(buffer, &m->id, sizeof(int));
    
    uint32_t name_len = (uint32_t)strnlen(m->name, 255);
    write_bytes(buffer, &name_len, sizeof(uint32_t));
    write_bytes(buffer, m->name, name_len);
    
    write_bytes(buffer, &m->type, sizeof(Type));
    write_bytes(buffer, &m->category, sizeof(Category));
    write_bytes(buffer, &m->status, sizeof(Status));
    write_bytes(buffer, &m->statusaccuracy, sizeof(int));
    write_bytes(buffer, &m->power, sizeof(int));
    write_bytes(buffer, &m->accuracy, sizeof(int));
}

// Deserialize Movement
static inline void deserialize_movement(const uint8_t** buffer, Movement* m) {
    read_bytes(buffer, &m->id, sizeof(int));
    
    uint32_t name_len;
    read_bytes(buffer, &name_len, sizeof(uint32_t));
    memcpy(m->name, *buffer, name_len);
    m->name[name_len] = '\0';
    *buffer += name_len;
    
    read_bytes(buffer, &m->type, sizeof(Type));
    read_bytes(buffer, &m->category, sizeof(Category));
    read_bytes(buffer, &m->status, sizeof(Status));
    read_bytes(buffer, &m->statusaccuracy, sizeof(int));
    read_bytes(buffer, &m->power, sizeof(int));
    read_bytes(buffer, &m->accuracy, sizeof(int));
}

// Calculate Movement size for serialization
static inline size_t size_movement(Movement* m) {
    return sizeof(int)                         // id
         + sizeof(uint32_t)                    // name length
         + strnlen(m->name, 255)               // name chars
         + sizeof(Type)                        // type enum
         + sizeof(Category)                    // category enum
         + sizeof(Status)                      // status enum
         + sizeof(int)                         // statusaccuracy
         + sizeof(int)                         // power
         + sizeof(int);                        // accuracy
}

#endif // MOVEMENT_SERIALIZATION_H
