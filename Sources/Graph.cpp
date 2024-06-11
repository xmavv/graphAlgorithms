#include "../Headers/Graph.h"
#include "../Headers/Utilities.h"
#include "../Headers/PriorityQueue.h"
#include "time.h"
#include <algorithm>

Graph::Graph(int V) {
    this->V = V;
    this->initGraph(V);
}

void Graph::initGraph(int V) {
    adjList = new pair<int, int>*[V];
    listSizes = new int[V]();
    for (int i = 0; i < V; ++i) {
        adjList[i] = nullptr;
    }

    incidenceMatrix = new int*[V];
    for (int i = 0; i < V; ++i) {
        incidenceMatrix[i] = new int[0]();
    }
    edgeCount = 0;
}

void Graph::initUnsignedGraph(int V) {
    adjListCopy = new pair<int, int>*[V];
    listSizesCopy = new int[V]();
    for (int i = 0; i < V; ++i) {
        adjListCopy[i] = nullptr;
    }

    incidenceMatrixCopy = new int*[V];
    for (int i = 0; i < V; ++i) {
        incidenceMatrixCopy[i] = new int[0]();
    }
    unsignedEdgeCount = 0;
}

Graph::~Graph() {
    for (int i = 0; i < V; ++i) {
        delete[] adjList[i];
        delete[] incidenceMatrix[i];
    }
    delete[] adjList;
    delete[] incidenceMatrix;
    delete[] listSizes;
}

void Graph::addEdgeList(int u, int v, int weight) {
    pair<int, int>* newAdjU = new pair<int, int>[listSizes[u] + 1];
    for (int i = 0; i < listSizes[u]; ++i) {
        newAdjU[i] = adjList[u][i];
    }
    newAdjU[listSizes[u]] = make_pair(v, weight);
    delete[] adjList[u];
    adjList[u] = newAdjU;
    listSizes[u]++;
}

void Graph::addEdgeListCopy(int u, int v, int weight) {
    pair<int, int>* newAdjU = new pair<int, int>[listSizesCopy[u] + 1];
    for (int i = 0; i < listSizesCopy[u]; ++i) {
        newAdjU[i] = adjListCopy[u][i];
    }
    newAdjU[listSizesCopy[u]] = make_pair(v, weight);
    delete[] adjListCopy[u];
    adjListCopy[u] = newAdjU;
    listSizesCopy[u]++;
}

void Graph::addEdgeMatrix(int u, int v, int weight) {
    for (int i = 0; i < V; ++i) {
        int* newRow = new int[edgeCount + 1];
        for (int j = 0; j < edgeCount; ++j) {
            newRow[j] = incidenceMatrix[i][j];
        }
        newRow[edgeCount] = 0;
        delete[] incidenceMatrix[i];
        incidenceMatrix[i] = newRow;
    }

    incidenceMatrix[u][edgeCount] = weight;
    incidenceMatrix[v][edgeCount] = -weight;
    edgeCount++;
}

void Graph::generateRandomGraph(float density, int maxCost) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, maxCost);

    int edgeCount = 0;
    int maxEdges = V * (V - 1) / 2;
    int requiredEdges = density * maxEdges;

    for (int i = 1; i < V; ++i) {
        int u = i;
        int v = rand() % i;
        int cost = dist(gen);
        addEdgeList(u, v, cost);
        addEdgeMatrix(u, v, cost);
        edgeCount++;
    }

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
    int verticesNumber;

    int initialVertex;
    int finalVertex;
    int weight;

    fstream file;
    file.open(filename, ios::in);

    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        exit(0);
    }

    string line;

    if (getline(file, line)) {
        int* array = Utilities::split(line, 2);

        verticesNumber = array[0];
        edgeNumber = array[1];
        this->V = verticesNumber;
        this->edgeCount = edgeNumber;
        this->initGraph(verticesNumber);
    }

    while (getline(file, line)) {
        int* array = Utilities::split(line, 3);
        initialVertex = array[0];
        finalVertex = array[1];
        weight = array[2];

        this->addEdgeList(initialVertex, finalVertex, weight);
        this->addEdgeMatrix(initialVertex, finalVertex, weight);
    }
    cout<<1<<endl;
    this->copyIncidenceMatrix();
    cout<<2<<endl;
    this->copyAdjList();
    cout<<3<<endl;
}

void Graph::printAdjList() {
    cout << endl << "Adjacency List" << endl << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (int j = 0; j < listSizes[i]; ++j) {
            cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
        }
        cout << endl;
    }
}

