
#include <iostream>
using namespace std;

int main() {
    double a = 0;
    double b = 0;
    double c = 0;

    cout << "enter a, b, c: ";
    cin >> a;
    cin >> b;
    cin >> c;

    // ax**2 + bx + c = 0
    // D = b**2 - 4ac
    // x = -b ± sqrt(D)
     
    double D = b*b - 4*a*c;

    if (D < 0) { 
        cout << "D < 0" << endl;
        return 0;
    }

    cout << "x1 = " << -b + sqrt(D) << endl;
    cout << "x2 = " << -b + sqrt(D) << endl;
}
