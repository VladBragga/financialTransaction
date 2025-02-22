#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <deque>
#include <string>
#include <vector>
#include <map>
#include "Command.h"
#include "Transaction.h"
#include "Account.h"

class TransactionManager {
private:
    std::deque<Transaction*> transactions;
    std::string transactionFile;
    std::map<std::string, Account> accounts;

public:
    explicit TransactionManager(const std::string& filename);
    ~TransactionManager();

    // Command execution
    bool executeCommand(Command* command);
    
    // Account operations
    bool accountExists(const std::string& accountId) const;
    double getAccountBalance(const std::string& accountId) const;
    void createAccountIfNotExists(const std::string& accountId);
    bool canWithdraw(const std::string& accountId, double amount) const;
    
    // File operations
    void loadTransactions();
    void saveTransactions();
    
    // Search operations
    std::vector<Transaction*> searchByType(const std::string& type) const;
    std::vector<Transaction*> searchByAccount(const std::string& accountId) const;
    std::vector<Transaction*> searchByAmount(double minAmount, double maxAmount) const;
    
    // Utility functions
    void printTransactions() const;
};

#endif 