#include <iostream>
#include <fstream>
#include <sstream>
#include "menu.hpp"
#include "gestionFichier.hpp"

using namespace std;

void ajoutCompteAll(string filename, vector<BanqueAccount>& listBanque){
    string name;
    double amount;
    cout << "Nom du compte : ";
    getline(cin, name);
    cout << "Montant initial : ";
    cin >> amount;
    cin.ignore();
    BanqueAccount account(name, amount);
    listBanque.push_back(account);
    ajouteCompte(filename, account);
    cout << "Compte ajouté avec succès.\n";
}

BanqueAccount foundCompte(vector<BanqueAccount>& listBanque){
    string name;
    cout << "Nom du compte : ";
    getline(cin, name);
    bool found = false;
    for (const BanqueAccount& account : listBanque) {
        if (account.getName() == name) {
            account.display();
            found = true;
            return account;
        }
    }
    if (!found) {
        cout << "Compte non trouvé.\n";
    }
    return BanqueAccount();
}

void gestionCompte(BanqueAccount& account, string filename, vector<BanqueAccount>& listBanque){
    cout << "Gestion du compte\n";
    cout << "1. Déposer de l'argent\n";
    cout << "2. Retirer de l'argent\n";
    cout << "3. Supprimer le compte\n";
    cout << "4. Retour\n";
    cout << "Votre choix : ";
    int choice;
    cin >> choice;
    cin.ignore();
    bool isModified = false;

    switch (choice) {
        case 1: {
            double value;
            cout << "Montant à déposer : ";
            cin >> value;
            cin.ignore();
            account.deposit(value);
            cout << "Montant déposé avec succès.\n";
            isModified = true;
            break;
        }
        case 2: {
            double value;
            cout << "Montant à retirer : ";
            cin >> value;
            cin.ignore();
            if (account.withdraw(value)) {
                cout << "Montant retiré avec succès.\n";
            } else {
                cout << "Montant insuffisant.\n";
            }
            isModified = true;
            break;
        }
        case 3: {
            cout << "Suppression du compte\n";
            supprimeCompte(filename, account);
            listBanque.erase(std::remove(listBanque.begin(), listBanque.end(), account), listBanque.end());
            cout << "Compte supprimé avec succès.\n";
            break;
        }
        case 4: {
            cout << "Retour au menu principal.\n";
            break;
        }
        default: {
            cout << "Choix invalide.\n";
            break;
        }
    }
    if (isModified) {
        supprimeCompte(filename, account);
        ajouteCompte(filename, account);
    }
}

void launchMenu(vector<BanqueAccount>& listBanque, string filename){
    cout << "Banque Menu\n";
    cout << "1. Ajouter un compte\n";
    cout << "2. Afficher les comptes\n";
    cout << "3. Trouver un compte spécifique\n";
    cout << "4. Connecter un compte\n";
    cout << "5. Quitter\n";
    cout << "Votre choix : ";
    int choice;
    cin >> choice;
    cin.ignore();

    bool isEnd = false;

    switch (choice) {
        case 1: { // ajout d'un compte
            ajoutCompteAll(filename, listBanque);
            break;
        }
        case 2: { // affichage des comptes
            cout << "📋 Liste des comptes bancaires :\n";
            for (const BanqueAccount& account : listBanque) {
                account.display();
                cout << "-------------------\n";
            }
            break;
        }
        case 3: { // recherche d'un compte
            foundCompte(listBanque);
            break;
        }
        case 4: {
            cout << "Connecter un compte\n";
            BanqueAccount account = foundCompte(listBanque);
            if (account.isAccountExist()){
                gestionCompte(account, filename, listBanque);
            }
            break;
        }
        case 5: {
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