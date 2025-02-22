#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <map>

class Account {
private:
    std::string accountId;
    double balance;

public:
    Account() : accountId(""), balance(0.0) {}
    
    Account(const std::string& id, double initialBalance = 0.0) 
        : accountId(id), balance(initialBalance) {}

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        balance += amount;
    }

    double getBalance() const { return balance; }
    std::string getId() const { return accountId; }
};

#endif 