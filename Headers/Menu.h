#ifndef GRAPHALGORITHMS_MENU_Ht
#define GRAPHALGORITHMS_MENU_H


class Menu {
    int userChoice;
    string fileName;

    void generateRandomGraph();
    void loadGraphFromFile(string name);
    void chooseDensity();

public:
    void start();
};


#endif //GRAPHALGORITHMS_MENU_H
