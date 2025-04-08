#include <iostream>
#include <vector>
#include "type.h++"
using namespace std;

// Class definition
class Pokemon {
public:
    // Attributes (data members)
	int id;
	string name;
    int hp;
    int attack;
    int defense; 
    int spattack;
    int spdefense;
    int speed;
    vector<Type> type;
};
