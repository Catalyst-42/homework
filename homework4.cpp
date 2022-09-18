#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <map>

using namespace std;

void t1() {
    ofstream write_file("file2.txt");
    for (int i = 0; i < 10; i++) { write_file << rand() << endl; }
    write_file.close();

    int sum = 0;
    string line;
    ifstream read_file("file2.txt");
    while (getline(read_file, line)) { sum += stoi(line); }
    read_file.close();

    cout << "sum = " << sum << endl;
}

int sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void t2() {
    double x;
    cout << "Enter x: ";
    cin >> x;

    if (sign(x) > 0) {
        cout << '+' << x << ", Positive number" << endl;
    } 
    else if (sign(x) < 0) {
        cout << x << ", Negative number" << endl;
    } 
    else {
        cout << "0, Zero does not have a sign" << endl;
    }
}

double rectangular_area(double a, double b) {
    return a * b;
}

double triangle_area(double a, double b, double c) {
    double p = (a+b+c) / 2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

double circle_area(double r) {
    return M_PI * r*r;
}

void t3() {
    double a, b, c, r;

    int figure_number;
    cout << "Choose figure:\n1: Rectangle\n2: Triangle\n3: Circle\nFigure number: ";
    cin >> figure_number;

    switch (figure_number) {
        case 1: // rectangle
            cout << "Enter rectangle parameters (a,b): ";
            cin >> a >> b;
            if (a > 0 && b > 0) {
                cout << "S = " << rectangular_area(a, b);
            } else {
                cout << "[Error] sides can't be negative!" << endl;
            }
            break;

        case 2: // triangle
            cout << "Enter triangle paremeters (a,b,c): ";
            cin >> a >> b >> c;
            if (a > 0 && b > 0 && c > 0) { 
                if (a+b > c && a+c > b && c+b > a) {
                    cout << "S = " << triangle_area(a, b, c) << endl;
                } else {
                    cout << "[Error] Not a triangle!";
                }
            } else { 
                cout << "[Error] sides can't be negative!" << endl;
            }
            break;

        case 3: // circle
            cout << "Enter circle radius (r): ";
            cin >> r;
            if (r >= 0) {
                cout << "S = " << circle_area(r);
            } else {
                cout << "[Error] Radius can't be negative!" << endl;
            }
            break;
    }
}

void t4() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 24; j++) {
            if (j < 8) cout << "* ";
            else cout << "--";
        }
        cout << endl;
    }
    
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            cout << "--";
        }
        cout << endl;
    }
}

void t5() {
    // Y |
    //   |.-.     .-.     .-   1 line
    // --/---\---/---\---/-->  2 line
    // -´|    `-´     `-´   X  3 line
    //   |

    int x_length = 14; // symbols

    cout << "Y ^";
    for (int i = 3; i < x_length; i++) { cout << ' '; }
    cout << endl;

    // 1 line
    cout << "  |";
    string heads = ".-.     ";
    for (int i = 0; i < x_length / 8; i++) { cout << heads; }
    cout << heads.substr(0, x_length % 8) << endl;

    // 2 line
    string mids = "---\\---/";
    cout << "--/";
    for (int i = 0; i < x_length / 8; i++) { cout << mids; }
    cout << mids.substr(0, x_length % 8) << ">" << endl;

    // 3 line
    string tails = "    `-´ ";
    cout << "-´|";
    for (int i = 0; i < x_length / 8; i++) { cout << tails; }
    cout << tails.substr(0, x_length % 8) << "X" << endl;

    cout << "  |sin(" << (double) x_length / 4 << "π) = " << sin((double) x_length / 4 * M_PI) << endl;
}

void t6() {
    map <char, int> intmap;
    intmap['I'] = 1;    intmap['V'] = 5;
    intmap['X'] = 10;   intmap['L'] = 50;
    intmap['C'] = 100;  intmap['D'] = 500;
    intmap['M'] = 1000;

    string input;
    cout << "Enter the Roman number [IVXLCDM]: ";
    cin >> input;

    int sum = intmap[input[input.length()-1]];
    for (int i = input.length()-2; i >= 0; i--) {
        if (intmap[input[i]] < intmap[input[i+1]]) { sum -= intmap[input[i]]; }
        else { sum += intmap[input[i]]; }
    }

    cout << input << " = " << sum << endl;
}

void t7() {
    int s=0, m=37, b=3, c=64;

    while (true) {
        s = (m*s + b) % c;
        cout << s;

        cin.get();
    }
    
}

int main() {
    setlocale(0, "");
    // cout << "Test 1\n", t1();
    // cout << "Test 2\n", t2();
    // cout << "Test 3\n", t3();
    // cout << "Test 4\n", t4();
    // cout << "Test 5\n", t5();
    // cout << "Test 6\n", t6();
    cout << "Test 7\n", t7();
}