#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class Transaction {
private:
    std::string operationType;
    double amount;
    std::string accountId;
    std::time_t timestamp;
    std::string description;

public:
    Transaction(const std::string& type, double amt, 
               const std::string& account, const std::string& desc);
    
    // Getters
    std::string getOperationType() const { return operationType; }
    double getAmount() const { return amount; }
    std::string getAccountId() const { return accountId; }
    std::time_t getTimestamp() const { return timestamp; }
    std::string getDescription() const { return description; }
    
    // For file operations
    std::string serialize() const;
    static Transaction* deserialize(const std::string& data);

    std::string getFormattedDateTime() const {
        char buffer[26];
        struct tm* timeinfo = localtime(&timestamp);
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }
};

#endif 