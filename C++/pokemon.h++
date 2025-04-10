#pragma once

#include <iostream>
#include <vector>
#include "type.h++"
#include "movement.h++"
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

    public:
        // Getter for the Pokedex number
        int getId() const {
            return id;
        }

        // Getter for the name of the Pokemon
        string getName() const {
            return name;
        }

        // Getter for the base hit points of the Pokemon
        int getHp() const {
            return hp;
        }

        // Getter for the base attack stat of the Pokemon
        int getAttack() const {
            return attack;
        }

        // Getter for the base defense stat of the Pokemon
        int getDefense() const {
            return defense;
        }

        // Getter for the base special attack stat of the Pokemon
        int getSpattack() const {
            return spattack;
        }

        // Getter for the base special defense stat of the Pokemon
        int getSpdefense() const {
            return spdefense;
        }

        // Getter for the base speed stat of the Pokemon
        int getSpeed() const {
            return speed;
        }

        // Getter for the list of types of the Pokemon
        vector<Type> getType() const {
            return type;
        }
};

class PokemonPlayer : public Pokemon {
    private:
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
        // Getter for the Pokemon's nickname
        string getNickname() const {
            return nickname;
        }

        // Setter for the Pokemon's nickname
        void setNickname(const string& newNickname) {
            nickname = newNickname;
        }

        // Getter for the Pokemon's list of movements
        vector<Movement> getListMovement() const {
            return listMovement;
        }

        // Setter for the Pokemon's list of movements
        void setListMovement(const vector<Movement>& newListMovement) {
            listMovement = newListMovement;
        }

        // Getter for the Pokemon's level
        int getLvl() const {
            return lvl;
        }

        // Setter for the Pokemon's level
        void setLvl(int newLvl) {
            lvl = newLvl;

            updateStats(this);
        }

        // Getter for the Pokemon's xp
        int getXp() const {
            return xp;
        }

        // Setter for the Pokemon's xp
        void setXp(int newXp) {
            xp = (newXp > 1000000) ? 1000000 : newXp;

            if (xpToLvl(xp) > getLvl()) {
                setLvl(xpToLvl(xp));
            }
        }

        // Getter for the hit points according to the current level
        int getLvlHp() const {
            return lvlhp;
        }

        // Setter for the hit points according to the current level
        void setLvlHp(int newLvlHp) {
            lvlhp = newLvlHp;
        }

        // Getter for the attack stat according to the current level
        int getLvlAttack() const {
            return lvlattack;
        }

        // Setter for the attack stat according to the current level
        void setLvlAttack(int newLvlAttack) {
            lvlattack = newLvlAttack;
        }

        // Getter for the defense stat according to the current level
        int getLvlDefense() const {
            return lvldefense;
        }

        // Setter for the defense stat according to the current level
        void setLvlDefense(int newLvlDefense) {
            lvldefense = newLvlDefense;
        }

        // Getter for the special attack stat according to the current level
        int getLvlSpAttack() const {
            return lvlspattack;
        }

        // Setter for the special attack stat according to the current level
        void setLvlSpAttack(int newLvlSpAttack) {
            lvlspattack = newLvlSpAttack;
        }

        // Getter for the special defense stat according to the current level
        int getLvlSpDefense() const {
            return lvlspdefense;
        }

        // Setter for the special defense stat according to the current level
        void setLvlSpDefense(int newLvlSpDefense) {
            lvlspdefense = newLvlSpDefense;
        }

        // Getter for the speed stat according to the current level
        int getLvlSpeed() const {
            return lvlspeed;
        }

        // Setter for the speed stat according to the current level
        void setLvlSpeed(int newLvlSpeed) {
            lvlspeed = newLvlSpeed;
        }

        // Getter for the Pokemon's current hit points
        int getCurHp() const {
            return curHp;
        }

        // Setter for the Pokemon's current hit points
        void setCurHp(int newCurHp) {
            curHp = newCurHp;
        }

        // Getter for the Pokemon's current status
        Status getStatus() const {
            return status;
        }

        // Setter for the Pokemon's current status
        void setStatus(const Status& newStatus) {
            status = newStatus;
        }
};

/**
 * @brief Calculates level based on experience points.
 * 
 * @param int The experience points accumulated by the player.
 * @return The level as an integer.
 */
int xpToLvl(int);

/**
 * @brief Updates the stats based on the new level.
 * 
 * @param PokemonPlayer* The pokemon whose stats need to be updated;
 */
void updateStats(PokemonPlayer*);