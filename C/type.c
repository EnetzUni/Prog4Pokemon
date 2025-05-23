#include "type.h"
#include "pokemon.h"

#include <stdio.h>
#include <string.h>

double efectividad(int TipoAtaqueint, int TipoDefensa1, int TipoDefensa2) {
    // Define the type names.
    char* Tipos[18] = {
        "Acero", "Agua", "Bicho", "Dragon", "Eléctrico", "Fantasma", "Fuego", "Hada",
        "Hielo", "Lucha", "Normal", "Planta", "Psíquico", "Roca", "Siniestro", "Tierra",
        "Veneno", "Volador"
    };

    char* TipoAtaque = Tipos[TipoAtaqueint]

    // Array of defense types.
    char* TiposEvaluados[2] = {Tipos[TipoDefensa1], Tipos[TipoDefensa2]};
    double Resultado = 1.0;

    // Evaluate both defense types.
    for (int j = 0; j < 2; j++) {
        char* Evaluacion = TiposEvaluados[j];

        // TipoAtaque == "Acero"
        if (strcmp(TipoAtaque, Tipos[0]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[1]) == 0 ||
                strcmp(Evaluacion, Tipos[4]) == 0 ||
                strcmp(Evaluacion, Tipos[6]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[7]) == 0 ||
                       strcmp(Evaluacion, Tipos[8]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Agua"
        if (strcmp(TipoAtaque, Tipos[1]) == 0) {
            if (strcmp(Evaluacion, Tipos[1]) == 0 ||
                strcmp(Evaluacion, Tipos[3]) == 0 ||
                strcmp(Evaluacion, Tipos[11]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[6]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0 ||
                       strcmp(Evaluacion, Tipos[15]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Bicho"
        if (strcmp(TipoAtaque, Tipos[2]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[5]) == 0 ||
                strcmp(Evaluacion, Tipos[6]) == 0 ||
                strcmp(Evaluacion, Tipos[7]) == 0 ||
                strcmp(Evaluacion, Tipos[9]) == 0 ||
                strcmp(Evaluacion, Tipos[16]) == 0 ||
                strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[11]) == 0 ||
                       strcmp(Evaluacion, Tipos[12]) == 0 ||
                       strcmp(Evaluacion, Tipos[14]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Dragon"
        if (strcmp(TipoAtaque, Tipos[3]) == 0) {
            if (strcmp(Evaluacion, Tipos[7]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[0]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[3]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Eléctrico"
        if (strcmp(TipoAtaque, Tipos[4]) == 0) {
            if (strcmp(Evaluacion, Tipos[15]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[3]) == 0 ||
                       strcmp(Evaluacion, Tipos[4]) == 0 ||
                       strcmp(Evaluacion, Tipos[11]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[1]) == 0 ||
                       strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Fantasma"
        if (strcmp(TipoAtaque, Tipos[5]) == 0) {
            if (strcmp(Evaluacion, Tipos[10]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[14]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[5]) == 0 ||
                       strcmp(Evaluacion, Tipos[12]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Fuego"
        if (strcmp(TipoAtaque, Tipos[6]) == 0) {
            if (strcmp(Evaluacion, Tipos[1]) == 0 ||
                strcmp(Evaluacion, Tipos[3]) == 0 ||
                strcmp(Evaluacion, Tipos[6]) == 0 ||
                strcmp(Evaluacion, Tipos[13]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                       strcmp(Evaluacion, Tipos[2]) == 0 ||
                       strcmp(Evaluacion, Tipos[8]) == 0 ||
                       strcmp(Evaluacion, Tipos[11]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Hada"
        if (strcmp(TipoAtaque, Tipos[7]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[6]) == 0 ||
                strcmp(Evaluacion, Tipos[16]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[3]) == 0 ||
                       strcmp(Evaluacion, Tipos[9]) == 0 ||
                       strcmp(Evaluacion, Tipos[14]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Hielo"
        if (strcmp(TipoAtaque, Tipos[8]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[1]) == 0 ||
                strcmp(Evaluacion, Tipos[6]) == 0 ||
                strcmp(Evaluacion, Tipos[8]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[3]) == 0 ||
                       strcmp(Evaluacion, Tipos[11]) == 0 ||
                       strcmp(Evaluacion, Tipos[15]) == 0 ||
                       strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Lucha"
        if (strcmp(TipoAtaque, Tipos[9]) == 0) {
            if (strcmp(Evaluacion, Tipos[5]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[2]) == 0 ||
                       strcmp(Evaluacion, Tipos[7]) == 0 ||
                       strcmp(Evaluacion, Tipos[12]) == 0 ||
                       strcmp(Evaluacion, Tipos[16]) == 0 ||
                       strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                       strcmp(Evaluacion, Tipos[8]) == 0 ||
                       strcmp(Evaluacion, Tipos[10]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0 ||
                       strcmp(Evaluacion, Tipos[14]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Normal"
        if (strcmp(TipoAtaque, Tipos[10]) == 0) {
            if (strcmp(Evaluacion, Tipos[5]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0) {
                Resultado *= 0.5;
            }
        }

        // TipoAtaque == "Planta"
        if (strcmp(TipoAtaque, Tipos[11]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[2]) == 0 ||
                strcmp(Evaluacion, Tipos[3]) == 0 ||
                strcmp(Evaluacion, Tipos[6]) == 0 ||
                strcmp(Evaluacion, Tipos[11]) == 0 ||
                strcmp(Evaluacion, Tipos[16]) == 0 ||
                strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[1]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0 ||
                       strcmp(Evaluacion, Tipos[15]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Psíquico"
        if (strcmp(TipoAtaque, Tipos[12]) == 0) {
            if (strcmp(Evaluacion, Tipos[14]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                       strcmp(Evaluacion, Tipos[12]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[9]) == 0 ||
                       strcmp(Evaluacion, Tipos[16]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Roca"
        if (strcmp(TipoAtaque, Tipos[13]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[9]) == 0 ||
                strcmp(Evaluacion, Tipos[15]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[2]) == 0 ||
                       strcmp(Evaluacion, Tipos[6]) == 0 ||
                       strcmp(Evaluacion, Tipos[8]) == 0 ||
                       strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Siniestro"
        if (strcmp(TipoAtaque, Tipos[14]) == 0) {
            if (strcmp(Evaluacion, Tipos[7]) == 0 ||
                strcmp(Evaluacion, Tipos[9]) == 0 ||
                strcmp(Evaluacion, Tipos[14]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[5]) == 0 ||
                       strcmp(Evaluacion, Tipos[12]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Tierra"
        if (strcmp(TipoAtaque, Tipos[15]) == 0) {
            if (strcmp(Evaluacion, Tipos[17]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[2]) == 0 ||
                       strcmp(Evaluacion, Tipos[11]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                       strcmp(Evaluacion, Tipos[4]) == 0 ||
                       strcmp(Evaluacion, Tipos[6]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0 ||
                       strcmp(Evaluacion, Tipos[16]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Veneno"
        if (strcmp(TipoAtaque, Tipos[16]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0) {
                Resultado *= 0;
            } else if (strcmp(Evaluacion, Tipos[5]) == 0 ||
                       strcmp(Evaluacion, Tipos[13]) == 0 ||
                       strcmp(Evaluacion, Tipos[15]) == 0 ||
                       strcmp(Evaluacion, Tipos[16]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[7]) == 0 ||
                       strcmp(Evaluacion, Tipos[11]) == 0) {
                Resultado *= 2;
            }
        }

        // TipoAtaque == "Volador"
        if (strcmp(TipoAtaque, Tipos[17]) == 0) {
            if (strcmp(Evaluacion, Tipos[0]) == 0 ||
                strcmp(Evaluacion, Tipos[4]) == 0 ||
                strcmp(Evaluacion, Tipos[13]) == 0) {
                Resultado *= 0.5;
            } else if (strcmp(Evaluacion, Tipos[2]) == 0 ||
                       strcmp(Evaluacion, Tipos[9]) == 0 ||
                       strcmp(Evaluacion, Tipos[11]) == 0) {
                Resultado *= 2;
            }
        }
    }
    return Resultado;
}

int calculatedamage(Pokemon pokemonataque, Pokemon pokemondefensa, Movimiento movimientousado) {
    int damage = 0;

    if (movimientousado.categoriaMovimiento == 1) {
        if (pokemonataque.type1 == movimientousado.type || pokemonataque.type2 == movimientousado.type) {
            damage = (((((2 * pokemonataque.nivel) / 5) * movimientousado.potencia * (pokemonataque.ataque / pokemondefensa.defensa)) / 50) + 2) * 1.5 * efectividad(movimientousado.tipo, pokemondefensa.type1, pokemondefensa.type2)
        } else {
            damage = (((((2 * pokemonataque.nivel) / 5) * movimientousado.potencia * (pokemonataque.ataque / pokemondefensa.defensa)) / 50) + 2) * efectividad(movimientousado.tipo, pokemondefensa.type1, pokemondefensa.type2)
        }
    } else if (movimientousado.categoriaMovimiento == 2) {
        if (pokemonataque.type1 == movimientousado.type || pokemonataque.type2 == movimientousado.type) {
            damage = (((((2 * pokemonataque.nivel) / 5) * movimientousado.potencia * (pokemonataque.ataqueespecial / pokemondefensa.defensaespecial)) / 50) + 2) * 1.5 * efectividad(movimientousado.tipo, pokemondefensa.type1, pokemondefensa.type2)
        } else {
            damage = (((((2 * pokemonataque.nivel) / 5) * movimientousado.potencia * (pokemonataque.ataqueespecial / pokemondefensa.defensaespecial)) / 50) + 2) * efectividad(movimientousado.tipo, pokemondefensa.type1, pokemondefensa.type2)
        }
    } else {;}

    return damage;
}