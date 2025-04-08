#include <iostream>
#include "type.h++"
using namespace std;

// Class definition
class Movement {
public:
    // Attributes (data members)
	enum class Effect { 
        PHYSICAL, SPECIAL, STATUS 
    };
	int id;
	string name;
    Type type;
    Effect effect;
    int power;
    int accuracy;
};
