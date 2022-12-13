#include <unordered_map>
#include <windows.h> // instead of unitstd.h
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <conio.h> // for Sleep
#include <algorithm> // for replace

using namespace std;
mutex mlock;

int score = 0;
int lines = 0;
int ticks = 0;

int figure_x = 4;
int figure_y = 0;

int figure_max_x = 22;
int figure_min_x = -2;

const int X = 19; // field length
const int Y = 21; // field heigth

int figure = 15;
int figure_next = 1;

int figure_color = 4;
int figure_next_color = 2;

const char figure_glyph = '@';

string clear_line = "";
string full_line = "";
string lower_border = " ";

//                   White      Red         Green       Yellow      Blue        Magenta     Cyan
string colors[7] = { "\033[0m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m" };

int field_colors[Y * X];
int field_colors_clear[Y * X];

string field[Y];
string field_clear[Y];

// like system("cls") but faster
void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

string getFigure(int figure) {
    unordered_map <int, string> figures;
    figures[0] = "         @ @    @ @         "; // O

    figures[1] = "       @ @ @ @              "; // I
    figures[2] = ". . @ .. . @ .. . @ .. . @ .";

    figures[3] = "           @ @  @ @         "; // S
    figures[4] = ". . @ .. . @ @. . . @. . . .";

    figures[5] = "         @ @      @ @       "; // Z
    figures[6] = ". . . @. . @ @. . @ .. . . .";

    figures[7] = "         @ @ @  @           "; // L
    figures[8] = ". . @ .. . @ .. . @ @. . . .";
    figures[9] = ". . . @. @ @ @. . . .. . . .";
    figures[10] = ". @ @ .. . @ .. . @ .. . . .";

    figures[11] = "         @ @ @      @       "; // J
    figures[12] = ". . @ @. . @ .. . @ .. . . .";
    figures[13] = ". @ . .. @ @ @. . . .. . . .";
    figures[14] = ". . @ .. . @ .. @ @ .. . . .";

    figures[15] = "         @ @ @    @         "; // T
    figures[16] = ". . @ .. . @ @. . @ .. . . .";
    figures[17] = ". . @ .. @ @ @. . . .. . . .";
    figures[18] = ". . @ .. @ @ .. . @ .. . . .";

    return figures[figure];
}

void coutField() {
    string screen = "";

    string fig = getFigure(figure_next);
    replace(fig.begin(), fig.end(), '@', figure_glyph);

    for (int y = 1; y < Y; y++) {
        // field
        screen += "\033[0m|";
        for (int x = 0; x < X; x++) screen += colors[field_colors[y * X + x]] + field[y][x];
        screen += "\033[0m|";

        // next figure
        if (y == 1) screen += " Следующая фигура: ";
        if (y > 1 && y < 5) screen += "   " + colors[figure_next_color] + fig.substr((y - 2) * 7, 7);

        if (y == 19) screen += " Линий: " + to_string(lines);
        if (y == 20) screen += " Счёт: " + to_string(score);

        screen += "\r\n";
    }

    screen += lower_border;
    cout << screen;
}

void setFigure() {
    for (int y = 0; y < Y; y++) {
        field[y] = field_clear[y];
    }

    for (int xy = 0; xy < X * Y; xy++) {
        field_colors[xy] = field_colors_clear[xy];
    }

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 7; x++) {
            if (getFigure(figure)[x + y * 7] == '@') {
                field[figure_y + y][figure_x + x] = figure_glyph;
                field_colors[figure_y * X + y * X + figure_x + x] = figure_color;
            }
        }
    }
}

void setMaxXY() {
    // max
    if (figure == 0 || figure == 2 || figure == 10 || figure == 14 || figure == 18) figure_max_x = X - 5;
    else figure_max_x = X - 7;

    // min
    if (figure == 2 || figure == 4 || figure == 6 || figure == 8 || figure == 12 || figure == 16) figure_min_x = -4;
    else if (figure == 1) figure_min_x = 0;
    else figure_min_x = -2;

    // x normalization, especially when rotating
    if (figure_x < figure_min_x) figure_x = figure_min_x;
    if (figure_x > figure_max_x) figure_x = figure_max_x;
}

