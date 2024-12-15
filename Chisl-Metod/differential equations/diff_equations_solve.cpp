#include <iostream>

using namespace std;

double func(double x, double y) {
    return (-1)*(y*y) + (1/(x*x));
}

void Rung(int n, double x0, double y0, double x1, double* rx, double* ry) {
	double y, x, h = (x1 - x0) / n, k1, k2, k3, k4;
	rx[0] = x0; ry[0] = y0;
	x = x0;
	for (int i = 1; i <= n; i++)
	{
		k1 = func(rx[i - 1], ry[i - 1]);
		k2 = func(rx[i - 1] + h * 0.5, ry[i - 1] + k1 * h * 0.5);
		k3 = func(rx[i - 1] + h * 0.5, ry[i - 1] + k2 * h * 0.5);
		k4 = func(rx[i - 1] + h, ry[i - 1] + k3 * h);
		ry[i] = ry[i - 1] + h / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);
		x += h;
		rx[i] = x;
	//	cout <<i<< " " << rx[i] << " " << ry[i] << endl;
	}
	//cout << "_______________________________"<<endl;
}

void method(int n, double x0, double y0, double x1, double* tx, double* ty, void
(*M) (int, double, double, double, double*, double*), double eps) {
	M(n, x0, y0, x1, tx, ty);
	double sy, fy = ty[n];
	int k = 0;
	while (fabs(sy - fy) > eps) {
		k++;
		n = n * 2;
		sy = fy;
		delete[] ty;
		delete[] tx;
		tx = new double[n + 1];
		ty = new double[n + 1];
		M(n, x0, y0, x1, tx, ty);
		fy = ty[n];
	}

	cout.width(5); cout << " x";
	cout.width(12); cout << " y" << endl;

	cout.width(5); cout << tx[n];
	cout.width(12); cout << ty[n] << endl;

	cout << "Количество итераций: " << k << endl;

}

int main() {
    setlocale(LC_ALL, "Russian");

	int n = 2;
	double x0 = 1, y0 = 1, x1 = 2, eps = 1E-6;
	double* tx = new double[n + 1];
	double* ty = new double[n + 1];

	cout << "Метод Рунгe-Кутта" << endl;

	method(n, x0, y0, x1, tx, ty, Rung, eps);

}