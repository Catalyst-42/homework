#include <unordered_map>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <mutex>

// c++ tetris.cpp -std=c++11 -o tetris && ./tetris

std::mutex mlock;
using namespace std;

int score = 0;
int ticks = 0;

int figure_x = 4;
int figure_y = 0;

int figure_max_x = 22;
int figure_min_x = -2;

const int X = 19;
const int Y = 20;

int figure = 15;
int figure_next = 1;

int input = -1;
int figures_id[6] = {0, 1, 3, 5, 11, 15};

string clear_line = ". . . . . . . . . .";
string full_line = "@ @ @ @ @ @ @ @ @ @";

// field to display
string field[Y] = {
    ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ."
};

// main field
string field_clear[Y] = {
    ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ."
};

string getFigure(int figure) {
    unordered_map <int, string> figures;
    figures[0] = ". . . .. @ @ .. @ @ .. . . ."; // O

    figures[1] = ". . . .@ @ @ @. . . .. . . ."; // I
    figures[2] = ". . @ .. . @ .. . @ .. . @ .";

    figures[3] = ". . . .. . @ @. @ @ .. . . ."; // S
    figures[4] = ". . @ .. . @ @. . . @. . . .";

    figures[5] = ". . . .. @ @ .. . @ @. . . ."; // Z
    figures[6] = ". . . @. . @ @. . @ .. . . .";

    figures[7] = ". . . .. @ @ @. @ . .. . . ."; // L
    figures[8] = ". . @ .. . @ .. . @ @. . . ."; 
    figures[9] = ". . . @. @ @ @. . . .. . . ."; 
    figures[10] = ". @ @ .. . @ .. . @ .. . . ."; 

    figures[11] = ". . . .. @ @ @. . . @. . . ."; // J
    figures[12] = ". . @ @. . @ .. . @ .. . . ."; 
    figures[13] = ". @ . .. @ @ @. . . .. . . ."; 
    figures[14] = ". . @ .. . @ .. @ @ .. . . .";

    figures[15] = ". . . .. @ @ @. . @ .. . . ."; // T
    figures[16] = ". . @ .. . @ @. . @ .. . . ."; 
    figures[17] = ". . @ .. @ @ @. . . .. . . ."; 
    figures[18] = ". . @ .. @ @ .. . @ .. . . .";

    return figures[figure];
}

void coutField() {
    string fig = getFigure(figure_next);
    for (int y = 0; y < Y; y++) {
        // borders
        cout << '|' << field[y] << '|';

        if (y == 0) cout << " Следующая фигура: ";
        
        // next figure
        if (y > 0 && y < 4) {
            cout << "   ";
            for (int i = 0; i < 7; i++) {
                if (fig.substr((y-1)*7, 7)[i] == '@') cout << '@';
                else cout << ' ';
            }
        }
        
        if (y == 19) cout << " Счёт: " << score;
        
        // lower border
        if (y == Y-1) {
            cout << "\r\n ";
            for (int x = 0; x < X; x++) {
                cout << '-';
            }
        }

        cout << "\r\n" << flush;
    }
}

void setFigure() {
    for (int y=0; y<Y; y++) {
        field[y] = field_clear[y];
    }

    for (int y=0; y<4; y++) {
        for (int x=0; x<7; x++) {
            if (getFigure(figure)[x+y*7] == '@') {
                field[figure_y+y][figure_x+x] = '@';
            }
        }
    }
}

void setMaxXY() {
    if (figure == 1) { 
        figure_min_x = 0; figure_max_x = 12; 
    }
    
    if (figure == 2) { 
        figure_min_x = -4; figure_max_x = 14;
    }
        
    if (figure == 3 || figure == 5 || figure == 7 || figure == 9 || figure == 11 || figure == 13 || figure == 15 || figure == 17) { 
        figure_min_x = -2; figure_max_x = 12; 
    }
    
    if (figure == 8 || figure == 12 || figure == 16 || figure == 4 || figure == 6) { 
        figure_min_x = -4; figure_max_x = 12; 
    }
    
    if (figure == 0 || figure == 10 || figure == 14 || figure == 18) { 
        figure_min_x = -2; figure_max_x = 14; 
    }

    // x normalization, especially when rotating
    if (figure_x < figure_min_x) figure_x = figure_min_x;
    if (figure_x > figure_max_x) figure_x = figure_max_x;
}

