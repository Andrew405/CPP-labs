#include <iostream>
#include <ctime>
#include <vector>
#include <clocale>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

// int random(int a,int b){
//     if (a > 0) {
//         return a + rand() % (b - a);
//     }
//     else {
//         return a + rand() % (abs(a) + b);
//     }
// }

int Bubble_sort(vector<int>& mass) {
    int count = 0;
    for (int j = 1; j < mass.size(); j++){
        bool sorted = true;
        for (size_t i = 0; i < mass.size() - j; i++) {
            if (mass[i] > mass[i+1]) {
                count+=1;
                int x = mass[i];
                mass[i] = mass[i+1];
                mass[i+1] = x;
                count+=3;
                sorted = false;
            }
        }
        if (sorted){
            break;
        }
    }
    return count;
}

int Shell_sort(vector<int>& mass) {
    int count = 0;
    size_t n = mass.size();
    for(int step = n/2; step > 0; step /= 2) {
        for (int i = step; i < n; i += 1) {   
            int j = i;
            count+=1;
            while(j >= step && mass[j - step] > mass[i]){
                int x = mass[j];
                mass[j] = mass[j - step];
                mass[j - step] = x;
                j-=step; 
                count+=5;
            }    
        }   
    }  
    return count; 
}

int Mixer_sort(vector<int>& mass) {
    int count = 0;
    size_t leftExchange = 0;
    size_t rightExchange = mass.size() - 1;
    int control = mass.size() - 1;
    count += 3;
    while (leftExchange < rightExchange) {
        bool sorted = true;
        for (size_t i = leftExchange; i < rightExchange; i++) {
            if (mass[i] > mass[i+1]) {
                int x = mass[i];
                mass[i] = mass[i+1];
                mass[i+1] = x;
                control = i;
                count += 5;
                sorted = false;
            }
        }
        rightExchange = control;
        count += 1;
        if (sorted){
            count += 1;
            break;
        }
        for (size_t i = rightExchange; i > leftExchange; i--) {
            if (mass[i] < mass[i-1]) {
                int x = mass[i];
                mass[i] = mass[i-1];
                mass[i-1] = x;
                control = i;
                count+=5;
            }
        }
        leftExchange = control;
        count+=1;
    }
    return count;
}

int mainTest() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    int sizeA;
    cin >> sizeA;
    vector<int> A;

    cout << "Массив А: " << endl;

    for(size_t i = 0; i < sizeA; i++) {
        A.push_back(int((rand() % 20000) - 10000));
        cout << A[i] << " "/*<< endl*/;
    }

    Bubble_sort(A);

    cout << endl << "Отсортированный пузырьком массив A: " << endl;
    for(size_t i = 0; i < sizeA; i++) {
        cout << A[i];
        cout << " ";
    }
    cout << endl;

    int sizeB;
    cin >> sizeB;
    vector<int> B;

    cout << "Массив B: " << endl;

    for (size_t i = 0; i < sizeB; i++) {
        B.push_back(int((rand() % 20000) - 10000));
        cout << B[i];
        cout << " ";
    }

    Shell_sort(B);

    cout << endl << "Отсортиррованный Шеллом массив B: " << endl;
    for (size_t i = 0; i < sizeB; i++) {
        cout << B[i];
        cout << " ";
    }

    int minB = B[0];
    int maxA = A[sizeA-1];

    vector<int> C;
    for(size_t i = 0; i < sizeA; i++) {
        if (A[i] > minB) {
            C.push_back(A[i]);
        } 
    }
    for(size_t i = 0; i < sizeB; i++) {
        if (B[i] > maxA) {
            C.push_back(B[i]);
        }
    }

    int sizeC = C.size();

    cout << endl << endl << "Массив С: " << endl;
    for (size_t i = 0; i < sizeC; i++) {
        cout << C[i];
        cout << " ";
    }
    cout << endl;

    Mixer_sort(C);

    cout << "Отсортированный перемешиванием массив С: " << endl;
    for (size_t i = 0; i < sizeC; i++) {
        cout << C[i];
        cout << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    int sizeA;                  //Создание массива А
    cin >> sizeA;
    vector<int> A;

    cout << "Массив А: " << endl;
    for(size_t i = 0; i < sizeA; i++) {
        A.push_back(int((rand() % 20000) - 10000));
        cout << A[i] << " "/*<< endl*/;
    }
    cout << endl;

    int sizeB;                  //Создание массива В
    cin >> sizeB;
    vector<int> B;

    cout << "Массив B: " << endl;
    for (size_t i = 0; i < sizeB; i++) {
        B.push_back(int((rand() % 20000) - 10000));
        cout << B[i];
        cout << " ";
    }
    cout << endl;

    vector<int> A2 = A;
    vector<int> B2 = B;

    Bubble_sort(A2);
    Bubble_sort(B2);

    int minB = B2[0];
    int maxA = A2[sizeA-1];

    vector<int> C;              //Создание массива С
    for(size_t i = 0; i < sizeA; i++) {
        if (A[i] > minB) {
            C.push_back(A[i]);
        } 
    }
    for(size_t i = 0; i < sizeB; i++) {
        if (B[i] < maxA) {
            C.push_back(B[i]);
        }
    }

    int sizeC = C.size();

    cout << endl << endl << "Массив С: " << endl;
    for (size_t i = 0; i < sizeC; i++) {
        cout << C[i];
        cout << " ";
    }
    cout << endl;

    vector<int> C2 = C;

    auto startBubble = high_resolution_clock::now();
    Bubble_sort(C2);
    auto stopBubble = high_resolution_clock::now();
    C2 = C;
    long int complexBubble = Bubble_sort(C2);
    auto durationBubble = (stopBubble-startBubble);

    cout << endl << "Отсортированный пузырьком массив C: " << endl;
    for(size_t i = 0; i < sizeC; i++) {
        cout << C2[i];
        cout << " ";
    }
    cout << endl;
    cout << "Время: " << durationBubble.count() << endl << "Количество операций: " << complexBubble << endl;

    C2 = C;

    auto startShell = high_resolution_clock::now();
    Shell_sort(C2);
    auto stopShell = high_resolution_clock::now();
    C2 = C;
    long int complexShell = Shell_sort(C2);
    auto durationShell = (stopShell-startShell);

    cout << endl << "Отсортиррованный Шеллом массив C: " << endl;
    for (size_t i = 0; i < sizeC; i++) {
        cout << C2[i];
        cout << " ";
    }
    cout << endl;
    cout << "Время: " << durationShell.count() << endl << "Количество операций: " << complexShell << endl;

    C2 = C;

    auto startMixer = high_resolution_clock::now();
    Mixer_sort(C2);
    auto stopMixer = high_resolution_clock::now();
    C2 = C;
    long int complexMixer = Mixer_sort(C2);
    auto durationMixer = (stopMixer-startMixer);

    cout << "Отсортированный перемешиванием массив С: " << endl;
    for (size_t i = 0; i < sizeC; i++) {
        cout << C2[i];
        cout << " ";
    }
    cout << endl;
    cout << "Время: " << durationMixer.count() << endl << "Количество операций: " << complexMixer;
}