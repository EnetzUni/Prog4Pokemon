#pragma once

#include <iostream>
#include <vector>
#include "pokemon.h++"
#include "pc.h++"
using namespace std;

/**
 * @class Player
 * @brief Represents a player in the game, including personal information and their Pokemon team.
 */
class Player {
    public:
        /// The player's nickname.
        string nickname;
    
        /// The player's password.
        string password;
    
        /// The player's gender.
        bool gender;
    
        /// List of the Pokemon in the player's team.
        vector<PokemonPlayer> listPokemon;

        /// The Pc where the rest of the player's Pokemon are stored.
        Pc playerpc;
    };