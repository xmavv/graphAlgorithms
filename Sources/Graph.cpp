#include "../Headers/Graph.h"
#include "../Headers/Utilities.h"

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

void Graph::loadGraphFromFile(string filename) {
    int edgeNumber;
    int vertivesNumber;

    int initialVertex;
    int finalVertex;
    int weight;

    fstream file;
    file.open(filename, ios::in);

    if(!file.is_open()) {
        cout<<"nie udalo sie otworzyc pliku!"<<endl;
        exit(0);
    }

    string line;

    if(getline(file, line)) {
        int *array = Utilities::split(line, 2);

        edgeNumber = array[0];
        vertivesNumber = array[1];
    }

    while(getline(file, line)) {
        int *array = Utilities::split(line, 3);
        initialVertex = array[0];
        finalVertex = array[1];
        weight = array[2];

        //TUTAJ TRZEBA KONSTRUKTOR WYWOLAC DLA TEGO GRAFU TYLE ILE MA TYCH WIERZCHOLKOW NIE
        this->V = vertivesNumber;

        this->addEdgeList(initialVertex, finalVertex, weight);
        this->addEdgeMatrix(initialVertex, finalVertex, weight);
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

void Graph::primMST() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int* key = new int[V];
    int* parent = new int[V];
    bool* inMST = new bool[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }

    int src = 0;
    pq.push({0, src});
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (int i = 0; i < listSizes[u]; ++i) {
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "MST using Prim's Algorithm:" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << endl;
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
}

int Graph::findSet(int i, int* parent) {
    if (i == parent[i]) {
        return i;
    }
    return parent[i] = findSet(parent[i], parent);
}

void Graph::unionSets(int u, int v, int* parent, int* rank) {
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

void Graph::kruskalMST() {
    pair<int, pair<int, int>>* edges = new pair<int, pair<int, int>>[V * V];
    int edgeCount = 0;

    for (int u = 0; u < V; ++u) {
        for (int i = 0; i < listSizes[u]; ++i) {
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;
            edges[edgeCount++] = {weight, {u, v}};
        }
    }

    sort(edges, edges + edgeCount);

    int* parent = new int[V];
    int* rank = new int[V]();
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    cout << "MST using Kruskal's Algorithm:" << endl;
    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int weight = edges[i].first;

        if (findSet(u, parent) != findSet(v, parent)) {
            cout << u << " - " << v << " : " << weight << endl;
            unionSets(u, v, parent, rank);
        }
    }

    delete[] edges;
    delete[] parent;
    delete[] rank;
}

void Graph::dijkstryDFS(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int* dist = new int[V];
    bool* visited = new bool[V];

    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (int i = 0; i < listSizes[u]; ++i) {
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest paths using Dijkstra's Algorithm from vertex " << src << ":" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " : " << dist[i] << endl;
    }

    delete[] dist;
    delete[] visited;
}

void Graph::bellmanFordDFS(int src) {
    int* dist = new int[V];

    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i < V; ++i) {
        for (int u = 0; u < V; ++u) {
            for (int j = 0; j < listSizes[u]; ++j) {
                int v = adjList[u][j].first;
                int weight = adjList[u][j].second;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        for (int j = 0; j < listSizes[u]; ++j) {
            int v = adjList[u][j].first;
            int weight = adjList[u][j].second;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                delete[] dist;
                return;
            }
        }
    }

    cout << "Shortest paths using Bellman-Ford Algorithm from vertex " << src << ":" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " : " << dist[i] << endl;
    }

    delete[] dist;
}