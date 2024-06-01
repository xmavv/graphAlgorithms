#include "../Headers/Graph.h"

Graph::Graph(int V) {
    this -> V = V;

        adjList = new pair<int, int>*[V]; // alokowanie tablicy wskaźników dla listy sąsiedztwa
        listSizes = new int[V](); // alokowanie i inicjalizacja tablicy rozmiarów list na 0
        for (int i = 0; i < V; ++i) {
            adjList[i] = nullptr; // początkowo wskaźniki są puste
    }

    incidenceMatrix = new int*[V]; // alokowanie tablicy wskaźników do macierzy incydencji
    for (int i = 0; i < V; ++i) {
        incidenceMatrix[i] = new int[V](); // alokowanie tablicy int dla każdego wierzchołka i inicjalizacja zerami
    }
}

Graph::~Graph() {
    for (int i = 0; i < V; ++i) {
        delete[] adjList[i]; // zwalnianie pamięci dla każdej tablicy sąsiedztwa
        delete[] incidenceMatrix[i]; // zwalnianie pamięci dla każdej tablicy w macierzy incydencji
    }
    delete[] adjList; // zwalnianie pamięci dla tablicy wskaźników
    delete[] incidenceMatrix; // zwalnianie pamięci dla tablicy wskaźników
    delete[] listSizes; // zwalnianie pamięci dla tablicy rozmiarów list
}

void Graph::addEdgeList(int u, int v, int weight) {
    // Zwiększenie rozmiaru listy sąsiedztwa dla wierzchołka u
    pair<int, int>* newAdjU = new pair<int, int>[listSizes[u] + 1];
    for (int i = 0; i < listSizes[u]; ++i) {
        newAdjU[i] = adjList[u][i];
    }
    newAdjU[listSizes[u]] = make_pair(v, weight);
    delete[] adjList[u];
    adjList[u] = newAdjU;
    listSizes[u]++;
}

void Graph::addEdgeMatrix(int u, int v, int cost) {
    incidenceMatrix[u][v] = cost;
}

void Graph::generateRandomGraph(float density, int maxCost){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, maxCost);

    int edgeCount = 0;
    int maxEdges = V * (V - 1);
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

void Graph::printAdjList() {
    cout<<endl<<"Lista nastepnikow"<<endl<<endl;
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (int j = 0; j < listSizes[i]; ++j) {
            cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
        }
        cout << endl;
    }
}

void Graph::printIncidenceMatrix() {
    cout<<endl<<"Macierz incydencji"<<endl<<endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            int currNumber = incidenceMatrix[i][j];

            if(currNumber <= 9) {
                cout << " " << currNumber << " "<< " ";
            } else if(currNumber >= 9 && currNumber < 100) {
                cout << " " << currNumber<< " ";
            } else {
                cout << currNumber<< " ";
            }
        }
        cout << endl;
    }
}