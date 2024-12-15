#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

double func (double x) {
    return 1/(sqrt(1+2*x*x*x));
}

double Sim (int n, double a, double b, double (*f)(double)) {
    double s = f(a) + f(b);
    double h = (b-a) / n;
    for (int i = 1; i < n; i+=2) {
        s += 4*f(a + h*i);
    }
    for (int i = 2; i < n-1; i+=2) {
        s += 2*f(a + h*i);
    }
    return s * h/3;
}

double Metod (int n1, double a1, double b1, double (*M)(int, double, double, double (* )(double)), double (*f)(double)) {
    return M(n1, a1, b1, f);
}

int main() {
    setlocale(LC_ALL, "RU");

    double a, b, eps, ln1, ln0=0, rez;
    int n;

    n = 2;
    a = 2.2;
    b = 3; 
    eps = 1e-6;

    ln1 = Metod(n, a, b, Sim, func);

    while (abs(ln1-ln0) > eps) {
        n *= 2;
        ln0 = ln1;
        ln1 = Metod(n, a, b, Sim, func);
    }

    rez = ln1;

    cout << "Результат: " << rez << endl;
}