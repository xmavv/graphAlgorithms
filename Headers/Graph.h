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
    pair<int, int>** adjList; // lista następników
    int* listSizes; // rozmiary list następników
    int** incidenceMatrix; // macierz incydencji
    int findSet(int i, int* parent);
    void unionSets(int u, int v, int* parent, int* rank);
    void initGraph(int V);
    Utilities u;

public:
    Graph(int V);
    ~Graph();
    void generateRandomGraph(float density, int maxCost);
    void printAdjList();
    void printIncidenceMatrix();
    void addEdgeList(int u, int v, int weight);
    void addEdgeMatrix(int u, int v, int cost);
    void loadGraphFromFile(string filename);
    void primMSTList();
    void primMSTMatrix();
    void kruskalMSTList();
    void kruskalMSTMatrix();
    void bellmanFordSPList(int src);
    void bellmanFordSPMatrix(int src);
    void dijkstraSPMatrix(int src);
    void dijkstraSPList(int src);
};


#endif //GRAPHALGORITHMS_GRAPH_H
