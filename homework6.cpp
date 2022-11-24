#include <stdexcept>
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

int counter = 0;
void permutate(string& s, int l, int r) {
    if (l == r) {
        for (int j = 0; j < s.length(); ++j) {
            if (s[j] == to_string(j)[0]) {
                ++counter;
                break;
            }
        }
    }
    else {
        for (int i = l; i <= r; ++i) {
            swap(s[l], s[i]);
            permutate(s, l+1, r);
            swap(s[l], s[i]);
        }
    }
}

void t1() {
    cout << "Шарики. В урне лежат n шариков (n<=10), подсчитать общее количество комбинаций, когда номер шарика совпал с номером действия \"вынимания\" этого шарика\n\n";
    counter = 0;

    string num_str = "0123456789";
    int n = 0;
    while (cout << "Введите число шариков n (n<=10): ") {
        if (cin >> n && cin.peek() == '\n' && n>0 && n<=10) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Неправильный ввод!\n\n";
    }

    permutate(num_str, 0, num_str.substr(0, n).size() - 1);
    cout << "Подходящих комбинаций: " << counter << '\n';
    
}

void t2() {
    cout << "19. Дано целое число (y) в диапазоне 0-99, определяющее возраст (в годах).\nВывести словесное описание указанного возраста\n\n";
    int y = 0;

    string decades[10] = {"", "десять", "двадцать", "трицдать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    string units[10] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    string ext[9] = {"одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    string form[3] = {"", "", ""};
    
    while (cout << "Введите число лет (y): ") {
        if (cin >> y && cin.peek() == '\n' && y>=0 && y<=99) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Неправильный ввод!\n\n";
    }


    if (y == 0) { 
        cout << "ноль лет\n";
    }
    else if (y > 10 && y < 20) {
        cout << ext[y-11] + " лет\n";
    }
    else {
        form[0] = y/10 ? decades[y / 10] + ' ': "";
        form[1] = y%10 ? units[y % 10] + ' ': "";

        if (y%10 == 0 || y%10 > 4) { form[2] = "лет "; }
        else if (y%10 == 1) { form[2] = "год "; }
        else { form[2] = "года "; }

        cout << form[0] << form[1] << form[2] << '\n';
    }
}

void t3() {
    string n = "";
    bool isPalindrom = true;
    cout << "29. Дано натуральное число n. Определить, является ли число n палиндромом\n\n";
    
    while (cout << "Введите число для проверки (n): ") {
        if (cin >> n && cin.peek() == '\n' && regex_match(n, regex("^[0-9]+$"))) { break; }

        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Неправильный ввод!\n\n";
    }

    for (int i = 0; i < n.length() / 2; ++i) {
        if (n[i] != n[n.length()-1 - i]) {
            isPalindrom = false;
            break;
        }
    }

    if (isPalindrom) {
        cout << n + " - палиндром\n";
    }
    else {
        cout << n + " - не палиндром\n";
    }
}

void t4() {
    string n = "";
    int sum_left = 0;
    int sum_right = 0;
    counter = 0;

    cout << "30. В шестизначных трамвайных билетах найти все счастливые билеты (сумма первых 3 чисел равна сумме последних 3 чисел)\n\n";
    
    for (long i=0; i<1000000; ++i) {
        for (int _=0; _<(6 - to_string(i).length()); ++_) {
            n += '0';
        }
        n += to_string(i);

        sum_left = 0;
        sum_right = 0;

        for (int j = 0; j < n.length() / 2; ++j) {
            sum_left += n[j];
            sum_right += n[n.length()-1 - j];
        }

        if (sum_left == sum_right) {
            cout << n << ' ';
            ++counter;
            if (counter%10==0) cout << '\n';
        }

        n = "";

    }
    cout << "\nВсего счастливых билетов: " << counter << " (" << counter/10000.0 << "%)" << '\n';
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int tasks = 4;
    void (*functions[tasks])() = {t1, t2, t3, t4};
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