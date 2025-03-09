#include <iostream>
#include <vector>
#include "bankAccount.hpp"
#include "gestionFichier.hpp"
#include "menu.hpp"

using namespace std;

#define FILE "data/account.txt"

int main() {
    vector<BanqueAccount> listAccount = getAccountFromFile(FILE);
    launchMenu(listAccount, FILE);

    return EXIT_SUCCESS;
}
