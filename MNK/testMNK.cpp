#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

int main() {
    double x[10] = { 66, 58, 73, 82, 81, 84, 55, 67, 81, 59 };
    double y[10] = { 133, 107, 145, 162, 163, 170, 104, 132, 159, 116 };

    // �������� ���������
    double* q = new double[10];
    double sx = 0, sy = 0, sxy = 0, sxx = 0, sx2 = 0, sy2 = 0;
    for (int i = 0; i < 10; i++) {
        sx += x[i];
        sy += y[i];
        sxx += x[i] * x[i];
        sxy += x[i] * y[i];
        sx2 += pow(x[i], 2);
        sy2 += pow(y[i], 2);
    }
    double A = (sx * sy - 10 * sxy) / (sx * sx - 10 * sxx);
    double B = (sy - A * sx) / 10;
    for (int j = 0; j < 10; j++) {
        q[j] = A * x[j] + B;
    }
    double sigm = 0;
    for (int i = 0; i < 10; i++) {
        sigm += pow(y[i] - q[i], 2);
    }                               //y[i] - q[i]  --  abs в выводе формы
    sigm = sqrt(sigm / 10);


    // ���������������� ���������
    double* qExp = new double[10];
    double s1 = 0, s2 = 0, s3 = 0, s4 = 0, syExp = 0;
    for (int i = 0; i < 10; i++)
    {
        s1 += x[i];
        s2 += log(y[i]);
        s3 += pow(x[i], 2);
        s4 += x[i] * log(y[i]);
        syExp += y[i];
    }
    double AExp = (s2 * s3 - s1 * s4) / (10 * s3 - pow(s1, 2));
    double BExp = (10 * s4 - s1 * s2) / (10 * s3 - pow(s1, 2));
    for (int j = 0; j < 10; j++) {
        qExp[j] = exp(AExp) * exp(BExp * x[j]);
    }
    double sigmExp = 0;
    for (int i = 0; i < 10; i++) {
        sigmExp += pow(y[i] - qExp[i], 2);
    }
    sigmExp = sqrt(sigmExp / 10);
    cout << "A: " << AExp << "B: " << BExp << "sigmExp: " << sigmExp;


    // ��������������� ���������
    double* qHyp = new double[10];
    double sy1x = 0, s1x = 0, syHyp = 0, s1x2 = 0;
    for (int j = 0; j < 10; j++) {
        qHyp[j] = 1 / y[j];
    }
    for (int i = 0; i < 10; i++) {
        sy1x += qHyp[i] * x[i];
        s1x += x[i];
        syHyp += qHyp[i];
        s1x2 += x[i] * x[i];
    }
    double BHyp = (10 * sy1x - s1x * syHyp) / (10 * s1x2 - pow(s1x, 2));
    double AHyp = syHyp / 10 - ((BHyp * s1x) / 10);

    double sigmHyp = 0;
    for (int i = 0; i < 10; i++) {
        qHyp[i] = 1 / (BHyp * x[i] + AHyp);
        sigmHyp += pow(y[i] - qHyp[i], 2);
    }
    sigmHyp = sqrt(sigmHyp / 10);

}