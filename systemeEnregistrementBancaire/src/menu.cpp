#include "menu.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void launchMenu(vector<BanqueAccount>& listBanque, string filename){
    cout << "Banque Menu\n";
    cout << "1. Ajouter un compte\n";
    cout << "2. Afficher les comptes\n";
    cout << "3. Trouver un compte spécifique\n";
    cout << "4. Quitter\n";
    cout << "Votre choix : ";
    int choice;
    cin >> choice;
    cin.ignore();

    bool isEnd = false;

    switch (choice) {
        case 1: {
            cout << "Nom du compte : ";
            string name;
            getline(cin, name);
            cout << "Montant initial : ";
            double amount;
            cin >> amount;
            cin.ignore();
            BanqueAccount account(name, amount);
            listBanque.push_back(account);
            ajouteCompte(filename, account);
            cout << "Compte ajouté avec succès.\n";
            break;
        }
        case 2: {
            cout << "📋 Liste des comptes bancaires :\n";
            for (const BanqueAccount& account : listBanque) {
                account.display();
                cout << "-------------------\n";
            }
            break;
        }
        case 3: {
            cout << "Nom du compte : ";
            string name;
            getline(cin, name);
            bool found = false;
            for (const BanqueAccount& account : listBanque) {
                if (account.getName() == name) {
                    account.display();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Compte non trouvé.\n";
            }
            break;
        }
        case 4: {
            cout << "Fermeture du programme.\n";
            isEnd = true;
            break;
        }
        default: {
            cout << "Choix invalide.\n";
            break;
        }
    }
    if (!isEnd) {
        launchMenu(listBanque, filename);
    }

}