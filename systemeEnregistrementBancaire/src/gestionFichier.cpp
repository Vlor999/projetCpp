#include "gestionFichier.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<BanqueAccount> getAccountFromFile(const string& filename) {
    vector<BanqueAccount> listBanqueAccount;
    ifstream fileReader(filename);

    if (!fileReader.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return listBanqueAccount;
    }

    string currentLine;
    bool isOpen = false;
    string name;
    double amount;

    while (getline(fileReader, currentLine)) {
        if (currentLine == "{") {
            isOpen = true;
        } 
        else if (currentLine == "}") {
            isOpen = false;
        } 
        else if (isOpen) {
            size_t pos = currentLine.find(":");
            if (pos != string::npos) {
                name = currentLine.substr(pos + 1);
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
            }
            if (getline(fileReader, currentLine)) {
                pos = currentLine.find(":");
                if (pos != string::npos) {
                    string amountStr = currentLine.substr(pos + 1); 
                    amountStr.erase(0, amountStr.find_first_not_of(" \t"));
                    amountStr.erase(amountStr.find_last_not_of(" \t") + 1);
                    amount = stod(amountStr);
                }
            }
            listBanqueAccount.push_back(BanqueAccount(name, amount));
        }
    }

    fileReader.close();
    return listBanqueAccount;
}

void ajouteCompte(const string& filename, const BanqueAccount& account) {
    ofstream fileWritter(filename);
    string toAdd = "{\n";
    toAdd += "    name : " + account.getName() + ";\n";
    toAdd += "    amount : " + to_string(account.getAmount()) + ";\n";
    toAdd += "}\n";
    fileWritter << toAdd;
    fileWritter.close();
}