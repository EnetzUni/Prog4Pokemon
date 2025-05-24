#include <string.h>
#include <stdio.h>
#include "type.h"

const char* getTypeName(Type type) {
    if (type >= 0 && type < TYPE_COUNT) {
        return TypeNames[type];
    }
    return (const char*) NULL;
}

double effectiveness(Type attackType, Type defenseType1, Type defenseType2) {
    double damageMultiplier = 1.0;
    Type defenseTypes[2] = {defenseType1, defenseType2};

    for (int i = 0; i < 2; ++i) {
        Type def = defenseTypes[i];

        switch (attackType) {
            case ACERO:
                if (def == ACERO || def == AGUA || def == ELECTRICO || def == FUEGO) damageMultiplier *= 0.5;
                else if (def == HADA || def == HIELO || def == ROCA) damageMultiplier *= 2;
                break;
            case AGUA:
                if (def == AGUA || def == DRAGON || def == PLANTA) damageMultiplier *= 0.5;
                else if (def == FUEGO || def == ROCA || def == TIERRA) damageMultiplier *= 2;
                break;
            case BICHO:
                if (def == ACERO || def == FANTASMA || def == FUEGO || def == HADA || def == LUCHA || def == VENENO || def == VOLADOR) damageMultiplier *= 0.5;
                else if (def == PLANTA || def == PSIQUICO || def == SINIESTRO) damageMultiplier *= 2;
                break;
            case DRAGON:
                if (def == HADA) damageMultiplier *= 0;
                else if (def == ACERO) damageMultiplier *= 0.5;
                else if (def == DRAGON) damageMultiplier *= 2;
                break;
            case ELECTRICO:
                if (def == TIERRA) damageMultiplier *= 0;
                else if (def == DRAGON || def == ELECTRICO || def == PLANTA) damageMultiplier *= 0.5;
                else if (def == AGUA || def == VOLADOR) damageMultiplier *= 2;
                break;
            case FANTASMA:
                if (def == NORMAL) damageMultiplier *= 0;
                else if (def == SINIESTRO) damageMultiplier *= 0.5;
                else if (def == FANTASMA || def == PSIQUICO) damageMultiplier *= 2;
                break;
            case FUEGO:
                if (def == AGUA || def == DRAGON || def == FUEGO || def == ROCA) damageMultiplier *= 0.5;
                else if (def == ACERO || def == BICHO || def == HIELO || def == PLANTA) damageMultiplier *= 2;
                break;
            case HADA:
                if (def == ACERO || def == FUEGO || def == VENENO) damageMultiplier *= 0.5;
                else if (def == DRAGON || def == LUCHA || def == SINIESTRO) damageMultiplier *= 2;
                break;
            case HIELO:
                if (def == ACERO || def == AGUA || def == FUEGO || def == HIELO) damageMultiplier *= 0.5;
                else if (def == DRAGON || def == PLANTA || def == TIERRA || def == VOLADOR) damageMultiplier *= 2;
                break;
            case LUCHA:
                if (def == FANTASMA) damageMultiplier *= 0;
                else if (def == BICHO || def == HADA || def == PSIQUICO || def == VENENO || def == VOLADOR) damageMultiplier *= 0.5;
                else if (def == ACERO || def == HIELO || def == NORMAL || def == ROCA || def == SINIESTRO) damageMultiplier *= 2;
                break;
            case NORMAL:
                if (def == FANTASMA) damageMultiplier *= 0;
                else if (def == ACERO || def == ROCA) damageMultiplier *= 0.5;
                break;
            case PLANTA:
                if (def == ACERO || def == BICHO || def == DRAGON || def == FUEGO || def == PLANTA || def == VENENO || def == VOLADOR) damageMultiplier *= 0.5;
                else if (def == AGUA || def == ROCA || def == TIERRA) damageMultiplier *= 2;
                break;
            case PSIQUICO:
                if (def == SINIESTRO) damageMultiplier *= 0;
                else if (def == ACERO || def == PSIQUICO) damageMultiplier *= 0.5;
                else if (def == LUCHA || def == VENENO) damageMultiplier *= 2;
                break;
            case ROCA:
                if (def == ACERO || def == LUCHA || def == TIERRA) damageMultiplier *= 0.5;
                else if (def == BICHO || def == FUEGO || def == HIELO || def == VOLADOR) damageMultiplier *= 2;
                break;
            case SINIESTRO:
                if (def == HADA || def == LUCHA || def == SINIESTRO) damageMultiplier *= 0.5;
                else if (def == FANTASMA || def == PSIQUICO) damageMultiplier *= 2;
                break;
            case TIERRA:
                if (def == VOLADOR) damageMultiplier *= 0;
                else if (def == BICHO || def == PLANTA) damageMultiplier *= 0.5;
                else if (def == ACERO || def == ELECTRICO || def == FUEGO || def == ROCA || def == VENENO) damageMultiplier *= 2;
                break;
            case VENENO:
                if (def == ACERO) damageMultiplier *= 0;
                else if (def == FANTASMA || def == ROCA || def == TIERRA || def == VENENO) damageMultiplier *= 0.5;
                else if (def == HADA || def == PLANTA) damageMultiplier *= 2;
                break;
            case VOLADOR:
                if (def == ACERO || def == ELECTRICO || def == ROCA) damageMultiplier *= 0.5;
                else if (def == BICHO || def == LUCHA || def == PLANTA) damageMultiplier *= 2;
                break;
        }
    }

    return damageMultiplier;
}