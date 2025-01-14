#include <iostream>
#include <cmath>
#include <algorithm>
#include <clocale>
#include <ctime>
#include <chrono>
#include <random>
#include <vector>

using namespace std;
using namespace chrono;


void QuickSort(vector<int>& massiv, int left, int right) {
	int i = left, j = right; 
	int pivot = massiv[left]; 

	while (i <= j) {
		while (massiv[i] < pivot) {
			i++; 
        }
		while (massiv[j] > pivot) {
			j--; 
        }
		if (i <= j) { 
			int temp = massiv[i]; 
			massiv[i] = massiv[j]; 
			massiv[j] = temp; 
			i++; 
			j--; 
		} 
	} 
	if (left < j) {
		QuickSort(massiv, left, j); 
    }
	if (i < right) {
		QuickSort(massiv, i, right); 
    }
} 


vector<int> CountingSort(vector<int> massiv, int n) {
    int maximum = 0;
    for (int i = 0; i < n; i++) {
        maximum = max(maximum, massiv[i]);
    }
    vector<int> countArray(maximum + 1, 0);

    for (int i = 0; i < n; i++) {
        countArray[massiv[i]]++;
    }

    for (int i = 1; i <= maximum; i++) {
        countArray[i] += countArray[i - 1];
    }
    vector<int> outputArray(n);

    for (int i = n - 1; i >= 0; i--) {
        outputArray[countArray[massiv[i]] - 1] = massiv[i];
        countArray[massiv[i]]--;
    }
    return outputArray;
}


vector<int> CountingSortForNegative(vector<int> massiv, int n) {
    if (n < 2) return massiv;

    int low = *min_element(massiv.begin(), massiv.end());
    int high = *max_element(massiv.begin(), massiv.end());
    vector<int> result(n, 0);
    vector<int> count(high - low + 1, 0);

    for (int data : massiv)
        count[data - low] += 1;

    for (int index = 1; index < count.size(); index++)
        count[index] += count[index - 1];

    reverse(massiv.begin(), massiv.end());

    for (int data : massiv) {
        count[data - low] -= 1;
        result[count[data - low]] = data;
    }

    return result;
}


vector<double> Zeidel(vector<vector<double> > matrix, int size, double eps) {
    vector<double> previousVariableValues = {0.0, 0.0, 0.0};
    int iterations = 0;

    while (true) {
        vector<double> currentVariableValues (size);
        iterations += 1;

        for (int i = 0; i < size; i++) {
            currentVariableValues[i] = matrix[i][size];
            for (int j = 0; j < size; j++) {
                if (j < i) {
                    currentVariableValues[i] -= matrix[i][j] * currentVariableValues[j];
                }

                if (j > i) {
                    currentVariableValues[i] -= matrix[i][j] * previousVariableValues[j];
                }
            }
            currentVariableValues[i] /= matrix[i][i];
        }
 
        double error = 0.0;
        
        for (int i = 0; i < size; i++) {
            error += abs (currentVariableValues[i] - previousVariableValues[i]);
        }

        if (error < eps) {
            break;
        }
 
        previousVariableValues = currentVariableValues;
    }

    cout << "Количество итераций: " << iterations << endl;

    return previousVariableValues;
}


double Lin(vector<double> x, vector<double> y, int size) {
    vector<double> q = vector<double>(size);
    double sx = 0, sy = 0, sxy = 0, sxx = 0, sx2 = 0, sy2 = 0;
    for (int i = 0; i < size; i++) {
        sx += x[i];        
        sy += y[i];        
        sxx += x[i] * x[i];
        sxy += x[i] * y[i];
        sx2 += pow(x[i], 2);
        sy2 += pow(y[i], 2);
    }
    double A = (sx * sy - size * sxy) / (sx * sx - size * sxx);     // А линейной регрессии
    double B = (sy - A * sx) / size;      //В линейной регрессии
    for (int j = 0; j < size; j++) {
        q[j] = A * x[j] + B;
    }
    double sigm = 0;        //Среднеквадратическое отклонение линейной регрессии
    for (int i = 0; i < size; i++) {
        sigm += pow(y[i] - q[i], 2);
    }
    sigm = sqrt(sigm / size);
    cout << "ALin: " << A << " BLin: " << B << " Среднеквадратическое отклонение: " << sigm << endl;
    return sigm;
}


