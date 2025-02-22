#include "TransactionManager.h"
#include <fstream>
#include <iostream>

TransactionManager::TransactionManager(const std::string& filename)
    : transactionFile(filename) {
    loadTransactions();
}

TransactionManager::~TransactionManager() {
    saveTransactions();
    for (auto* trans : transactions) {
        delete trans;
    }
}

bool TransactionManager::executeCommand(Command* command) {
    Transaction* transaction = command->execute();
    
    // Update account balances based on transaction type
    std::string type = transaction->getOperationType();
    std::string accountId = transaction->getAccountId();
    double amount = transaction->getAmount();

    createAccountIfNotExists(accountId);

    if (type == "WITHDRAW") {
        if (!canWithdraw(accountId, amount)) {
            delete transaction;
            delete command;
            return false;
        }
        accounts[accountId].withdraw(amount);
    }
    else if (type == "DEPOSIT") {
        accounts[accountId].deposit(amount);
    }
    else if (type == "TRANSFER") {
        std::string targetAccount = transaction->getDescription().substr(
            transaction->getDescription().find("to ") + 3);
        
        if (!canWithdraw(accountId, amount)) {
            delete transaction;
            delete command;
            return false;
        }
        
        createAccountIfNotExists(targetAccount);
        accounts[accountId].withdraw(amount);
        accounts[targetAccount].deposit(amount);
    }

    transactions.push_back(transaction);
    saveTransactions();
    delete command;
    return true;
}

void TransactionManager::loadTransactions() {
    std::ifstream file(transactionFile);
    std::string line;
    
    // Clear existing transactions and accounts
    for (auto* trans : transactions) {
        delete trans;
    }
    transactions.clear();
    accounts.clear();
    
    // Check if file exists and is not empty
    if (!file.is_open()) {
        std::ofstream createFile(transactionFile);  // Create empty file if it doesn't exist
        return;
    }
    
    // Check if file is empty
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        return;  // Return if file is empty
    }
    file.seekg(0, std::ios::beg);  // Reset to beginning of file
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Transaction* trans = Transaction::deserialize(line);
            transactions.push_back(trans);
            
            // Update account balances based on transaction type
            std::string type = trans->getOperationType();
            std::string accountId = trans->getAccountId();
            double amount = trans->getAmount();
            
            createAccountIfNotExists(accountId);
            
            if (type == "WITHDRAW") {
                accounts[accountId].withdraw(amount);
            }
            else if (type == "DEPOSIT") {
                accounts[accountId].deposit(amount);
            }
            else if (type == "TRANSFER") {
                std::string targetAccount = trans->getDescription().substr(
                    trans->getDescription().find("to ") + 3);
                createAccountIfNotExists(targetAccount);
                accounts[accountId].withdraw(amount);
                accounts[targetAccount].deposit(amount);
            }
        }
    }
}

void TransactionManager::saveTransactions() {
    std::ofstream file(transactionFile);
    
    for (const auto* trans : transactions) {
        file << trans->serialize() << std::endl;
    }
}

void TransactionManager::printTransactions() const {
    if (transactions.empty()) {
        std::cout << "\nTransaction history is empty.\n";
        return;
    }

    std::cout << "\nAll Transactions:\n";
    for (const auto* trans : transactions) {
        std::cout << "Date: " << trans->getFormattedDateTime()
                  << "\nType: " << trans->getOperationType()
                  << "\nAmount: $" << trans->getAmount()
                  << "\nAccount: " << trans->getAccountId()
                  << "\nDescription: " << trans->getDescription()
                  << "\nCurrent Balance: $" << getAccountBalance(trans->getAccountId())
                  << "\n-------------------\n";
    }
}

bool TransactionManager::accountExists(const std::string& accountId) const {
    return accounts.find(accountId) != accounts.end();
}

double TransactionManager::getAccountBalance(const std::string& accountId) const {
    auto it = accounts.find(accountId);
    return it != accounts.end() ? it->second.getBalance() : 0.0;
}

void TransactionManager::createAccountIfNotExists(const std::string& accountId) {
    if (!accountExists(accountId)) {
        accounts.insert(std::make_pair(accountId, Account(accountId)));
    }
}

bool TransactionManager::canWithdraw(const std::string& accountId, double amount) const {
    auto it = accounts.find(accountId);
    return it != accounts.end() && it->second.getBalance() >= amount;
}

std::vector<Transaction*> TransactionManager::searchByType(const std::string& type) const {
    std::vector<Transaction*> result;
    for (auto* trans : transactions) {
        if (trans->getOperationType() == type) {
            result.push_back(trans);
        }
    }
    if (result.empty()) {
        std::cout << "\nNo transactions found of type '" << type << "'.\n";
    }
    return result;
}

std::vector<Transaction*> TransactionManager::searchByAccount(const std::string& accountId) const {
    std::vector<Transaction*> result;
    for (auto* trans : transactions) {
        if (trans->getAccountId() == accountId) {
            result.push_back(trans);
        }
    }
    if (result.empty()) {
        std::cout << "\nNo transactions found for account '" << accountId << "'.\n";
    }
    return result;
}

std::vector<Transaction*> TransactionManager::searchByAmount(double minAmount, double maxAmount) const {
    std::vector<Transaction*> result;
    for (auto* trans : transactions) {
        double amount = trans->getAmount();
        if (amount >= minAmount && amount <= maxAmount) {
            result.push_back(trans);
        }
    }
    if (result.empty()) {
        std::cout << "\nNo transactions found in the range $" << minAmount 
                  << " to $" << maxAmount << ".\n";
    }
    return result;
} 