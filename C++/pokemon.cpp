#include <iostream>
#include <cmath>
#include "pokemon.hpp"
using namespace std;

/** 
 * @class Pokemon
 * @brief This is the main Pokemon class, with base stats.
 */

// Getter for the Pokedex number
int Pokemon::getId() {
    return this->id;
}

// Getter for the name of the Pokemon
string Pokemon::getName() {
    return this->name;
}

// Getter for the base hit points of the Pokemon
int Pokemon::getHp() {
    return this->hp;
}

// Getter for the base attack stat of the Pokemon
int Pokemon::getAttack() {
    return this->attack;
}

// Getter for the base defense stat of the Pokemon
int Pokemon::getDefense() {
    return this->defense;
}

// Getter for the base special attack stat of the Pokemon
int Pokemon::getSpattack() {
    return this->spattack;
}

// Getter for the base special defense stat of the Pokemon
int Pokemon::getSpdefense() {
    return this->spdefense;
}

// Getter for the base speed stat of the Pokemon
int Pokemon::getSpeed() {
    return this->speed;
}

// Getter for the list of types of the Pokemon
vector<Type> Pokemon::getType() {
    return this->type;
}

/// Getter for the level at which the Pokemon evolves.
int Pokemon::getEvolvl() {
    return this->evolvl;
}

/** 
 * @class PokemonPlayer
 * @brief This pokemon class creates basically an instance of a pokemon, a pokemon that is specific for a player
 * @see Pokemon
 */

// Getter for the Pokemon's nickname
string PokemonPlayer::getNickname() {
    return this->nickname;
}

// Setter for the Pokemon's nickname
void PokemonPlayer::setNickname(string& newNickname) {
    this->nickname = newNickname;
}

// Getter for the Pokemon's list of movements
vector<Movement> PokemonPlayer::getListMovement() {
    return listMovement;
}

// Setter for the Pokemon's list of movements
void PokemonPlayer::setListMovement(vector<Movement>& newListMovement) {
    this->listMovement = newListMovement;
}

// Getter for the Pokemon's level
int PokemonPlayer::getLvl() {
    return lvl;
}

// Setter for the Pokemon's level
void PokemonPlayer::setLvl(int newLvl) {
    this->lvl = newLvl;

    // Stats are updated because of the level change
    updateStats(this);
}

// Getter for the Pokemon's xp
int PokemonPlayer::getXp() {
    return this->xp;
}

// Setter for the Pokemon's xp
void PokemonPlayer::setXp(int newXp) {
    // Update unless higher than 1M, in that case it stays at 1M.
    this->xp = (newXp > 1000000) ? 1000000 : newXp;

    // Update the level if the xp has reached a new level
    if (xpToLvl(xp) > getLvl()) {
        setLvl(xpToLvl(xp));
    }
}

// Getter for the hit points according to the current level
int PokemonPlayer::getLvlHp() {
    return this->lvlhp;
}

// Setter for the hit points according to the current level
void PokemonPlayer::setLvlHp(int newLvlHp) {
    this->lvlhp = newLvlHp;
}

// Getter for the attack stat according to the current level
int PokemonPlayer::getLvlAttack() {
    return this->lvlattack;
}

// Setter for the attack stat according to the current level
void PokemonPlayer::setLvlAttack(int newLvlAttack) {
    this->lvlattack = newLvlAttack;
}

// Getter for the defense stat according to the current level
int PokemonPlayer::getLvlDefense() {
    return this->lvldefense;
}

// Setter for the defense stat according to the current level
void PokemonPlayer::setLvlDefense(int newLvlDefense) {
    this->lvldefense = newLvlDefense;
}

// Getter for the special attack stat according to the current level
int PokemonPlayer::getLvlSpAttack() {
    return this->lvlspattack;
}

// Setter for the special attack stat according to the current level
void PokemonPlayer::setLvlSpAttack(int newLvlSpAttack) {
    this->lvlspattack = newLvlSpAttack;
}

// Getter for the special defense stat according to the current level
int PokemonPlayer::getLvlSpDefense() {
    return this->lvlspdefense;
}

// Setter for the special defense stat according to the current level
void PokemonPlayer::setLvlSpDefense(int newLvlSpDefense) {
    this->lvlspdefense = newLvlSpDefense;
}

// Getter for the speed stat according to the current level
int PokemonPlayer::getLvlSpeed() {
    return this->lvlspeed;
}

// Setter for the speed stat according to the current level
void PokemonPlayer::setLvlSpeed(int newLvlSpeed) {
    this->lvlspeed = newLvlSpeed;
}

// Getter for the Pokemon's current hit points
int PokemonPlayer::getCurHp() {
    return this->curHp;
}

// Setter for the Pokemon's current hit points
void PokemonPlayer::setCurHp(int newCurHp) {
    this->curHp = newCurHp;
}

// Getter for the Pokemon's current status
Status PokemonPlayer::getStatus() {
    return this->status;
}

// Setter for the Pokemon's current status
void PokemonPlayer::setStatus(Status& newStatus) {
    this->status = newStatus;
}

void displayInfo() {
    cout << endl;
}

int xpToLvl(int xp) {
    // Cube root-based level calculation
    // Truncates decimal part
    return static_cast<int> (cbrt(xp));
}

void updateStats(PokemonPlayer* pokemon) {
    // We calculate the new attributes by using the formulas
    // IV, EV and Nature are set to their default max values for all (IV = 31, EV = 255 & Nature = 1.1 (110%))
    // Level refers to the new level of the pokemon and Base refers to the value of that stat for the pokemon species
    // HP = (((2 * BASE + IV (EV / 4)) * LEVEL) / 100) + LEVEL + 10
    pokemon->setLvlHp(static_cast<int> (((2 * pokemon->getHp() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + pokemon->getLvl() + 10);
    
    // Other Stat = ((((2 * BASE + IV (EV / 4)) * LEVEL) / 100) + 5) * NATURE
    pokemon->setLvlAttack(static_cast<int> ((((2 * pokemon->getAttack() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlDefense(static_cast<int> ((((2 * pokemon->getDefense() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlSpAttack(static_cast<int> ((((2 * pokemon->getSpattack() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlSpDefense(static_cast<int> ((((2 * pokemon->getSpdefense() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlSpeed(static_cast<int> ((((2 * pokemon->getSpeed() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
}