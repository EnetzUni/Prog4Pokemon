#include <iostream>
#include <vector>
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
    vector<Type>;

    // Method (member function)
    void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << ", Year: " << year << endl;
    }
};
