#include <iostream>
#include <vector>
using namespace std;

// Class definition
class Player {
public:
    // Attributes (data members)
	string nickname;
    string password;
    bool gender;
    vector<Pokemon> listPokemon;


    // Method (member function)
    void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << ", Year: " << year << endl;
    }
};
