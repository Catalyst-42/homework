#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

void t1() {
    // V = 1/3πh(R2+Rr+r2)
    // S = π(R2+(R+r)l+r2)

    double h = 0;
    double l = 0;
    double r = 0;
    double R = 0;

    cout << "Enter the parameters of the cone (h,l,r,R): ";
    cin >> h >> l >> r >> R;

    cout << "V = " << (double) 1/3 * M_PI*h*(R*R + R*r + r*r) << endl;
    cout << "S = " << (double) M_PI*(R*R + (R+r)*l + r*r) << endl;
}

void t2() {
    double a = 0;
    double x = 0;
    double w = 0;

    bool error = false;

    cout << "Enter the parameters (x,a): ";
    cin >> x >> a;

    if (abs(x) < 1) {
        if (x != 0) {
            w = a * log(abs(x));
        } 
        else {
            // ln(0)
            cout << "w can't be found, (ln of zero)" << endl;
            error = true;
        }
    } 
    else {
        if (a - x*x > 0) {
            w = sqrt(a - x*x);
        } 
        else {
            // root(x < 0)
            cout << "w can't be found, (root of negative number)" << endl;
            error = true;
        }
    }

    if (!error) {
        cout << "w = " << w << endl;
    }
}

void t3() {
    double x, y, b;
    // z = ln(b - y) * sqrt(b - x)

    cout << "Enter the parameters (x,y,b): ";
    cin >> x >> y >> b;

    if (b-y <= 0) {
        cout << "z can't be found, (ln(x) from x <= 0)" << endl;
    } 
    else if (b - x < 0) {
        cout << "z can't be found, (sqrt() from negative number)" << endl;
    }
    else {
        cout << "z = " << log(b - y) * sqrt(b - x);
    }
}

void t4() {
    int N;

    cout << "enter N: ";
    cin >> N;

    if (N < 1) {
        N = 1;
    }

    for (int n=N; n<N+10; n++) {
        cout << n << " ";
    }
    
    cout << endl;
}

 
void t5() {
    for (double x = -4; x <= 4; x += 0.5) {
        if (x - 1 != 0 ) {
            cout  << "x = " << setw(7) << left << x;
            cout << "y = " << (x*x - 2*x + 2) / (x - 1) << endl;
        }
        else {
            cout  << "x = " << setw(7) << left << x;
            cout << "no answer (division by zero)" << endl;
        }
    }
}

int main() {
    cout << "Task 1" << endl, t1();
    cout << "Task 2" << endl, t2();
    cout << "Task 3" << endl, t3();
    cout << "Task 4" << endl, t4();
    cout << "Task 5" << endl, t5();
}
