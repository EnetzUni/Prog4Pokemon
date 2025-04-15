#ifndef PC_HPP
#define PC_HPP

#pragma once

#include <iostream>
#include <vector>
#include "pokemon.hpp"
using namespace std;

/**
 * @class Pc
 * @brief Represents the rest of the Pokemon stored by a player that are not on his current team
 */
class Pc {
    public:
        /// List of the Pokemon stored in the Pc.
        vector<PokemonPlayer> listPokemon;
    };

#endif