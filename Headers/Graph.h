#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V; // liczba wierzchołków
    int** adjList; // lista następników
    int** incidenceMatrix; // macierz incydencji
    int* listSizes; // rozmiary list następników

public:
    Graph(int V) : V(V) {
        adjList = new int*[V]; // alokowanie tablicy wskaźników
        listSizes = new int[V]();
        for (int i = 0; i < V; ++i) {
            adjList[i] = nullptr; // początkowo wskaźniki są puste
        }

        incidenceMatrix = new int*[V]; // alokowanie tablicy wskaźników do tablic
        for (int i = 0; i < V; ++i) {
            incidenceMatrix[i] = new int[V](); // alokowanie tablicy int dla każdego wierzchołka
        }
    }

    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] adjList[i]; // zwalnianie pamięci dla każdej tablicy sąsiedztwa
            delete[] incidenceMatrix[i]; // zwalnianie pamięci dla każdej tablicy w macierzy incydencji
        }
        delete[] adjList; // zwalnianie pamięci dla tablicy wskaźników
        delete[] incidenceMatrix; // zwalnianie pamięci dla tablicy wskaźników
        delete[] listSizes; // zwalnianie pamięci dla tablicy rozmiarów list
    }

    void addEdgeList(int u, int v, int cost) {
        listSizes[u]++;
        listSizes[v]++; // dla grafu nieskierowanego

        int* newAdjU = new int[listSizes[u]];
        int* newAdjV = new int[listSizes[v]];

        if (adjList[u] != nullptr) {
            copy(adjList[u], adjList[u] + listSizes[u] - 1, newAdjU);
            delete[] adjList[u];
        }
        if (adjList[v] != nullptr) {
            copy(adjList[v], adjList[v] + listSizes[v] - 1, newAdjV);
            delete[] adjList[v];
        }

        newAdjU[listSizes[u] - 1] = v;
        newAdjV[listSizes[v] - 1] = u; // dla grafu nieskierowanego

        adjList[u] = newAdjU;
        adjList[v] = newAdjV;
    }

    void addEdgeMatrix(int u, int v, int cost) {
        incidenceMatrix[u][v] = cost;
        incidenceMatrix[v][u] = cost; // dla grafu nieskierowanego
    }

    void generateRandomGraph(float density, int maxCost) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, maxCost);

        int edgeCount = 0;
        int maxEdges = (V * (V - 1)) / 2;
        int requiredEdges = density * maxEdges;

        // Generowanie drzewa rozpinającego
        for (int i = 1; i < V; ++i) {
            int u = i;
            int v = rand() % i;
            int cost = dist(gen);
            addEdgeList(u, v, cost);
            addEdgeMatrix(u, v, cost);
            edgeCount++;
        }

        // Dodawanie pozostałych krawędzi
        while (edgeCount < requiredEdges) {
            int u = rand() % V;
            int v = rand() % V;
            if (u != v && incidenceMatrix[u][v] == 0) {
                int cost = dist(gen);
                addEdgeList(u, v, cost);
                addEdgeMatrix(u, v, cost);
                edgeCount++;
            }
        }
    }

    void readFromAdjListFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Cannot open file!" << endl;
            return;
        }

        int u, v, cost;
        while (file >> u >> v >> cost) {
            addEdgeList(u, v, cost);
        }
        file.close();
    }

    void readFromIncidenceMatrixFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Cannot open file!" << endl;
            return;
        }

        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                file >> incidenceMatrix[i][j];
            }
        }
        file.close();
    }

    // Przykładowy algorytm BFS
    void BFS(int start) {
        bool* visited = new bool[V]();
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int i = 0; i < listSizes[u]; ++i) {
                int v = adjList[u][i];
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        delete[] visited;
    }

    // Funkcja do mierzenia czasu działania algorytmów
    template<typename Func>
    double measureTime(Func func) {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        return elapsed.count();
    }
};


#endif //GRAPHALGORITHMS_GRAPH_H
