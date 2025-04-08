#include <iostream>
#include <vector>
#include "pokemon.h++"
using namespace std;

// Class definition
class Player {
public:
    // Attributes (data members)
	string nickname;
    string password;
    bool gender;
    vector<Pokemon> listPokemon;
};
