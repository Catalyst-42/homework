#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>
#include <map>

// #define M_PI 3.14159265358979323846
#define R "\033[31m"
#define Y "\033[33m"
#define P "\033[35m"
#define W "\033[0m"

using namespace std;
const char *clear = "clear";

void t1() {
    cout << "Euclid's algorithm\n\n";

    int a, b;
    while (cout << "Enter the numbers (a,b): ") {
        if (cin >> a >> b && cin.peek() == '\n' && a > 0 && b > 0) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input!" << endl << endl;
    }

    while (a != 0 && b != 0) {
        if (a > b) a %= b;
        else b %= a;
    }

    cout << "d = " << a + b << endl;
}

void t2() {
    cout << "Prime numbers from 2 to n\n\n";

    int n = 0, numbers = 0;
    bool is_prime = true;
    char confirm = 'y';
    
    while (cout << "Enter the last number (n): ") {
        if (cin >> n && cin.peek() == '\n' && n > 0) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input!" << endl << endl;
    }

    if (n > 2e6) {
        cout << "Last number is too big!\nStart the calculation? (y/n): ";
        cin >> confirm;

        if (confirm != 'y') {
            cout << "Calculation canceled" << endl;
            return;
        }
    }

    for (int number = 3; number <= n; number++) {
        is_prime = true;
        for (int d = 2; d < sqrt(number) + 1; d++) {
            if (number % d == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            numbers++;
            cout << setw(7) << number << ' ';
            if (numbers % 8 == 0) { cout << endl; }
        }
    }
    cout << setw(0) << "\n\nTotal prime numbers [2-n]: " << numbers << endl;
}

void t3() {
    cout << "3-15. Search for a specific word in a text file\n";
    cout << "3-39. Counting the number of occurrences of characters in a text file\n\n";
    ifstream file("file.txt");
    string line, file_data, find, find_file_data;
    size_t pos = 0;
    int entrances = 0;

    while (getline(file, line)) { file_data += line + "\n"; }
    file.close();
    
    cout << file_data;
    find_file_data = file_data;

    cout << "\n" << "Find: ";
    cin >> find;

    while (true) {
        pos = find_file_data.find(find, pos + 1);

        if (pos == string::npos) break;
        entrances++;

        find_file_data.insert(pos + find.length(), W);
        find_file_data.insert(pos, Y);

        // White color length
        pos += 7 + find.length(); 
    }

    system(clear);
    cout << P << "Task 3" << W << endl;
    cout << "3-15. Search for a specific word in a text file\n";
    cout << "3-39. Counting the number of occurrences of characters in a text file\n\n";
    cout << find_file_data << "\nEntrances: " << entrances << '\n';
}

int factorial(int x) {
    int f = 1;
    for (int i=2; i<=x; i++) {
        f *= i;
    }

    return f;
}

void t4() {
    cout << "4-15. y = summa((k+2)! / ((k + 1)^k * x^(4k))), Epsilon = 10^-6\n\n";
    double x = 0;
    double y = 0;
    int k = 0;

    double y_prev = 990;

    while (cout << "Enter 0.4 <= x <= 100 (x): ") {
        if (cin >> x && cin.peek() == '\n' && x >= 0.4 && x <= 100) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input!" << endl << endl;
    }

    while (true) {
        y_prev = y;
        y += (factorial(2*k + 1)) / (pow(k + 1, k) * pow(x, 4*k));

        if (abs(y - y_prev) < 10e-6) { break; }
        k++;
    }
    cout << "y = " << y;
}

void t5() {
    cout << "4-38. Three-digit numbers with a sum of digits m < 27\n\n";
    int m;
    int numbers = 0;

    while (cout << "Enter m < 27 (m): ") {
        if (cin >> m && cin.peek() == '\n' && m < 27) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input!" << endl << endl;
    }

    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                if (a + b + c == m) {
                    cout << a << b << c << ' ';
                    
                    numbers++;
                    if (numbers%8 == 0) { cout << endl; }
                }
            }
        }
    }
    cout  << "\nTotal numbers: " << numbers << endl;
}

void make_file() {
    ofstream file("file.txt");
    string text = "Lorem est ipsum 32 dolor sit amet, at pri utroque 32 debitis. \n"
                  "Harum virtute cum eu? Aperiri 23 nonumes an pri, sumo est nibh\n"
                  "vim te. Quo est ad eius reprehendunt.\n"
                  "\n"
                  "Vix tollit est legimus explicari 3232 et, ex essent eripuit mel!\n"
                  "515 Aeque vocent te duo, dicam (partiendo 324) dissentiunt\n"
                  "per at, meliore accumsan 8-32-515 an vis. Libris menandri ea\n"
                  "eos, everti diceret cum id, 1324 est ne nostrum postulant.\n"
                  "Usu noluisse expetenda ei, an has dico adhuc 32 deserunt,\n"
                  "nusquam concludaturque mei ut est.\n";
    file << text;
    file.close();
}

int main() {
    make_file();
    setlocale(0, "");

    const int tasks = 5; //                  4-15 4-38
    void (*functions[tasks])() = {t1, t2, t3, t4, t5};
    int function_number = 0;

    while (true) {
        cout << "Введите номер задания [1-" << tasks << "]: ";
        cin >> function_number;
        system(clear); // cls
        
        if (function_number==0 || function_number > tasks) { return 0; }
        cout << P << "Task " << function_number << W << endl;
        functions[function_number - 1]();

        cout << endl;
    }
}
