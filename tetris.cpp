#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <map>

// c++ tetris.cpp -std=c++11 -o tetris && ./tetris
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

bool block_update = false;

string clear_line = ". . . . . . . . . .";
string full_line = "@ @ @ @ @ @ @ @ @ @";

// field to display
string field[Y] = {
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . ."
};

// main field
string field_clear[Y] = {
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . .",
    ". . . . . . . . . ."
};

string getFigure(int figure) {
    map <int, string[4]> figures;
    figures[0][0] = ". . . .";
    figures[0][1] = ". @ @ .";
    figures[0][2] = ". @ @ .";
    figures[0][3] = ". . . .";

    figures[1][0] = ". . . ."; figures[2][0] = ". . @ .";
    figures[1][1] = "@ @ @ @"; figures[2][1] = ". . @ .";
    figures[1][2] = ". . . ."; figures[2][2] = ". . @ .";
    figures[1][3] = ". . . ."; figures[2][3] = ". . @ .";

    figures[3][0] = ". . . ."; figures[4][0] = ". . @ .";
    figures[3][1] = ". . @ @"; figures[4][1] = ". . @ @";
    figures[3][2] = ". @ @ ."; figures[4][2] = ". . . @";
    figures[3][3] = ". . . ."; figures[4][3] = ". . . .";
    
    figures[5][0] = ". . . ."; figures[6][0] = ". . . @";
    figures[5][1] = ". @ @ ."; figures[6][1] = ". . @ @";
    figures[5][2] = ". . @ @"; figures[6][2] = ". . @ .";
    figures[5][3] = ". . . ."; figures[6][3] = ". . . .";
    
    figures[7][0] = ". . . ."; figures[8][0] = ". . @ ."; figures[9][0] = ". . . @"; figures[10][0] = ". @ @ ."; 
    figures[7][1] = ". @ @ @"; figures[8][1] = ". . @ ."; figures[9][1] = ". @ @ @"; figures[10][1] = ". . @ ."; 
    figures[7][2] = ". @ . ."; figures[8][2] = ". . @ @"; figures[9][2] = ". . . ."; figures[10][2] = ". . @ ."; 
    figures[7][3] = ". . . ."; figures[8][3] = ". . . ."; figures[9][3] = ". . . ."; figures[10][3] = ". . . ."; 

    figures[11][0] = ". . . ."; figures[12][0] = ". . @ @"; figures[13][0] = ". @ . ."; figures[14][0] = ". . @ .";
    figures[11][1] = ". @ @ @"; figures[12][1] = ". . @ ."; figures[13][1] = ". @ @ @"; figures[14][1] = ". . @ .";
    figures[11][2] = ". . . @"; figures[12][2] = ". . @ ."; figures[13][2] = ". . . ."; figures[14][2] = ". @ @ .";
    figures[11][3] = ". . . ."; figures[12][3] = ". . . ."; figures[13][3] = ". . . ."; figures[14][3] = ". . . .";

    figures[15][0] = ". . . ."; figures[16][0] = ". . @ ."; figures[17][0] = ". . @ ."; figures[18][0] = ". . @ .";
    figures[15][1] = ". @ @ @"; figures[16][1] = ". . @ @"; figures[17][1] = ". @ @ @"; figures[18][1] = ". @ @ .";
    figures[15][2] = ". . @ ."; figures[16][2] = ". . @ ."; figures[17][2] = ". . . ."; figures[18][2] = ". . @ .";
    figures[15][3] = ". . . ."; figures[16][3] = ". . . ."; figures[17][3] = ". . . ."; figures[18][3] = ". . . .";
    

    return figures[figure][0] + figures[figure][1] + figures[figure][2] + figures[figure][3];
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
            for (int i = 0; i < 27; i++) {
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

    // if rotate possible
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
    if (figure_x + direction < figure_min_x || figure_x > figure_max_x) return;

    for (int y=0; y<4; y++) {
        for (int x=0; x<7; x++) {
            if (getFigure(figure)[x+y*7] == '@' && field_clear[figure_y+y][figure_x+x+direction] == '@') {
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
            if (getFigure(figure)[x+y*7] == '@' && (field_clear[figure_y+y+1][figure_x+x] == '@' || figure_y+y == 19)) {
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

void yIncrease() {
    while (true) {
        sleep(1);
        if (!block_update) {
            checkCollision();

            ticks++;
            figure_y++;

            if (ticks%10==0) score += 1;

            updateBoard();
            block_update = false;
        }
    }
}

void gameLoop() {
    while (true) {
        updateBoard();

        // check input
        input = -1;
        block_update = false;
        input = getchar();
        block_update = true;
        
        if (input == 27) exit(0); // esc

        if (input == 115) {       // s
            checkCollision();
            figure_y++;
            ticks++;
            if (ticks%10==0) score += 1;
        }

        if (input == 97) move(-2); // a
        if (input == 100) move(2); // d
        if (input == 32) rotate(); // space
    }
}

int main() {
    system("/bin/stty raw");

    thread thr1(yIncrease);
    thread thr2(gameLoop);
    
    thr1.join();
    thr2.join();
}
