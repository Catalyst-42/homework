
#include <iostream>
using namespace std;

int main() {
    bool lamp = false;
    bool is_day = false;
    bool curtains = false;

    if (is_day && curtains || lamp) {
        cout << "bright" << endl;
    } else {
        cout << "dark" << endl;
    }
}
