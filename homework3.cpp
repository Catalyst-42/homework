#include <algorithm>
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
        cout << "S and n can't be negative!" << endl;
        return;
    }

    if (S == 0) {
        cout << "m = 0" << endl;
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

    if (1+p/100 < 0 && (int) n != n) {
        cout << "m can't be founded (root from negative number)" << endl;
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
    double S, m, n, r, p;
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
    
    double left = -100;
    double right = 1000;
    double m_approx = 0;

    while (left < right) {
        p = (left + right) / 2;
        if (p == -200) p -= 1;

        r = p / 100;
        m_approx = (S*r * pow(1+r, n)) / (12 * (pow(1+r, n) - 1));

        if (p == right) right += 1000;
        if (p == left) left -= 1000;

        // cout << m - m_approx << " <> p =" << p << endl;

        if (m_approx == m) { 
            cout << "p (approx.) = " << p << endl; 
            break; 
        }

        if (m_approx > m) { right = p; }
        else { left = p; }
    }
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

    bool find_once = false;
    bool find = false;

    while (getline(file, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line.at(i))) {
                cout << line.at(i); find = true; find_once = true;
            } 
            else if (find) {
                cout << " "; find = false;
            }
        }
    }

    if (!find_once) cout << "File doesn't contain numbers!";
    cout << endl;
    file.close();
}

void t5() {
    string line = "";

    cout << "Enter line to sort: ";
    cin >> line;

    // insertion sort 012AaBbCc
    for (int i = 0; i < line.length(); ++i) {
        int j = i;
        while (j > 0 && tolower(line[j]) <= tolower(line[j-1])) {
            if (line[j] != tolower(line[j - 1])) {
                swap(line[j], line[j-1]);
            }
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
