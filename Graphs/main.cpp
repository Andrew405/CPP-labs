#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;

public:
    void readAdjacencyMatrixFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Failed to open file.");
        }

        string line;
        while (getline(file, line)) {
            vector<int> row;
            istringstream iss(line);
            int value;
            while (iss >> value) {
                row.push_back(value);
            }
            adjacencyMatrix.push_back(row);
        }
        file.close();
    }

    void readAdjacencyMatrixFromConsole() {
        cout << "Enter adjacency matrix row by row, press Enter after each row.\n";
        string input;
        while (true) {
            getline(cin, input);
            if (input.empty()) {
                break;
            }
            vector<int> row;
            for (char c : input) {
                if (c == '0' || c == '1') {
                    row.push_back(c - '0');
                } else {
                    throw runtime_error("Invalid input format");
                }
            }
            adjacencyMatrix.push_back(row);
        }
    }

    void printAdjacencyMatrix() const {
        cout << "Adjacency Matrix:\n";
        for (const auto& row : adjacencyMatrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    map<char, vector<char>> adjacencyList() const {
        map<char, vector<char>> adjList;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            char vertex = 'A' + i;
            adjList[vertex] = vector<char>();
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                if (adjacencyMatrix[i][j] == 1) {
                    adjList[vertex].push_back('A' + j);
                }
            }
        }
        return adjList;
    }

    vector<vector<int>> incidenceMatrix() const {
        size_t numVertices = adjacencyMatrix.size();
        size_t numEdges = 0;
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = i; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] == 1) {
                    numEdges++;
                }
            }
        }

        vector<vector<int>> incMatrix(numVertices, vector<int>(numEdges, 0));

        size_t edgeIndex = 0;
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = i; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] == 1) {
                    incMatrix[i][edgeIndex] = 1;
                    incMatrix[j][edgeIndex] = 1;
                    edgeIndex++;
                }
            }
        }

        return incMatrix;
    }

    map<char, vector<int>> incidenceList() const {
        map<char, vector<int>> incList;
        vector<vector<int>> incMatrix = incidenceMatrix();

        for (size_t i = 0; i < incMatrix.size(); ++i) {
            char vertex = 'A' + i;
            incList[vertex] = vector<int>();
            for (size_t j = 0; j < incMatrix[i].size(); ++j) {
                if (incMatrix[i][j] == 1) {
                    incList[vertex].push_back(j);
                }
            }
        }

        return incList;
    }
};

int main() {
    Graph graph;

    string choice;
    cout << "Enter 'file' to read adjacency matrix from file or 'console' to read from console: ";
    getline(cin >> ws, choice); // Считываем строку, игнорируя ведущие пробелы

    if (choice == "file") {
        string filename;
        cout << "Enter filename containing adjacency matrix: ";
        cin >> filename;

        try {
            graph.readAdjacencyMatrixFromFile(filename);
        } 
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }
    } 
    else if (choice == "console") {
        try {
            graph.readAdjacencyMatrixFromConsole();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }
    } 
    else {
        cerr << "Invalid choice." << endl;
        return 1;
    }

    graph.printAdjacencyMatrix();

    cout << "\nAdjacency List:\n";
    auto adjList = graph.adjacencyList();
    for (const auto& [vertex, neighbours] : adjList) {
        cout << vertex << ": ";
        for (char neighbour : neighbours) {
            cout << neighbour << " ";
        }
        cout << endl;
    }

    vector<vector<int>> incMatrix = graph.incidenceMatrix();
    cout << "\nIncidence Matrix:\n";
    cout << "   12  13  22  24  33  34  \n";
    int count = 0;
    for (const auto& row : incMatrix) {
        count++;
        cout << count << ": ";
        for (int value : row) {
            cout << value << "   ";
        }
        cout << endl;
    }
    count = 0;
    cout << "\nIncidence List:\n";
    auto incList = graph.incidenceList();
    for (const auto& [vertex, edges] : incList) {
        count++;
        cout << count << ": ";
        for (int edge : edges) {
            cout << edge << " ";
        }
        cout << endl;
    }

    cout << "Press any key to exit...";
    cin.ignore();
    cin.get();

    return 0;
}
