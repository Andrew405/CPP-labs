#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

double func(double x) {
    return x-cos(x);
}

double func1(double x) {
    return 1+sin(x);
}

double func2(double x) {
    return cos(x);
}

int main() {
    setlocale(LC_ALL, "RU");

    double a, b, E, x, x0 = 0;
    cout << "Введите параметры a и b, и точность E: " << endl;
    cin >> a >> b >> E;

    if (func(a)*func2(a) > 0) {
        x = a;
    }
    else {
        x = b;
    }

    for (int n = 0; abs(x-x0) > E; n++) {
        if (n > 100) {
            cout << " Корень с заданной точностью не найден! " << endl;
            break;
        }
        x0 = x;
        x = x0 - (func(x0)/func1(x0));
    }

    cout << "x = " << x << " f(x) = " << func(x) << endl;
}