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
    string id;
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
                name = currentLine.substr(pos + 1, currentLine.size());
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
                name.erase(name.find_last_not_of(";") + 1);
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
            if (getline(fileReader, currentLine)) {
                pos = currentLine.find(":");
                if (pos != string::npos) {
                    string id = currentLine.substr(pos + 1, currentLine.size());
                    id.erase(0, id.find_first_not_of(" \t"));
                    id.erase(id.find_last_not_of(" \t") + 1);
                    id.erase(id.find_last_not_of(";") + 1);
                    listBanqueAccount.push_back(BanqueAccount(name, amount, id));

                }
            }
        }
    }

    fileReader.close();
    return listBanqueAccount;
}

void ajouteCompte(const string& filename, const BanqueAccount& account) {
    ofstream fileWritter(filename, ios::app);
    string toAdd = "{\n";
    toAdd += "    name : " + account.getName() + ";\n";
    toAdd += "    amount : " + to_string(account.getAmount()) + ";\n";
    toAdd += "    id : " + account.getId() + ";\n";
    toAdd += "}\n";
    fileWritter << toAdd;
    fileWritter.close();
}

void supprimeCompte(const string& filename, const BanqueAccount& account){
    ifstream fileReader(filename);
    ofstream fileWritter("temp.txt");

    if (!fileReader.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return;
    }

    string currentLine;
    bool isOpen = false;
    string id;
    string name;
    double amount;

    while (getline(fileReader, currentLine)) {
        cout << currentLine << endl;
        if (currentLine == "{") {
            isOpen = true;
        } 
        else if (currentLine == "}") {
            isOpen = false;
            if (id != account.getId()) {
                fileWritter << "{\n";
                fileWritter << "    name : " + name + ";\n";
                fileWritter << "    amount : " + to_string(amount) + ";\n";
                fileWritter << "}\n";
            }
        } 
        else if (isOpen) {
            size_t pos = currentLine.find(":");
            if (pos != string::npos) {
                name = currentLine.substr(pos + 1);
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
                name.erase(name.find_last_not_of(";") + 1);
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
            if (getline(fileReader, currentLine)) {
                pos = currentLine.find(":");
                if (pos != string::npos) {
                    id = currentLine.substr(pos + 1, currentLine.size());
                    id.erase(0, id.find_first_not_of(" \t"));
                    id.erase(id.find_last_not_of(" \t") + 1);
                    id.erase(id.find_last_not_of(";") + 1);
                }
            }
        }
    }

    fileReader.close();
    fileWritter.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}
