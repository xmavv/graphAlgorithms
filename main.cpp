#include "iostream"
using namespace std;
#include "Headers/Menu.h"
#include "Headers/Utilities.h"
int main() {

    Menu menu(Graph(0));
    menu.start();

//    Graph g(10);
//    g.generateRandomGraph(0.5, 10);
//    g.printAdjList();
//    g.printIncidenceMatrix();

    return 0;
}
