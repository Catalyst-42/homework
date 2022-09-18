#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <math.h>

using namespace std;

void t1() {
    double S, n, p;
    cout << "Enter the parameters (S, n, p): ";
    cin >> S >> n >> p;
    
    if (S < 0 || n < 0) {
        cout << "S and n can't be negative!";
        return;
    }

    if (p == 0) {
        cout << "m = " << S / n / 12<< endl;
        return;
    }

    if (n == 0) {
        cout << "m = " << S * (1 + p/100) << endl;
        return;
    }

    double r = p/100;
    double m = (S*r * pow(1+r, n)) / (12 * (pow(1+r, n) - 1));

    if ((12 * (pow(1+r, n) - 1)) == 0) {
        cout << "m can't be founded (division by zero)" << endl;
    } else {
        cout << "m = " << m << endl;
    }
}

void t2() {
    double S, m, n, r;
    cout << "Enter the parameters (S, m, n): ";
    cin >> S >> m >> n;
    
    if (S < 0 || n < 0) {
        cout << "S and n can't be negative" << endl;
        return;
    }

    if (S == 0 && m == 0) {
        cout << "p can be any number" << endl;
        return;
    }

    if (n == 0) {
        cout << "p = " << m/S*100 - 100 << endl;
        return;
    }
    
    for (double p = -500; p <= 500; p += 0.1) {
        r = (double) p/100;
        if (abs(m - (S*r * pow(1+r, n)) / (12 * (pow(1+r, n) - 1))) <= 0.01) {
            cout << "p = " << p << endl;
            return;
        }
    }

    cout << "p not in range [-500, 500]" << endl;
}

void t3() {
    ifstream file;
    string line, file_data;

    file.open("file.txt");

    while (getline(file, line)) { file_data += line + "\n"; }
    cout << file_data;

    file.close();
}

void t4() {
    ifstream file("file.txt");
    string line;

    while (getline(file, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line.at(i))) {
                cout << line.at(i);
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    file.close();
}

void t5() {
    int length = 30;
    char line[length];

    cout << "Enter 30 characters: ";
    cin >> line;

    // insertion sort
    for (int i = 0; i < length; ++i) {
        int j = i;
        while (j > 0 && line[j] < line[j-1]) {
            swap(line[j], line[j-1]);
            j--;
        }
    }

    cout << line << endl;
}

int main() {
    setlocale(0, "");
    cout << "Task 1\n"; t1();
    cout << "Task 2\n"; t2();
    cout << "Task 3\n"; t3();
    cout << "Task 4\n"; t4();
    cout << "Task 5\n"; t5();
}
