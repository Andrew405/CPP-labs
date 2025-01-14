#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace std;

bool var5(bool const a, bool const b, bool const c, bool const d, bool const e) {
	return (a && !b && !c) || (d && !e);
}

void printTruthTable() {
	vector<int>sdnf;
	vector<int>sknf;
	vector<string>headers = { "a", "b", "c", "d", "e", "f" };

	cout << "Таблица истинности:" << endl;

	for (const string& header : headers) {
		cout << header << " ";
	}
	cout << endl;

	for (int a = 0; a <= 1; a++) {
		for (int b = 0; b <= 1; b++) {
			for (int c = 0; c <= 1; c++) {
				for (int d = 0; d <= 1; d++) {
					for (int e = 0; e <= 1; e++) {
						cout << a << " " << b << " " << c << " " << d << " " << e << " ";
						cout << var5(a, b, c, d, e) << endl;
						if (var5(a, b, c, d, e)) {
							sdnf.push_back(a);
							sdnf.push_back(b);
							sdnf.push_back(c);
							sdnf.push_back(d);
							sdnf.push_back(e);
						}
						else {
							sknf.push_back(a);
							sknf.push_back(b);
							sknf.push_back(c);
							sknf.push_back(d);
							sknf.push_back(e);
						}
					}
				}
			}
		}
	}

	cout << "СДНФ:\n" << endl;
	for (int i = 0; i < sdnf.size(); i += 5) {
		cout << "(";
		for (int j = 0; j < 5; j++) {
			if (sdnf[i + j] == 0)
				cout << "!" << headers[j];
			else
				cout << headers[j];
			if (j != 4) cout << " && ";
		}
		cout << ")";
		if (i != sdnf.size() - 5) cout << " || ";
	}
	cout << endl;

	cout << "СКНФ:\n" << endl;
	for (int i = 0; i < sknf.size(); i += 5) {
		cout << "(";
		for (int j = 0; j < 5; j++) {
			if (sknf[i + j] == 1)
				cout << "!" << headers[j];
			else
				cout << headers[j];
			if (j != 4) cout << " || ";
		}
		cout << ")";
		if (i != sknf.size() - 5) cout << " && ";
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	cout << "5 вариант:" << endl;
	printTruthTable();
	return 0;
}