double Exp(vector<double> x, vector<double> y, int size) {
    vector<double> qExp = vector<double>(size);
    double s1 = 0, s2 = 0, s3 = 0, s4 = 0, syExp = 0;
    for (int i = 0; i < size; i++)
    {
        s1 += x[i];
        s2 += log(y[i]);
        s3 += pow(x[i], 2);
        s4 += x[i] * log(y[i]);
        syExp += y[i];
    }
    long double AExp = (s2 * s3 - s1 * s4) / (size * s3 - pow(s1, 2));
    long double BExp = (size * s4 - s1 * s2) / (size * s3 - pow(s1, 2));
    for (int j = 0; j < size; j++) {
        qExp[j] = exp(AExp) * exp(BExp * x[j]);
    }
    long double sigmExp = 0;         //Среднеквадратическое отклонение экспоненциальной регрессии
    for (int i = 0; i < size; i++) {
        sigmExp += pow(y[i] - qExp[i], 2);
    }
    sigmExp = sqrt(sigmExp / size);
    cout << "AExp: " << AExp << " BExp: " << BExp << " Среднеквадратическое отклонение: " << sigmExp << endl;
    return sigmExp;
}


double Hyp(vector<double> x, vector<double> y, int size) {
    vector<double> qHyp = vector<double>(size);
    double sy1x = 0, s1x = 0, syHyp = 0, s1x2 = 0;
    for (int j = 0; j < size; j++) {
        qHyp[j] = 1 / y[j];
    }
    for (int i = 0; i < size; i++) {
        sy1x += qHyp[i] * x[i];
        s1x += x[i];
        syHyp += qHyp[i];
        s1x2 += x[i] * x[i];
    }
    double BHyp = (size * sy1x - s1x * syHyp) / (size * s1x2 - pow(s1x, 2));
    double AHyp = syHyp / size - ((BHyp * s1x) / size);
    double sigmHyp = 0;         //Среднеквадратическое отклонение гиперболической регрессии
    for (int i = 0; i < size; i++) {
        qHyp[i] = 1 / (BHyp * x[i] + AHyp);
        sigmHyp += pow(y[i] - qHyp[i], 2);
    }
    sigmHyp = sqrt(sigmHyp / size);
    cout << "AHyp: " << AHyp << " BHyp: " << BHyp << " Среднеквадратическое отклонение: " << sigmHyp << endl;
    return sigmHyp;
}


