
#include <iostream>
using namespace std;

int main() {
    int a = 0;
    int b = 0;

    cout << "enter a, b: ";
    cin >> a;
    cin >> b;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a + b << endl;
    if (b != 0) {
        cout << "a % b = " << a % b << endl;
    }
}
