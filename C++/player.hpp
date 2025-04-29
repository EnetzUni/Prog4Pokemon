#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <iostream>
#include <vector>
#include "pokemon.hpp"
#include "pc.hpp"
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

        /// Maximum level of Pokemon that the player can encounter.
        int maxLvL;
    };

#endif