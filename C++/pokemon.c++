#include <iostream>
#include <cmath>
#include "pokemon.h++"
using namespace std;

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