void Graph::printIncidenceMatrix() {
    cout << endl << "Incidence Matrix" << endl << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < edgeCount; ++j) {
            int currNumber = incidenceMatrix[i][j];

            if(currNumber < 0) {
                cout<<currNumber<<"  ";
            } else if(currNumber <= 9) {
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

void Graph::makeUndirectedMatrix() {
    for(int i=0; i<V; i++){
        for(int j=0; j<edgeCount; j++){
            if (incidenceMatrixCopy[i][j] == 0) continue;

            incidenceMatrixCopy[i][j] = abs(incidenceMatrixCopy[i][j]);
        }
    }


}

void Graph::copyAdjList() {
    adjListCopy = new pair<int, int>*[V];
    listSizesCopy = new int[V];
    for (int i = 0; i < V; i++) {
        listSizesCopy[i] = listSizes[i];
        adjListCopy[i] = new pair<int, int>[listSizes[i]];
        for (int j = 0; j < listSizes[i]; j++) {
            adjListCopy[i][j] = adjList[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        cout << k << ": ";
        for (int j = 0; j < listSizesCopy[k]; ++j) {
            cout << "(" << adjListCopy[k][j].first << ", " << adjListCopy[k][j].second << ") ";
        }
        cout << endl;
    }
}

void Graph::copyIncidenceMatrix() {
    incidenceMatrixCopy = new int*[V];
    for (int i = 0; i < V; i++) {
        incidenceMatrixCopy[i] = new int[edgeCount];
        for (int j = 0; j < edgeCount; j++) {
            incidenceMatrixCopy[i][j] = incidenceMatrix[i][j];
        }
    }
}

void Graph::makeUndirectedList() {
    for (int u = 0; u < V; ++u) {
        for (int i = 0; i < listSizes[u]; ++i) {
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;

            bool exists = false;
            for (int j = 0; j < listSizes[v]; ++j) {
                if (adjList[v][j].first == u) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                addEdgeListCopy(v, u, weight);
            }
        }
    }

    // Do debugowania, wyświetl listę po zakończeniu operacji
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (int j = 0; j < listSizesCopy[i]; ++j) {
            cout << "(" << adjListCopy[i][j].first << ", " << adjListCopy[i][j].second << ") ";
        }
        cout << endl;
    }
}

void Graph::primMSTList() {
    this->makeUndirectedList();

    PriorityQueue pq(V);
    int* key = new int[V];
    int* parent = new int[V];
    bool* inMST = new bool[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }

    int src = 0;
    pq.push(src);
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.extractMin();
        inMST[u] = true;

        for (int i = 0; i < listSizesCopy[u]; ++i) {
            int v = adjListCopy[u][i].first;
            int weight = adjListCopy[u][i].second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                parent[v] = u;
                pq.push(v);
            }
        }
    }

    int totalWeight = 0;
    cout << "MST using Prim's Algorithm (Adjacency List):" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " : " << key[i] << endl;
        totalWeight += key[i];
    }
    cout << "Total weight: " << totalWeight << endl;

    delete[] key;
    delete[] parent;
    delete[] inMST;
}

