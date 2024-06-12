#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <queue>
#include <algorithm>
#include "Utilities.h"

using namespace std;

class Graph {
private:
    int V; // liczba wierzchołków
    int edgeCount;
    int unsignedEdgeCount;
    pair<int, int>** adjList; // lista następników
    int* listSizes; // rozmiary list następników
    pair<int, int>** adjListCopy;
    int* listSizesCopy;
    int** incidenceMatrix; // macierz incydencji
    int** incidenceMatrixCopy;
    int findSet(int i, int* parent);
    void unionSets(int u, int v, int* parent, int* rank);
    void initGraph(int V);
    void initUnsignedGraph(int V);
    Utilities u;
    void makeUndirectedMatrix();
    void makeUndirectedList();
    void copyAdjList();
    void copyIncidenceMatrix();

public:
    Graph(int V);
    ~Graph();
    void generateRandomGraph(float density, int maxCost);
    void printAdjList();
    void printIncidenceMatrix();
    void addEdgeList(int u, int v, int weight);
    void addEdgeListCopy(int u, int v, int weight);
    void addEdgeMatrix(int u, int v, int cost);
    void loadGraphFromFile(string filename);
    double primMSTList();
    double primMSTMatrix();
    double kruskalMSTList();
    double kruskalMSTMatrix();
    double bellmanFordSPList(int src);
    double bellmanFordSPMatrix(int src);
    double dijkstraSPMatrix(int src);
    double dijkstraSPList(int src);
};


#endif //GRAPHALGORITHMS_GRAPH_H
