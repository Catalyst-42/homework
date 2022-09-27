#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>
#include <map>

#define M_PI 3.14159265358979323846
#define P "\033[35m"
#define W "\033[0m"

using namespace std;

void t1() {
    ofstream write_file("file2.txt");
    for (int i = 0; i < 2; i++) { write_file << rand()<< endl; }
    write_file.close();

    double sum = 0;
    string line;
    ifstream read_file("file2.txt");
    while (getline(read_file, line)) { sum += stod(line); }
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
                cout << "S = " << rectangular_area(a, b) << endl;
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
                    cout << "[Error] Not a triangle!" << endl;
                }
            } else { 
                cout << "[Error] sides can't be negative!" << endl;
            }
            break;

        case 3: // circle
            cout << "Enter circle radius (r): ";
            cin >> r;
            if (r >= 0) {
                cout << "S = " << circle_area(r) << endl;
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
    const int X = 60;
    const int Y = 7;
    const int scale = Y / 2;
      
    for (int y = Y; y >= 0; y--) {
        for (int x = 0; x <= X; x++) {
            round(sin(M_PI*x/16)*scale + scale) == y ? cout << '*' : cout << ' ';
        }
        cout << endl;
    }
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

    if (regex_match(input, regex("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"))) {
        int sum = intmap[input[input.length()-1]];
        for (int i = input.length()-2; i >= 0; i--) {
            if (intmap[input[i]] < intmap[input[i+1]]) { sum -= intmap[input[i]]; }
            else { sum += intmap[input[i]]; }
        }

        cout << input << " = " << sum << endl;
    }
    else {
        cout << "Wrong number pattern!" << endl;
    }
}

void t7() {
    int s=0, m=37, b=3, c=64;

    while (true) {
        s = (m*s + b) % c;
        cout << s;
        
        if (cin.get() == '0') { return; }
    }
}

void t8() {
    double A[3][4] = {
        {5,  2, 0, 10},
        {3,  5, 2, 5},
        {20, 0, 0, 0}
    };

    double B[4][2] = {
        {1.2, 0.5},
        {2.8, 0.4},
        {5.0, 1.0},
        {2.0, 1.5},
    };

    double C[3][2] = {};
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 2; x++) {
            C[y][x] = 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double comission[3] = {C[0][1], C[1][1], C[2][1]};
    double sold[3] = {C[0][0] - C[0][1], C[1][0] - C[1][1], C[2][0] - C[2][1]};

    int comission_min = 1, comission_max = 3;
    int min = C[0][1], max = C[2][1];
    for (int i = 1; i < 3; i++) {
        if (comission[i] > max) {
            comission_max = i + 1; max = comission[i];
        }
        if (comission[i] < min) {
            comission_min = i + 1; min = comission[i];
        }
    }

    cout << "max comission: " << comission_max << " seller (" << max << "c)" << endl;
    cout << "min comission: " << comission_min << " seller (" << min << "c)" << endl;

    int sold_min = 1, sold_max = 3;
    min = C[0][0] - C[0][1]; max = C[2][0] - C[2][1];
    for (int i = 1; i < 3; i++) {
        if (sold[i] > max) {
            sold_max = i + 1; max = sold[i];
        }

        if (sold[i] < min) {
            sold_min = i + 1; min = sold[i];
        }
    }

    cout << "max sold: " << sold_max << " seller (" << max << "c)" << endl;
    cout << "min sold: " << sold_min << " seller (" << min << "c)" << endl;
    
    cout << sold[0] + sold[1] + sold[2] << "c sold out" << endl;
    cout << comission[0] + comission[1] + comission[2] << "c from comission" << endl;
    cout << sold[0] + sold[1] + sold[2] + comission[0] + comission[1] + comission[2] << "c all coins" << endl;
}

void t9() {
    long int D, x, y;
    string A = "", B = "";
    string intmap = "0123456789ABCDEFGHJKLMNOPQRSTUVWXYZ";

    cout << "Input numbers for Ax -> By (A,x,y): ";
    cin >> A >> x >> y;

    for (int i = 0; i < A.length(); i++) {
        if (intmap.find(A[i]) >= x) {
            cout << "Wrong input!" << endl; 
            return;       
        }
    }

    D = 0;
    for (int i = 0; i < A.length(); i++) {
        D += intmap.find(A[i]) * pow(x, -i+A.length()-1);
    }

    while (D > 0) {
        B = intmap[D%y] + B;
        D /= y;
    }

    cout << "B = " << B << endl;
}

int main() {
    setlocale(0, "");
    cout << P << "Test 1\n" << W, t1();
    cout << P << "Test 2\n" << W, t2();
    cout << P << "Test 3\n" << W, t3();
    cout << P << "Test 4\n" << W, t4();
    cout << P << "Test 5\n" << W, t5();
    cout << P << "Test 6\n" << W, t6();
    cout << P << "Test 7\n" << W, t7();
    cout << P << "Test 8\n" << W, t8();
    cout << P << "Test 9\n" << W, t9();
}
