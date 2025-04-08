#include <iostream>
#include <cmath>
using namespace std;

void displayInfo() {
    cout << endl;
}

int xpToLvl(int xp) {
    // Cube root-based level calculation
    // Truncates decimal part
    return static_cast<int> (cbrt(xp));
}