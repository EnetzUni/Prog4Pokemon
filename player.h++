#pragma once

#include <iostream>
#include <vector>
#include "pokemon.h++"
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
    
        /// A list of the Pokemon in the Player's team.
        vector<Pokemon> listPokemon;
    };