void rotate() {
    int figure_heap = figure;
    int figure_x_heap = figure_x;
    int figure_y_heap = figure_y;

    //                    O  I     S     Z     L            J               T
    int rotations[19] = { 0, 2, 1, 4, 3, 6, 5, 10, 7, 8, 9, 14, 11, 12, 13, 18, 15, 16, 17 };
    figure = rotations[figure];

    // if rotate is not possible
    setMaxXY();
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 7; x++) {
            if (getFigure(figure)[x + y * 7] == '@' && (field_clear[figure_y + y][figure_x + x] == figure_glyph || figure_y + y > Y - 1)) {
                figure = figure_heap;
                figure_x = figure_x_heap;
                figure_y = figure_y_heap;
                setMaxXY();
                return;
            }
        }
    }
}

void move(int direction) {
    if (figure_x + direction < figure_min_x || figure_x + direction > figure_max_x) return;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 7; x++) {
            if (getFigure(figure)[x + y * 7] == '@' && (field_clear[figure_y + y][figure_x + x + direction] == figure_glyph)) {
                return;
            }
        }
    }

    figure_x += direction;
}

void checkCollision() {
    int figures_id[6] = { 0, 1, 3, 5, 11, 15 };
    bool clip = false;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 7; x++) {
            if (getFigure(figure)[x + y * 7] == '@' && (figure_y + y == Y - 1 || field_clear[figure_y + y + 1][figure_x + x] == figure_glyph)) {
                clip = true;
                break;
            }
        }
    }

    if (!clip) return;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 7; x++) {
            if (getFigure(figure)[x + y * 7] == '@') {
                if (field_clear[figure_y + y][figure_x + x] == figure_glyph) {
                    setCursorPosition(0, 0);
                    coutField();

                    cout << "  Игра окончена\r\n";
                    exit(0);
                }

                field_clear[figure_y + y][figure_x + x] = figure_glyph;
                field[figure_y + y][figure_x + x] = figure_glyph;

                field_colors_clear[figure_y * X + y * X + figure_x + x] = figure_color;
            }
        }
    }

    figure_x = (X + 1) / 2 - 4;
    if (figure_x % 2 != 0) figure_x++;

    figure_y = 0;

    figure = figure_next;

    figure_next = rand() % 6;
    figure_next = figures_id[figure_next];

    figure_color = figure_next_color;
    figure_next_color = rand() % 7;
}

void checkLines() {
    for (int y = Y; y > 0; y--) {
        if (field_clear[y] == full_line) {
            score += 10;
            lines++;
            field_clear[y] = clear_line;

            for (int yy = y - 1; yy > 0; yy--) {
                for (int x = 0; x < X; x++) {
                    field_colors_clear[(yy + 1) * X + x] = field_colors_clear[yy * X + x];
                }
                field_clear[yy + 1] = field_clear[yy];
            }
            break;
        }
    }
}

void updateBoard() {
    setCursorPosition(0, 0);
    setMaxXY();
    checkLines();
    setFigure();
    coutField();

    cout << "\r\n";
    // debug
    // cout << "input: " << input << " x,y: " << figure_y << ", " << figure_x << "\r\n";
    // cout << "figure: " << figure << "\r\n";
    // cout << "ticks: " << ticks;
}

bool block = false;
void yIncrease() {
    while (true) {
        Sleep((750000 - 250 * score) / 1000); // 1 000 000 - 1 sec
        mlock.lock();

        checkCollision();
        figure_y++;
        ticks++;
        if (ticks % 10 == 0) score += 1;

        updateBoard();
        mlock.unlock();
    }
}

void gameLoop() {
    int input = -1;
    while (true) {
        // check input
        input = -1;
        input = _getch();
        mlock.lock();

        if (input == 27) exit(0);  // esc

        if (input == 115) {        // s
            checkCollision();
            figure_y++;
            ticks++;
            if (ticks % 10 == 0) score += 1;
        }

        if (input == 97) move(-2); // a
        if (input == 100) move(2); // d
        if (input == 32) rotate(); // space

        updateBoard();
        mlock.unlock();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    // generate lines
    for (int x = 0; x < X; x++) {
        clear_line += " ";
        full_line += (x % 2 == 0) ? &figure_glyph : " ";
        lower_border += "-";
    }

    // generate fields
    for (int y = 0; y < Y; y++) {
        field[y] = clear_line;
        field_clear[y] = clear_line;
    }

    // generate colors
    for (int xy = 0; xy < X * Y; xy++) {
        field_colors[xy] = 0;
        field_colors_clear[xy] = 0;
    }

    srand(time(NULL));

    thread thr1(yIncrease);
    thread thr2(gameLoop);

    thr1.join();
    thr2.join();
}
