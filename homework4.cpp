#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>
#include <map>

// #define M_PI 3.14159265358979323846
#define P "\033[35m"
#define W "\033[0m"

using namespace std;

void t1() {
    cout << P << "Task 1\n" << W << endl;
    ofstream write_file("file2.txt");

    for (int i = 0; i < 10; i++) { 
        write_file << (double) rand() / RAND_MAX * 160 << endl; 
    }

    write_file.close();

    ifstream read_file("file2.txt");
    double sum = 0;
    double line;

    while (read_file >> line) {
        sum += line;
    }
    
    read_file.close();
    cout << "sum = " << sum << endl;
}

int sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void t2() {
    cout << P << "Task 2\n" << W << endl;
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

void rectangle_area() {
    double a, b;

    cout << "Enter rectangle parameters (a,b): ";
    cin >> a >> b;
    if (a > 0 && b > 0) {
        cout << "S = " << a*b << endl;
    } else {
        cout << "[Error] sides can't be negative!" << endl;
    }
}

void triangle_area() {
    double a, b, c, alpha, beta;
    double p;

    int choice;
    cout << "Choose a formula:" << endl;
    cout << "1: S = sqrt(p*(p - a)*(p - b)*(p - c))\n   by a, b, c\n" << endl;
    cout << "2: S = 0.5*a*b*sin(alpha)\n   by a, b, alpha in degrees\n" << endl;
    cout << "3: S = (a*a * sin(alpha) * sin(beta)) / (2 * sin(alpha + beta))\n   by a, alpha and beta in degrees\n" << endl;
    cout << "Input: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter triangle parameters (a,b,c): ";
            cin >> a >> b >> c;
            if (a > 0 && b > 0 && c > 0) { 
                if (a+b > c && a+c > b && c+b > a) {
                    p = (a+b+c) / 2;
                    cout << "S = " << sqrt(p*(p-a)*(p-b)*(p-c)) << endl;
                } 
                else {
                    cout << "[Error] Not a triangle!" << endl;
                }
            } else { 
                cout << "[Error] sides can't be negative!" << endl;
            }
            break;        

        case 2:
            cout << "Enter triangle parameters (a,b,alpha): ";
            cin >> a >> b >> alpha;
            alpha = alpha * M_PI / 180;
            if (a > 0 && b > 0 && alpha < M_PI) {
                cout << "S = " << 0.5*a*b*sin(alpha) << endl;
            } 
            else {
                cout << "[Error] a and b can't be negative, alpha should be less than 180 degrees!" << endl;
            }
            break;

        case 3:
            cout << "Enter triangle parameters (a,alpha,beta): ";
            cin >> a >> alpha >> beta;
            alpha = alpha * M_PI / 180;
            beta = beta * M_PI / 180;
            if (a > 0 && alpha > 0 && beta > 0 && alpha + beta < M_PI) {
                cout << "S = " << (a*a*sin(alpha)*sin(beta)) / (2*sin(alpha + beta)) << endl;
            }
            else {
                cout << "[Error] a and h can't be negative, alpha + beta should be less than 180 degrees!" << endl;
            }
            break;

        default:
            cout << "[Error] Wrong formula number!" << endl;
            break;
    }
}

void circle_area() {
    double r;
    cout << "Enter circle radius (r): ";
    cin >> r;

    if (r >= 0) {
        cout << "S = " << M_PI * r*r << endl;
    } 
    else {
        cout << "[Error] Radius can't be negative!" << endl;
    }
}

void t3() {
    cout << P << "Task 3\n" << W << endl;
    double a, b, c, r;

    int figure_number;
    cout << "Choose figure:\n1: Rectangle\n2: Triangle\n3: Circle\nFigure number: ";
    cin >> figure_number;

    switch (figure_number) {
        case 1:
            rectangle_area();
            break;

        case 2:
            triangle_area();
            break;

        case 3:
            circle_area();
            break;

        default:
            cout << "[Error] Wrong figure number!" << endl;
            break;
    }
}

void t4() {
    cout << P << "Task 4\n" << W << endl;
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
    cout << P << "Task 5\n" << W << endl;
    const int X = 64;
    const int Y = 7;
    const int scale = Y / 2;
      
    bool glyph[6] = {false, false, false, false, false, true};
    for (int y = Y; y >= 0; y--) {
        for (int x = 0; x <= X; x++) {
            glyph[0] = (x==X && y==scale);
            glyph[1] = (y==Y && x==0);
            glyph[2] = (x==0);
            glyph[3] = (round(sin(M_PI*x/16)*scale + scale)==y);
            glyph[4] = (y==scale);

            for (int g = 0; g <= 5; g++) {
                if (glyph[g]) {
                    cout << ">^|*- "[g];
                    break;
                }
            }
        }
        cout << endl;
    }
}

