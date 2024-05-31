#include "iostream"
using namespace std;
#include "../Headers/Menu.h"

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

        if(userChoice == 1) {
            cout<<("podaj rozmiar tablicy ");
            cin>>arrayLength;
        } if(userChoice == 9) {
            break;
        }
        int arrayCopy[arrayLength];

        switch(userChoice) {
            case 1:
                generateRandomArray(arrayLength); //global arrayToSort variable changed, so we can work with it

                Utilities<T>::copyArray(arrayToSort, arrayCopy, arrayLength);

                choosePreSort(arrayCopy);
                break;
            case 2:
                cout<<("podaj nazwe pliku (plik tekstowy musi znajodwac sie w tym samym folderze co plik wykonywalny programu!) ");
                cin>>fileName;
                loadArrayFromFile(fileName);

                Utilities<T>::copyArray(arrayToSort, arrayCopy, arrayLength);

                choosePreSort(arrayCopy);
                break;
            case 9:
                return;
            case 0:
                exit(0);
            default:
                cerr<<"niepoprawny wybor!"<<endl;
        }

        if(userChoice == 9) return;
    }
    if(userChoice == 9) return;
}