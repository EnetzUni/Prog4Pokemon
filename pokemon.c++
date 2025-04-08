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
    pokemon->setLvlHp(static_cast<int> (((2 * pokemon->getHp() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + pokemon->getLvl() + 10);
    pokemon->setLvlAttack(static_cast<int> ((((2 * pokemon->getAttack() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlDefense(static_cast<int> ((((2 * pokemon->getDefense() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlSpAttack(static_cast<int> ((((2 * pokemon->getSpattack() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlSpDefense(static_cast<int> ((((2 * pokemon->getSpdefense() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
    pokemon->setLvlSpeed(static_cast<int> ((((2 * pokemon->getSpeed() + 31 + (255 / 4)) * pokemon->getLvl()) / 100) + 5) * 1.1);
}