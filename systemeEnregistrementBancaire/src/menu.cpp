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
    string id;
    cout << "ID du compte : ";
    getline(cin, id);
    bool found = false;
    for (const BanqueAccount& account : listBanque) {
        if (account.getId() == id) { // Il est plus normal de comparer les ID des comptes que les noms
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
    cout << "3. Afficher information\n";
    cout << "4. Supprimer le compte\n";
    cout << "5. Retour\n";
    cout << "Votre choix : ";
    int taille = 8; // Nombre de lignes à effacer
    int choice;
    cin >> choice;
    cin.ignore();
    bool isModified = false;

    switch (choice) {
        case 1: {
            clearTerminal(taille);
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
            clearTerminal(taille);
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
        case 3:{
            clearTerminal(taille);
            account.display();
            break;
        }
        case 4: {
            clearTerminal(taille);
            cout << "Suppression du compte\n";
            supprimeCompte(filename, account);
            listBanque.erase(std::remove(listBanque.begin(), listBanque.end(), account), listBanque.end());
            cout << "Compte supprimé avec succès.\n";
            break;
        }
        case 5: {
            clearTerminal(taille);
            cout << "Retour au menu principal.\n";
            return;
        }
        default: {
            clearTerminal(taille);
            cout << "Choix invalide.\n";
            break;
        }
    }
    if (isModified) {
        supprimeCompte(filename, account);
        ajouteCompte(filename, account);
    }
    gestionCompte(account, filename, listBanque);
}

void clearTerminal(int taille){
    for (int i = 1; i < taille; i++) {
        std::cout
        << "\x1b[1A"
        << "\x1b[2K";
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
    int taille = 8; // Nombre de lignes à effacer : nombre de retour a la ligne + 1

    switch (choice) {
        case 1: { // ajout d'un compte
            clearTerminal(taille);
            ajoutCompteAll(filename, listBanque);
            break;
        }
        case 2: { // affichage des comptes
            clearTerminal(taille);
            cout << "📋 Liste des comptes bancaires :\n";
            for (const BanqueAccount& account : listBanque) {
                account.display();
            }
            break;
        }
        case 3: { // recherche d'un compte
            clearTerminal(taille);
            foundCompte(listBanque);
            break;
        }
        case 4: {
            clearTerminal(taille);
            cout << "Connecter un compte\n";
            BanqueAccount account = foundCompte(listBanque);
            if (account.isAccountExist()){
                gestionCompte(account, filename, listBanque);
            }
            break;
        }
        case 5: {
            clearTerminal(taille);
            cout << "Fermeture du programme.\n";
            isEnd = true;
            break;
        }
        default: {
            clearTerminal(taille);
            cout << "Choix invalide.\n";
            break;
        }
    }
    if (!isEnd) {
        launchMenu(listBanque, filename);
    }

}