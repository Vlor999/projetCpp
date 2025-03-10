#pragma once
#include <vector>
#include "bankAccount.hpp"

/*
    Lie le fichier et trouve suivant un format conventionne le nom des comptes et leur valeur
*/
std::vector<BanqueAccount> getAccountFromFile(const std::string& filename);

/*
    Ajout un compte sous le même formt que précédement 
*/
void ajouteCompte(const string& filename, const BanqueAccount& account);

void supprimeCompte(const string& filename, const BanqueAccount& account);

