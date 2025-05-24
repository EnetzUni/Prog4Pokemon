#ifndef TYPE_H
#define TYPE_H

/**
 * @enum Type
 * @brief Represents the elemental type of a Pokemon or its move.
 */
typedef enum {
    ACERO, AGUA, BICHO, DRAGON, ELECTRICO, FANTASMA, FUEGO, HADA, HIELO, LUCHA, NORMAL, PLANTA, PSIQUICO, ROCA, SINIESTRO, TIERRA, VENENO, VOLADOR, TYPE_COUNT
} Type;

static const char* const TypeNames[] = {
    [ACERO]     = "ACERO",
    [AGUA]      = "AGUA",
    [BICHO]     = "BICHO",
    [DRAGON]    = "DRAGON",
    [ELECTRICO] = "ELECTRICO",
    [FANTASMA]  = "FANTASMA",
    [FUEGO]     = "FUEGO",
    [HADA]      = "HADA",
    [HIELO]     = "HIELO",
    [LUCHA]     = "LUCHA",
    [NORMAL]    = "NORMAL",
    [PLANTA]    = "PLANTA",
    [PSIQUICO]  = "PSIQUICO",
    [SINIESTRO] = "SINIESTRO",
    [DRAGON]    = "DRAGON",
    [TIERRA]    = "TIERRA",
    [VENENO]    = "VENENO",
    [VOLADOR]   = "VOLADOR"
};

const char* getTypeName(Type type);

double effectiveness(Type attackType, Type defenseType1, Type defenseType2);

#endif