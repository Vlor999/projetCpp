#pragma once
#include <string>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;

namespace uuid {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 15);
    static uniform_int_distribution<> dis2(8, 11);

    inline std::string generate_uuid_v4() {
        stringstream ss;
        ss << hex;
        for (int i = 0; i < 8; i++) ss << dis(gen);
        ss << "-";
        for (int i = 0; i < 4; i++) ss << dis(gen);
        ss << "-4";
        for (int i = 0; i < 3; i++) ss << dis(gen);
        ss << "-";
        ss << dis2(gen);
        for (int i = 0; i < 3; i++) ss << dis(gen);
        ss << "-";
        for (int i = 0; i < 12; i++) ss << dis(gen);
        return ss.str();
    }
}

class BanqueAccount {
    
private:
    string name;
    double amount;
    string id;
    bool isAccount = true;

public:
    BanqueAccount(const std::string& name, double initialAmount, const std::string& id)
        : name(name), amount(initialAmount), id(id) {}

    BanqueAccount(const std::string& name, double initialAmount)
        : name(name), amount(initialAmount), id(uuid::generate_uuid_v4()) {}

    BanqueAccount(const std::string& name) : BanqueAccount(name, 0) {}

    BanqueAccount() : BanqueAccount("Compte inconnu") {this->isAccount = false;}

    std::string getName() const { 
        return name; 
    }

    double getAmount() const { 
        return amount; 
    }

    std::string getId() const { 
        return id; 
    }

    bool isAccountExist() const {
        return isAccount;
    }

    void setName(const std::string& newName) { 
        name = newName; 
    }

    void deposit(double value) { 
        amount += value; 
    }

    bool withdraw(double value) {
        if (value > amount) return false;
        amount -= value;
        return true;
    }

    void display() const {
        cout << "Compte: " << name << " (ID: " << id << ")\n"
             << "Solde: " << amount << " €" << endl;
    }

    bool operator==(const BanqueAccount& other) const {
        return this->id == other.id;
    }
};
