#ifndef GRAPHALGORITHMS_MENU_Ht
#define GRAPHALGORITHMS_MENU_H
#include "../Headers/Graph.h"
#include "../Headers/Utilities.h"


class Menu {
    int userChoice;
    int numberOfVertices;
    string filename;
    Graph g;
    void generateGraph();
    void printGraph();
    double chooseAlgorithm();
    void loadFromFile();

public:
    Menu(Graph g);
    void start();
    void test();
};


#endif //GRAPHALGORITHMS_MENU_H
