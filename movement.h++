#include <iostream>
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

    // Method (member function)
    void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << ", Year: " << year << endl;
    }
};
