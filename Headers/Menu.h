#ifndef GRAPHALGORITHMS_MENU_Ht
#define GRAPHALGORITHMS_MENU_H
#include "../Headers/Graph.h"


class Menu {
    int userChoice;
    int numberOfVertices;
    string fileName;
    Graph g;
    void generateGraph();
    void printGraph();
    void chooseAlgorithm();

public:
    Menu(Graph g);
    void start();
};


#endif //GRAPHALGORITHMS_MENU_H
