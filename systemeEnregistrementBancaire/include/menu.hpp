#pragma once
#include <vector>
#include "bankAccount.hpp"
#include "gestionFichier.hpp"

void launchMenu(vector<BanqueAccount>& listBanque, string filename);

void ajoutCompteAll(string filename, vector<BanqueAccount>& listBanque);

BanqueAccount foundCompte(vector<BanqueAccount>& listBanque);
