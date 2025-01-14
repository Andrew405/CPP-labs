#include <iostream>
#include <cmath>
#include <locale>

using namespace std;

struct Figure
{
    bool circle;
    double x0;
    double y0;
    double w;
    double h;
    double R;
};

// Проверка координат внутри фигуры

bool inFigure(const Figure& Figure, double x, double y){
    if (Figure.circle){
        double distance = sqrt(pow(x - Figure.x0, 2) + pow(y - Figure.y0, 2));
        return  distance <= Figure.R;
    }
    else{
        return x >= Figure.x0 - Figure.w / 2 && x <= Figure.x0 + Figure.w / 2 && y >= Figure.y0 - Figure.h / 2 && y <= Figure.y0 + Figure.h / 2;
    }
}

bool inFigures(const Figure& A, const Figure& B, const Figure& C, const Figure& D, double x, double y){
    bool inBorD = inFigure(B, x, y) || inFigure(D, x, y);
    return (!inFigure(A, x, y) && inBorD) || inFigure(C, x, y);
}

// Функция для ввода данных о фигуре
void inputFigure(Figure& fig) {
    cout << "Выберите тип фигуры (0 - Прямоугольник, 1 - Круг): ";
    cin >> fig.circle;
    cout << "Введите координаты фигуры (x0 y0): ";
    cin >> fig.x0 >> fig.y0;
    if (!fig.circle) {
        cout << "Введите ширину и высоту прямоугольника (w h): ";
        cin >> fig.w >> fig.h;
    } else {
        cout << "Введите радиус круга (R): ";
        cin >> fig.R;
    }
}

int main(){
    setlocale(LC_ALL, "ru");

    Figure A, B, C, D;
    double x, y;
    int choice = 0;

    cout << "Введите данные первой фигуры:\n";
    inputFigure(A);
    cout << "Введите данные второй фигуры:\n";
    inputFigure(B);
    cout << "Введите данные третьей фигуры:\n";
    inputFigure(C);
    cout << "Введите данные четвертой фигуры:\n";
    inputFigure(D);

    while (choice != 2) {
        cout << "Выберите действие\n";
        cout << "1. Ввести координаты точки и проверить её принадлежность множеству.\n";
        cout << "2. Выход\n";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Выберите координаты точки: ";
                cin >> x >> y;
                if (inFigures(A, B, C, D, x, y)){
                    cout << "Точка внутри фигуры\n";
                }
                else{
                    cout << "Точка не внутри фигуры\n";
                }
                break;
            case 2:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Некорректный ввод. Попытайтесь ещё раз.\n";
        }
    
    }
}