int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int choice = 1;
    while (choice > 0 && choice < 4) {
        cout << "Выберите желаемый пункт из списка функций: " << endl;
        cout << "1. Сортировки" << endl;
        cout << "2. Численный метод" << endl;
        cout << "3. Метод наименьших квадратов" << endl;
        cout << "4. Выход" << endl;
        cin >> choice;

        if (choice == 1) {                                      //Сортировки
            int choice2 = 0;
            cout << "Выберите желаемый метод сортировки: " << endl;
            cout << "1. Быстрая сортировка" << endl;
            cout << "2. Сортировка подсчетом" << endl;
            cin >> choice2;

            if (choice2 == 1) {                                 //Быстрая сортировка
                int n;
                cout << "Введите размер массива: " << endl;
                cin >> n;
                vector<int> massiv(n);
                cout << "Массив: " << endl;
                for (int i = 0; i < n; i++) {
                    massiv[i] = int((rand() % 20000) - 10000);
                    cout << massiv[i] << " ";
                }
                cout << endl << endl;

                auto start = high_resolution_clock::now();
                QuickSort(massiv, 0, n-1);
                auto stop = high_resolution_clock::now();
                auto time = stop - start;

                cout << "Отсортированный массив: " << endl;
                for (int i = 0; i < n; i++) {
                    cout << massiv[i] << " ";
                }
                cout << endl << "Процессорное время: " << time.count() << endl;
            }
            else if (choice2 == 2) {                            //Сортировка подсчетом
                int choice3;
                cout << "Вариант сортировки: " << endl;
                cout << "1. Классическая сортировка подсчетом" << endl;
                cout << "2. Сортировка подсчетом включающая отрицательные числа" << endl;
                cin >> choice3;

                if (choice3 == 1) {                             //Классическая сортировка подсчетом
                    int n;
                    cout << "Введите размер массива: " << endl;
                    cin >> n;
                    vector<int> massiv(n);
                    cout << "Массив: " << endl;
                    for (int i = 0; i < n; i++) {
                        massiv[i] = int(rand() % 10000);
                        cout << massiv[i] << " ";
                    }
                    cout << endl << endl;

                    vector<int> result;
                    auto start = high_resolution_clock::now();
                    result = CountingSort(massiv, n);
                    auto stop = high_resolution_clock::now();
                    auto time = stop - start;

                    cout << "Отсортированный массив: " << endl;
                    for (int i = 0; i < n; i++) {
                        cout << result[i] << " ";
                    }
                    cout << endl << "Процессорное время: " << time.count() << endl;
                }
                else if (choice3 == 2) {                        //Сортировка подсчетом включающая отрицательные числа
                    int n;
                    cout << "Введите размер массива: " << endl;
                    cin >> n;
                    vector<int> massiv(n);
                    cout << "Массив: " << endl;
                    for (int i = 0; i < n; i++) {
                        massiv[i] = int((rand() % 20000) - 10000);
                        cout << massiv[i] << " ";
                    }
                    cout << endl << endl;

                    vector<int> result;
                    auto start = high_resolution_clock::now();
                    result = CountingSortForNegative(massiv, n);
                    auto stop = high_resolution_clock::now();
                    auto time = stop - start;

                    cout << "Отсортированный массив: " << endl;
                    for (int i = 0; i < n; i++) {
                        cout << result[i] << " ";
                    }
                    cout << endl << "Процессорное время: " << time.count() << endl;
                }
            }
        }
        else if (choice == 2) {                                 //Численный метод
            int size = 3;
            vector<vector<double>> matrix = {{41, 5.2, -5.8, 70}, 
                                             {3.8, -31, 4.0, 53},
                                             {7.8, 5.3, -63, 58}};
            cout << "Матрица коэффициентов и свободных членов: " << endl;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            double eps;
            cout << "Введите необходимую точность решения: " << endl;
            cin >> eps;

            vector<double> variables(size);
            variables = Zeidel(matrix, size, eps);

            cout << "Найденные неизвестные: " << endl;
            for (int i = 0; i < 3; i++) {
                cout << variables[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 3) {                                 //Метод наименьших квадратов
            vector<double> x = {7, 10, 15, 20, 30, 45, 60 ,120};
            vector<double> y = {10.0, 9.0, 7.5, 6.0, 6.3, 5.8, 5.4, 5.0};
            int size = x.size();
            cout << "x: ";
            for (int i = 0; i < size; i++) {
                cout << x[i] << " ";
            }
            cout << endl << "y: ";
            for (int i = 0; i < size; i++) {
                cout << y[i] << " ";
            }
            cout << endl;

            cout << "Результаты линейной регрессии: " << endl;
            double sigmLin = Lin(x, y, size);
            cout << "Результаты экспоненциальной регрессии: " << endl;
            double sigmExp = Exp(x, y, size);
            cout << "Результаты гиперболической регрессии: " << endl;
            double sigmHyp = Hyp(x, y, size);

            cout << "Под имеющиеся данные больше всего подходит модель: " << endl;
            if (sigmLin < sigmExp && sigmLin < sigmHyp) {
                cout << "Линейной регрессии" << endl;
            }
            else if (sigmExp < sigmLin && sigmExp < sigmHyp) {
                cout << "Экспоненциальной регрессии" << endl;
            }
            else if (sigmHyp < sigmLin && sigmHyp < sigmExp) {
                cout << "Гиперболической регрессии" << endl;
            }

            cout << endl << "Нажмите любую клавишу для выхода в главное меню" << endl;
            char exit;
            cin >> exit;
        }
    }
}