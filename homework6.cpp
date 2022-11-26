#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>
#include <map>

// #define M_PI 3.14159265358979323846
#define R "\033[31m"
#define G "\033[32m"
#define Y "\033[33m"
#define P "\033[35m"
#define W "\033[0m"

using namespace std;
const char *clear = "clear"; // or "cls" for windows

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

string toBinary(int n) {
    string binary;
    while (n != 0) {
        binary = (n%2==0 ? '0' : '1') + binary;
        n /= 2;
    }
    return binary;
}

void t5() {
    cout << "В выражении 12894*4193*9510*8653*4381*2546*1158*8645*2587 заменить звёздочки знаками \"+\" или \"-\", чтобы получившееся выражение равнялось 1989\n\n";
    string command_binary = "";
    int sum = 12894;

    int numbers[9] = {12894, 4193, 9510, 8653, 4381, 2546, 1158, 8645, 2587};
    for (int command = 0; command < 0b11111111; ++command) {
        // make 01010011 command, 0 -> -, 1 -> +
        command_binary = "";
        for (int _ = 0; _ < 8 - toBinary(command).length(); ++_) {
            command_binary += '0';
        }
        command_binary += toBinary(command);

        // try to count by command
        sum = 12894;
        for (int c = 0; c < 8; ++c) {
            if (command_binary[c] == '0') sum -= numbers[c+1];
            else sum += numbers[c+1];
        }

        if (sum == 1989) {
            for (int c = 0; c < 8; ++c) {
                cout << numbers[c] << ((command_binary[c] == '0') ? " - " : " + ");
            }
            cout << numbers[8] << " = " << sum;
        }
    }
} 

void t6() {
    cout << "87. Построить все правильные скобочные выражения длины 10\n\n";
    string str = "";
    int sum = 0;
    counter = 0;

    for (int i=0; i<0b1111111111; ++i) {
        str = "";
        for (int _ = 0; _ < 10 - toBinary(i).length(); ++_) {
            str += '0';
        }
        str += toBinary(i);
        
        // 0 -> ( 
        // 1 -> )
        replace(str.begin(), str.end(), '0', '(');
        replace(str.begin(), str.end(), '1', ')');
        sum = 0;
        for (int j=0; j<10; ++j) {
            if (str[j]=='(') sum++;
            else sum--;
            
            if (sum < 0) break;
            if (j == 9 && sum == 0) {
                cout << str + ' ';
                counter++;
                if (counter % 5 == 0) cout << '\n';
            }
        }
    }

    cout << "\n\nВсего комбинаций: " << counter << '\n';
}

void t7() {
    cout << "96. Игра \"быки и коровы\"\nПравила:\nПопытайтесь угадать комбинацию из 4 разных чисел за наименьшее число ходов\n+ -> угадано число и позиция\n- -> число есть в ответе\n";
    string numbers = "0123456789";
    string answer = "0000";
    string guess = "";
    int index = 0;
    counter = 0;

    // generate answer
    for (int i=0; i<4; ++i) {
        index = (double) rand()*numbers.length() / RAND_MAX;
        answer[i] = numbers[index];
        numbers.erase(index, 1);
    }

    // guess loop
    while (guess != answer) {
        cout << "\n> ";
        cin >> guess;
        
        if (guess.length() == 4) {
            counter++;

            cout << "  ";
            for (int i=0; i<4; ++i) {
                if (guess[i] == answer[i]) cout << G << "+" << W;
                else if (answer.find(guess[i], 0) != string::npos) cout << Y << "-" << W;
                else cout << ' ';
            }

            cout << '\n';
        } 
        else if (guess == "0") {
            return;
        }
        else {
            cout << "Неправильный ввод!\n";
        }
    }

    cout << "\nВерно!\nНа решение ушло ходов: " << counter << '\n';
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int tasks = 7;
    void (*functions[tasks])() = {t1, t2, t3, t4, t5, t6, t7};
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
