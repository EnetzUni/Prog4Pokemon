#ifndef POKEMON_HPP
#define POKEMON_HPP

#pragma once

#include <iostream>
#include <vector>
#include "type.h"
#include "movement.hpp"
using namespace std;

/** 
 * @class Pokemon
 * @brief This is the main Pokemon class, with base stats.
 */
class Pokemon {
    private:
        /// The Pokedex number for the Pokemon.
        int id;

        /// The name of the Pokemon.
        string name;

        /// The base hit points of the Pokemon.
        int hp;

        /// The base attack stat of the Pokemon.
        int attack;

        /// The base defense stat of the Pokemon.
        int defense;

        /// The base special attack stat of the Pokemon.
        int spattack;

        /// The base special defense stat of the Pokemon.
        int spdefense;

        /// The base speed stat of the Pokemon.
        int speed;

        /// The list of types of the Pokemon (1 or 2 types)
        vector<Type> type;

        /// The level at which the Pokemon evolves.
        int evolvl;

    public:
        int getId();
        string getName();
        int getHp();
        int getAttack();
        int getDefense();
        int getSpattack();
        int getSpdefense();
        int getSpeed();
        vector<Type> getType();
        int getEvolvl();
};

/** 
 * @class PokemonPlayer
 * @brief This pokemon class creates basically an instance of a pokemon, a pokemon that is specific for a player
 * @see Pokemon
 */
class PokemonPlayer : public Pokemon {
    private:
        /// The Pokemon's pokeid.
        int pokeid;

        /// The Pokemon's nickname.
        string nickname;

        /// The Pokemon's list of Movements.
        vector<Movement> listMovement;

        /// The Pokemon's level.
        int lvl;

        /// The Pokemon's exact amount of xp to calculate level.
        int xp;

        /// The hit points of the Pokemon according to their current level.
        int lvlhp;
        
        /// The attack stat of the Pokemon according to their current level.
        int lvlattack;

        /// The defense stat of the Pokemon according to their current level.
        int lvldefense;

        /// The special attack stat of the Pokemon according to their current level.
        int lvlspattack;

        /// The special defense stat of the Pokemon according to their current level.
        int lvlspdefense;

        /// The speed stat of the Pokemon according to their current level.
        int lvlspeed;

        /// The Pokemon's current hit points.
        int curHp;

        /// The Pokemon's current status
        Status status;

    public:
        string getNickname();
        void setNickname(string&);
        vector<Movement> getListMovement();
        void setListMovement(vector<Movement>&);
        int getLvl();
        void setLvl(int);
        int getXp();
        void setXp(int);
        int getLvlHp();
        void setLvlHp(int);
        int getLvlAttack();
        void setLvlAttack(int);
        int getLvlDefense();
        void setLvlDefense(int);
        int getLvlSpAttack();
        void setLvlSpAttack(int);
        int getLvlSpDefense();
        void setLvlSpDefense(int);
        int getLvlSpeed();
        void setLvlSpeed(int);
        int getCurHp();
        void setCurHp(int);
        Status getStatus();
        void setStatus(Status&);
};

/**
 * @brief Calculates level based on experience points.
 * 
 * @param xp The experience points accumulated by the player.
 * 
 * @return The level as an integer.
 */
int xpToLvl(int);

/**
 * @brief Updates the stats based on the new level.
 * 
 * @param pokemon The pokemon whose stats need to be updated.
 */
void updateStats(PokemonPlayer*);

/**
 * @brief Creates the desired pokemon.
 * 
 * @param id The id of the pokemon to be created.
 * 
 * @return The created pokemon.
 */
void createPokemon(int);

/**
 * @brief Creates the desired pokemon.
 * 
* This function can be called with different types for the Pokémon and movements:
 * - The first parameter can either be a Pokemon id (int) or a Pokemon object.
 * - The movements can either be a vector of Movement objects or a vector of movement IDs (int). 
 *
 * @param idORpokemon The pokemon or id of such Pokemon of the pokemonPlayer to be created.
 * @param pokeid The id of the pokemonPlayer to be created.
 * @param nickname The nickname of the pokemonPlayer to be created.
 * @param idsORmovements The movements or ids of such movements of the pokemonPlayer to be created.
 * @param xp The xp of the pokemonPlayer to be created.
 * 
 * @return The created pokemonPlayer.
 */
void createPokemonPlayer(int, int, string, vector<Movement>, int);
void createPokemonPlayer(Pokemon, int, string, vector<Movement>, int);
void createPokemonPlayer(int, int, string, vector<int>, int);
void createPokemonPlayer(Pokemon, int, string, vector<int>, int);

#endif