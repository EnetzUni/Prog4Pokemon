#ifndef TYPE_H
#define TYPE_H

/**
 * @enum Type
 * @brief Represents the elemental type of a Pokemon or its move.
 */
typedef enum {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY
} Type;

static const char* const TypeNames[] = {
    [NORMAL]   = "NORMAL",
    [FIRE]     = "FIRE",
    [WATER]    = "WATER",
    [ELECTRIC] = "ELECTRIC",
    [GRASS]    = "GRASS",
    [ICE]      = "ICE",
    [FIGHTING] = "FIGHTING",
    [POISON]   = "POISON",
    [GROUND]   = "GROUND",
    [FLYING]   = "FLYING",
    [PSYCHIC]  = "PSYCHIC",
    [BUG]      = "BUG",
    [ROCK]     = "ROCK",
    [GHOST]    = "GHOST",
    [DRAGON]   = "DRAGON",
    [DARK]     = "DARK",
    [STEEL]    = "STEEL",
    [FAIRY]    = "FAIRY"
};

#endif