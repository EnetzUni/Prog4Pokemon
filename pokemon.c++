#include <iostream>
#include <cmath>
using namespace std;

void displayInfo() {
    cout << endl;
}

int xptolvl(int xp) {
    return static_cast<int> (cbrt(xp));
}