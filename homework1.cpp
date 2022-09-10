
#include <iostream>
#include <math.h>

using namespace std;

void task1_1() {
    string name = "";

    cout << "enter your name: ";
    cin >> name;
    cout << "Hi, " << name << endl;
}

void task1_2() {
    int a = 0;
    int b = 0;

    cout << "enter a, b: ";
    cin >> a;
    cin >> b;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    if (b != 0) { cout << "a % b = " << a % b << endl; }
}

void task1_3() {
    double b = 0;
    double c = 0;

    cout << "enter b, c: ";
    cin >> b;
    cin >> c;

    // bx + c = 0
    // bx = -c
    // x = -c/b
    
    if (c == 0 && b == 0) {
        cout << "x can be any number" << endl;
    }
    else if (b == 0) { 
        cout << "no answer (division by zero)" << endl;
    }
    else { 
        cout << "x = " << -c/b; 
    }
}

void task1_4() {
    double a = 0;
    double b = 0;
    double c = 0;

    cout << "enter a, b, c: ";
    cin >> a;
    cin >> b;
    cin >> c;

    // ax^2 + bx + c = 0
    // D = b^2 - 4ac
    // x = (-b ± sqrt(D)) / (2a)

    double D = b*b - 4*a*c;

    if (a == 0) {
        // bx + c = 0
        // x = -c/b

        if (b == 0) { 
            cout << "no answer (division by zero)" << endl;
        }
        else { 
            cout << "x = " << -c/b << endl; 
        }
    }
    else if (D < 0) {
        cout << "no answer (negative D)" << endl;
    } 
    else {
        cout << "x1 = " << (-b + sqrt(D)) / (2*a) << endl;
        cout << "x2 = " << (-b - sqrt(D)) / (2*a) << endl;
    }
}

void task1_5() {
    char lamp = 'n';
    char is_day = 'n';
    char curtains = 'n';

    cout << "Is the lamp on? (y/n): ";
    cin >> lamp;

    cout << "is it day now? (y/n): ";
    cin >> is_day;

    cout << "is the curtains are open? (y/n): ";
    cin >> curtains;

    if (is_day == 'y' && curtains == 'y' || lamp == 'y') {
        cout << "bright" << endl;
    }
    else {
        cout << "dark" << endl;
    }
}

int main() {
    cout << "Task 1.1" << endl, task1_1();
    cout << "\nTask 1.2" << endl, task1_2();
    cout << "\nTask 1.3" << endl, task1_3();
    cout << "\nTask 1.4" << endl, task1_4();
    cout << "\nTask 1.5" << endl, task1_5();
}
