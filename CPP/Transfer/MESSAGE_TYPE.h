// message_type.h
#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MSG_PLAYER = 1,
    MSG_PC = 2,
    MSG_POKEMON_PLAYER = 3,
    MSG_POKEMON_PLAYER_BATTLE = 4,
    MSG_MOVEMENT = 5
} MessageType;

#ifdef __cplusplus
}
#endif

#endif // MESSAGE_TYPE_H
