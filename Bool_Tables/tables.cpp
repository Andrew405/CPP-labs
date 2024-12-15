#include <iostream>

using namespace std;

int main() {
    bool a, b, c, d, e, F;

    cout << "| e d c b a | F |" << endl;

    cout << "SDNF: ";

    for (int i = 0; i < 32; i++){
        a = i       & 0xF1;
        b = (i>>1)  & 0xF1;
        c = (i>>2)  & 0xF1;
        d = (i>>3)  & 0xF1;
        e = (i>>4)  & 0xF1;

        F = (a && !b && !c) || (d && !e);

        if (F == 1){
            cout << "| " << e << " " << d << " " << c << " " << b << " " << a << " | " << F << " |  || ";
        }
    }
    cout << endl;
    cout << "SKNF: ";

    for (int i = 0; i < 32; i++){
        a = i       & 0xF1;
        b = (i>>1)  & 0xF1;
        c = (i>>2)  & 0xF1;
        d = (i>>3)  & 0xF1;
        e = (i>>4)  & 0xF1;

        F = (a && !b && !c) || (d && !e);

        if (F == 0) {
            cout << "| " << e << " " << d << " " << c << " " << b << " " << a << " | " << F << " |  && ";
        }
        
    }

    return 0;
}