void Graph::primMSTMatrix() {
    this->makeUndirectedMatrix();

    int* key = new int[V];
    int* parent = new int[V];
    bool* inMST = new bool[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;
    int totalWeight = 0;

    for (int count = 0; count < V - 1; ++count) {
        int minKey = INT_MAX, u = -1;

        for (int i = 0; i < V; ++i) {
            if (!inMST[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }
        }

        inMST[u] = true;

        for (int e = 0; e < edgeCount; ++e) {
            int weight = incidenceMatrixCopy[u][e];
            if (weight > 0) {
                for (int v = 0; v < V; ++v) {
                    if (incidenceMatrixCopy[v][e] > 0 && v != u && !inMST[v] && weight < key[v]) {
                        key[v] = weight;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    cout << "MST using Prim's Algorithm (Incidence Matrix):" << endl;
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " : " << key[i] << endl;
            totalWeight += key[i];
        }
    }
    cout << "Total weight: " << totalWeight << endl;

    delete[] key;
    delete[] parent;
    delete[] inMST;
}

void Graph::kruskalMSTList() {
    u.startCounter();

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

    int totalWeight = 0;

    cout << "MST using Kruskal's Algorithm (Adjacency List):" << endl;
    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int weight = edges[i].first;

        if (findSet(u, parent) != findSet(v, parent)) {
            cout << u << " - " << v << " : " << weight << endl;
            totalWeight += weight;
            unionSets(u, v, parent, rank);
        }
    }
    double stop = u.getCounter();

    cout << "Total weight: " << totalWeight << endl;
    cout << "Total time: " << to_string(stop) + "[ms]" << endl;

    delete[] edges;
    delete[] parent;
    delete[] rank;
}

void Graph::kruskalMSTMatrix() {
    u.startCounter();

    pair<int, pair<int, int>>* edges = new pair<int, pair<int, int>>[edgeCount];
    int edgeIndex = 0;

    for (int v = 0; v < edgeCount; ++v) {
        for (int u = 0; u < V; ++u) {
            if (incidenceMatrix[u][v] > 0) {
                int weight = incidenceMatrix[u][v];
                int w = -1;
                for (int k = 0; k < V; ++k) {
                    if (incidenceMatrix[k][v] == -weight) {
                        w = k;
                        break;
                    }
                }
                if (w != -1) {
                    edges[edgeIndex++] = {weight, {u, w}};
                }
            }
        }
    }

    sort(edges, edges + edgeIndex);

    int* parent = new int[V];
    int* rank = new int[V]();
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    int totalWeight = 0;

    cout << "MST using Kruskal's Algorithm (Incidence Matrix):" << endl;
    for (int i = 0; i < edgeIndex; ++i) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int weight = edges[i].first;

        if (findSet(u, parent) != findSet(v, parent)) {
            cout << u << " - " << v << " : " << weight << endl;
            totalWeight += weight;
            unionSets(u, v, parent, rank);
        }
    }
    double stop = u.getCounter();

    cout << "Total weight: " << totalWeight << endl;
    cout << "Total time: " << to_string(stop) + "[ms]" << endl;

    delete[] edges;
    delete[] parent;
    delete[] rank;
}

void Graph::dijkstraSPList(int src) {
    u.startCounter();

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
    double stop = u.getCounter();

    cout << "Shortest paths using Dijkstra's Algorithm from vertex " << src << " (Adjacency List):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " : " << dist[i] << endl;
    }
    cout << "Total time: " << to_string(stop) + "[ms]" << endl;

    delete[] dist;
    delete[] visited;
}

void Graph::dijkstraSPMatrix(int src) {
    u.startCounter();

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

        for (int v = 0; v < edgeCount; ++v) {
            if (incidenceMatrix[u][v] > 0) {
                int weight = incidenceMatrix[u][v];
                for (int w = 0; w < V; ++w) {
                    if (w != u && incidenceMatrix[w][v] == -weight && !visited[w] && dist[u] + weight < dist[w]) {
                        dist[w] = dist[u] + weight;
                        pq.push({dist[w], w});
                    }
                }
            }
        }
    }
    double stop = u.getCounter();

    cout << "Shortest paths using Dijkstra's Algorithm from vertex " << src << " (Incidence Matrix):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " : " << dist[i] << endl;
    }
    cout << "Total time: " << to_string(stop) + "[ms]" << endl;

    delete[] dist;
    delete[] visited;
}

void Graph::bellmanFordSPList(int src) {
    u.startCounter();

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
    double stop = u.getCounter();

    cout << "Shortest paths using Bellman-Ford Algorithm from vertex " << src << " (Adjacency List):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " : " << dist[i] << endl;
    }
    cout << "Total time: " << to_string(stop) + "[ms]" << endl;

    delete[] dist;
}

void Graph::bellmanFordSPMatrix(int src) {
    u.startCounter();

    int* dist = new int[V];

    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i < V; ++i) {
        for (int v = 0; v < edgeCount; ++v) {
            for (int u = 0; u < V; ++u) {
                if (incidenceMatrix[u][v] > 0) {
                    int weight = incidenceMatrix[u][v];
                    for (int w = 0; w < V; ++w) {
                        if (incidenceMatrix[w][v] == -weight && dist[u] != INT_MAX && dist[u] + weight < dist[w]) {
                            dist[w] = dist[u] + weight;
                        }
                    }
                }
            }
        }
    }

    for (int v = 0; v < edgeCount; ++v) {
        for (int u = 0; u < V; ++u) {
            if (incidenceMatrix[u][v] > 0) {
                int weight = incidenceMatrix[u][v];
                for (int w = 0; w < V; ++ w) {
                    if (incidenceMatrix[w][v] == -weight && dist[u] != INT_MAX && dist[u] + weight < dist[w]) {
                        cout << "Graph contains negative weight cycle" << endl;
                        delete[] dist;
                        return;
                    }
                }
            }
        }
    }
    double stop = u.getCounter();

    cout << "Shortest paths using Bellman-Ford Algorithm from vertex " << src << " (Incidence Matrix):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " : " << dist[i] << endl;
    }
    cout << "Total time: " << to_string(stop) + "[ms]" << endl;

    delete[] dist;
}