void rotate() {
    int figure_heap = figure;
    int figure_x_heap = figure_x;
    int figure_y_heap = figure_y;

    if (figure == 1) { figure = 2; } 
    else if (figure == 2) { figure = 1; }

    else if (figure == 3) { figure = 4; } 
    else if (figure == 4) { figure = 3; }

    else if (figure == 5) { figure = 6; }
    else if (figure == 6) { figure = 5; }

    else if (figure == 7) { figure = 10; }
    else if (figure > 7 && figure <= 10) { figure--; }

    else if (figure == 11) { figure = 14; }
    else if (figure > 11 && figure <= 14)  { figure = --figure; }

    else if (figure == 15) { figure = 18; }
    else if (figure > 15 && figure <= 18) { figure = --figure; }

    // if rotate is possible
    setMaxXY();
    for (int y=0; y<4; y++) {
        for (int x=0; x<7; x++) {
            if (getFigure(figure)[x+y*7] == '@' && field_clear[figure_y+y][figure_x+x] == '@') {
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

    for (int y=0; y<4; y++) {
        for (int x=0; x<7; x++) {
            if (getFigure(figure)[x+y*7] == '@' && (field_clear[figure_y+y][figure_x+x+direction] == '@')) {
                return;
            }
        }
    }

    figure_x += direction;
}

void checkCollision() {
    bool clip = false;
    for (int y=0; y<4; y++) {
        for (int x=0; x<7; x++) {
            if (getFigure(figure)[x+y*7] == '@' && (figure_y+y == 19 || field_clear[figure_y+y+1][figure_x+x] == '@')) {
                clip = true;
                break;
            }
        }
    }

    if (clip) {
        for (int y=0; y<4; y++) {
            for (int x=0; x<7; x++) {
                if (getFigure(figure)[x+y*7] == '@') {
                    if (field_clear[figure_y+y][figure_x+x] == '@') {
                        system("clear");
                        setFigure();
                        coutField();

                        cout << "Игра окончена\r\n";
                        system ("/bin/stty cooked");
                        exit(0);
                    }

                    field_clear[figure_y+y][figure_x+x] = '@';
                    field[figure_y+y][figure_x+x] = '@';

                }
            }
        }
        
        figure_x = 6;
        figure_y = 0;

        figure = figure_next;

        figure_next = rand() % 6;
        figure_next = figures_id[figure_next];
    }

}

void checkLines() {
    for (int y=Y; y>0; y--) {
        if (field_clear[y] == full_line) {
            score += 10;
            field_clear[y] = clear_line;
            for (int yy=y-1; yy > 0; yy--) {
                field_clear[yy+1] = field_clear[yy];
            }
            break;
        }
    }
}

void updateBoard() {
    system("clear");
    setMaxXY();
    checkLines();
    setFigure();
    coutField();

    cout << "\r\n";
    // debug
    // cout << "input: " << input << " x,y: " << figure_y << ", " << figure_x << "\r\n";
    // cout << "figure: " << figure << "\r\n";
    // cout << "ticks: " << ticks << flush;
}

bool block = false;
void yIncrease() {
    while (true) {
        sleep(1);
        mlock.lock();

        checkCollision();

        ticks++;
        figure_y++;
        if (ticks%10==0) score += 1;

        updateBoard();
        mlock.unlock();
    }
}

void gameLoop() {
    while (true) {
        updateBoard();

        // check input
        input = -1;
        input = getchar();
        mlock.lock();
        
        if (input == 27) exit(0);  // esc

        if (input == 115) {        // s
            checkCollision();
            figure_y++;
            ticks++;
            if (ticks%10==0) score += 1;
        }

        if (input == 97) move(-2); // a
        if (input == 100) move(2); // d
        if (input == 32) rotate(); // space

        mlock.unlock();
    }
}

int main() {
    srand(time(NULL));
    system("/bin/stty raw");

    thread thr1(yIncrease);
    thread thr2(gameLoop);
    
    thr1.join();
    thr2.join();
}
