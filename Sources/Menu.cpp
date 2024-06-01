#include "iostream"
using namespace std;
#include "../Headers/Menu.h"

Menu::Menu(Graph g) : g(g) {}

void Menu::start() {
    while(true) {
        cout<<("--------------------MENU-2--------------------");
        cout<<endl<<"wybierz sposob podania danych"<<endl;
        cout<<"1. wygeneruj losowo dane o zadanej dlugosci"<<endl;
        cout<<"2. wczytaj dane z pliku"<<endl<<endl;
        cout<<"lub: "<<endl<<endl;
        cout<<"9. wyjdz do menu-1"<<endl;
        cout<<"0. wyjdz z programu"<<endl;
        cin>>userChoice;
        if(userChoice == 9) return;

        if(userChoice == 1) {
            cout << "podaj liczbe wierzchołków" << endl;
            cin >> numberOfVertices;

            Graph g(numberOfVertices);
            this -> g = g;
        } else if (userChoice == 2) {
            cout<<"podaj nazwe pliku"<<endl;
        } else {
            cout<<"niepoprawny wybor!";
            continue;
        }
    }
}

void Menu::generateGraph() {
    float density;
    int maxWeight;

    cout<<"podaj gestosc a nastepnie max wage krawedzi"<<endl;
    cin>>density;
    cin>>maxWeight;
    g.generateRandomGraph(density, maxWeight);
}

void Menu::printGraph() {
    cout<<"twoj graf wyglada tak o"<<endl;

    g.printIncidenceMatrix();
    g.printAdjList();
}
