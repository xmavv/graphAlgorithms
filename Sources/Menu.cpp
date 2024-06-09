#include "iostream"
using namespace std;
#include "../Headers/Menu.h"

Menu::Menu(Graph g) : g(g) {}

void Menu::start() {
    while(true) {
        cout<<endl<<endl<<("--------------------MENU-1--------------------")<<endl;
        cout<<"1. wygeneruj graf losowo o zadanej dlugosci wierzcholkow"<<endl;
        cout<<"2. wczytaj dane z pliku"<<endl<<endl;
        cout<<"lub: "<<endl<<endl;
        cout<<"0. wyjdz z programu"<<endl;
        cin>>userChoice;
        if(userChoice == 0) exit(0);

        if(userChoice == 1) {
            cout<<"podaj liczbe wierzcholkow"<<endl;
            cin>>numberOfVertices;

            Graph g(numberOfVertices);
            this -> g = g;

            generateGraph();
            chooseAlgorithm();
        } else if (userChoice == 2) {
            loadFromFile();
            chooseAlgorithm();
        } else {
            cout<<"niepoprawny wybor!"<<endl;
            continue;
        }
    }
}

void Menu::generateGraph() {
    float density;
    int maxWeight;

    cout<<"podaj gestosc"<<endl;
    cout<<"podaj max wage krawedzi"<<endl;
    cin>>density;
    cin>>maxWeight;
    g.generateRandomGraph(density, maxWeight);

    cout<<"chcesz zobaczyc twoj graf?"<<endl;
    cout<<"1. tak"<<endl;
    cout<<"2. nie"<<endl;
    cin>>userChoice;
    if(userChoice == 1) printGraph();
}

void Menu::printGraph() {
    cout<<"twoj graf wyglada tak o"<<endl;

    g.printIncidenceMatrix();
    g.printAdjList();
}

void Menu::chooseAlgorithm() {
    while(true) {
        cout <<endl<<endl<<("--------------------MENU-2--------------------")<<endl;
        cout << "1. MST PRIM" << endl;
        cout << "2. MST KRUSKAL" << endl;
        cout << "3. DFS BELLMAN FORD" << endl;
        cout << "4. DFS DIJKSTRY" << endl;
        cout << "5. zobacz graf" << endl;
        cout << "lub: " << endl << endl;
        cout << "9. wyjdz do menu-1" << endl;
        cout << "0. wyjdz z programu" << endl;
        cin >> userChoice;

        if(userChoice == 9) return;
        if(userChoice == 0) exit(0);

        if(userChoice == 1) {
            cout<<"1. lista"<<endl;
            cout<<"2. macierz"<<endl;
            cin>>userChoice;

            if(userChoice == 1) g.primMSTList();
            if(userChoice == 2) g.primMSTMatrix();
            else {
                cout<<"niepoprawny wybor"<<endl;
                continue;
            }
        }
        else if(userChoice == 2) {
            cout<<"1. lista"<<endl;
            cout<<"2. macierz"<<endl;
            cin>>userChoice;

            if(userChoice == 1) g.kruskalMSTList();
            if(userChoice == 2) g.kruskalMSTMatrix();
            else {
                cout<<"niepoprawny wybor"<<endl;
                continue;
            }
        }
        else if(userChoice == 3) {
            cout<<"1. lista"<<endl;
            cout<<"2. macierz"<<endl;
            cin>>userChoice;

            if(userChoice == 1) {
                cout<<"podaj dla ktorego wierzcholka chcesz znalezc najkrotsza droge"<<endl;
                cin>>userChoice;

                g.bellmanFordSPList(userChoice);
                continue;
            }
            if(userChoice == 2) {
                cout<<"podaj dla ktorego wierzcholka chcesz znalezc najkrotsza droge"<<endl;
                cin>>userChoice;

                g.bellmanFordSPMatrix(userChoice);
                continue;
            }
            else {
                cout<<"niepoprawny wybor"<<endl;
                continue;
            }
        }
        else if(userChoice == 4) {
            cout<<"1. lista"<<endl;
            cout<<"2. macierz"<<endl;
            cin>>userChoice;

            if(userChoice == 1) {
                cout<<"podaj dla ktorego wierzcholka chcesz znalezc najkrotsza droge"<<endl;
                cin>>userChoice;

                g.dijkstraSPList(userChoice);
                continue;
            }
            if(userChoice == 2) {
                cout<<"podaj dla ktorego wierzcholka chcesz znalezc najkrotsza droge"<<endl;
                cin>>userChoice;

                g.dijkstraSPMatrix(userChoice);
                continue;
            }
            else {
                cout<<"niepoprawny wybor"<<endl;
                continue;
            }
        }
        else if(userChoice == 5) printGraph();
        else {
            cout<<"niepoprawny wybor!"<<endl;
            continue;
        }
    }
}

void Menu::loadFromFile() {
    cout<<"podaj nazwe pliku"<<endl;
    cin>>filename;

    g.loadGraphFromFile(filename);
}