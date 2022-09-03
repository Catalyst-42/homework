#include <iostream>
using namespace std;

int main() {
    double b = 0;
    double c = 0;

    cout << "enter b, c: ";
    cin >> b;
    cin >> c;

    // bx + c = 0
    // bx = -c
    // x = -c/b
    
    if (b != 0) {
        cout << "x = " << -c/b << endl;
    } else {
        cout << "b = 0" << endl;
    }
}
