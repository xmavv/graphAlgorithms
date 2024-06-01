#include "iostream"
using namespace std;
#include "Headers/Menu.h"
#include "Headers/Graph.h"

int main() {
//    Menu menu;
//    menu.start();

        int V = 100;
        Graph g(V);

        // Generowanie grafu o gęstości 50% i maksymalnym koszcie 10
        g.generateRandomGraph(0.5, 10);

        // Wczytywanie grafu z pliku
//        g.readFromAdjListFile("adjlist.txt");
//        g.readFromIncidenceMatrixFile("incidence_matrix.txt");

        // Przykład użycia algorytmu BFS
        g.BFS(0);
        cout << endl;

        // Mierzenie czasu działania BFS
        double timeTaken = g.measureTime([&]() { g.BFS(0); });
        cout << "Time taken for BFS: " << timeTaken << " seconds" << endl;

        return 0;

//    cout<<'xd';
}