void t6() {
    cout << P << "Task 6\n" << W << endl;
    map <char, int> intmap;
    intmap['I'] = 1;    intmap['V'] = 5;
    intmap['X'] = 10;   intmap['L'] = 50;
    intmap['C'] = 100;  intmap['D'] = 500;
    intmap['M'] = 1000; 

    string input;
    while (cout << "Enter the Roman number [IVXLCDM]: ") {
        cin >> input;
        if (cin.good() && regex_match(input, regex("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"))) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Wrong number pattern!" << endl << endl;
        
    }


    int sum = intmap[input[input.length()-1]];
    for (int i = input.length()-2; i >= 0; i--) {
        if (intmap[input[i]] < intmap[input[i+1]]) { sum -= intmap[input[i]]; }
        else { sum += intmap[input[i]]; }
    }

    cout << input << " = " << sum << endl;
}

void t7() {
    cout << P << "Task 7\n" << W << endl;
    int s=0, m=37, b=3, c=64;
    int lim;

    while (cout << "Enter the recursion limit (lim): ") {
        if (cin >> lim && cin.peek() == '\n') { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input!" << endl << endl;
    }

    for (int i = 0; i < lim; i++) {
        s = (m*s + b) % c;
    }

    cout << "s = " << s << endl;
}

void t8() {
    cout << P << "Task 8\n" << W << endl;
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
    double sold[3] = {C[0][0], C[1][0], C[2][0]};

    int sold_min = 1, sold_max = 1;
    int min = C[0][0], max = C[0][0];
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

    int comission_min = 1, comission_max = 1;
    min = C[0][1], max = C[0][1];
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

    
    
    cout << sold[0] + sold[1] + sold[2] << "c sold out" << endl;
    cout << comission[0] + comission[1] + comission[2] << "c from comission" << endl;
    cout << sold[0] + sold[1] + sold[2] + comission[0] + comission[1] + comission[2] << "c all coins" << endl;
}

void t9() {
    cout << P << "Task 9\n" << W << endl;

    long int D, x, y;
    bool error = false;
    string A = "", B = "";
    string intmap = "0123456789ABCDEFGHJKLMNOPQRSTUVWXYZ";

    while (cout << "Input numbers for Ax -> By (A,x,y): ") {
        cin >> A >> x >> y;

        for (int i=0; i<A.length(); i++) {
            A[i] = toupper(A[i]);
        }
        
        if (!regex_match(A, regex("^[A-Z0-9]+$"))) {
            cout << "Number A can only contain characters 0-9 A-Z!" << endl;
            error = true;
        }

        if (!error) {
            for (int i = 0; i < A.length(); i++) {
                if (intmap.find(A[i]) >= x) {
                    cout << "Incorrect number system!" << endl;     
                    error = true;
                    break;
                }    
            }
        }

        if (!error) {
            if (x > 35 || x < 2 || y < 0 || y > 35 || cin.peek() != '\n') {
                cout << "Number system can be only from 2 to 35!" << endl;
                error = true;
            }
        }

        if (!error) { break; }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << endl;
        error = false;
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

void make_file() {
    ofstream file("file.txt");
    string text = "27823kjm2398 ijk2 1234 jhk234 123\n"
                  "234 321jlkn 13l2nk 23l1 21ln2 2\n"
                  " \n"
                  "1 a 2 b 3\n"
                  "4 c 5 d 6\n"
                  " \n"
                  "Lorem ipsum dolor sit amet, consectetur adipiscing elit. \n";
    file << text;
    file.close();
}

int main() {
    setlocale(0, "");
    make_file();
    int function_number = 0;
    void (*functions[9])() = {t1, t2, t3, t4, t5, t6, t7, t8, t9};

    /*
    for (function_number=1; function_number<=9; function_number++) {
        functions[function_number-1]();
    }
    */

    while (true) {
        cout << "?????????????? ?????????? ?????????????? [1-9]: ";
        cin >> function_number;
        
        if (function_number==0) { return 0; }
        function_number--;
        
        functions[function_number]();
    }
}
