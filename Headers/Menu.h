#ifndef GRAPHALGORITHMS_MENU_Ht
#define GRAPHALGORITHMS_MENU_H
#include "../Headers/Graph.h"


class Menu {
    int userChoice;
    int numberOfVertices;
    string fileName;
    Graph g;

public:
    Menu(Graph g);
    void start();
    void generateGraph();
    void printGraph();
};


#endif //GRAPHALGORITHMS_MENU_H
