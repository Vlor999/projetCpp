#include <iostream>
#include <vector>
#include "bankAccount.hpp"
#include "gestionFichier.hpp"

using namespace std;

#define FILE "include/account.txt"

int main() {
    vector<BanqueAccount> listAccount = getAccountFromFile(FILE);

    cout << "📋 Liste des comptes bancaires :\n";
    for (const BanqueAccount& account : listAccount) {
        account.display();
        cout << "-------------------\n";
    }

    return EXIT_SUCCESS;
}
