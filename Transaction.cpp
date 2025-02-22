#include "Transaction.h"
#include <sstream>

Transaction::Transaction(const std::string& type, double amt, 
                       const std::string& account, const std::string& desc)
    : operationType(type)
    , amount(amt)
    , accountId(account)
    , description(desc) {
    timestamp = std::time(nullptr);
}

std::string Transaction::serialize() const {
    std::stringstream ss;
    ss << operationType << "|"
       << amount << "|"
       << accountId << "|"
       << timestamp << "|"
       << description;
    return ss.str();
}

Transaction* Transaction::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string type, account, desc;
    double amt;
    std::time_t time;
    
    std::getline(ss, type, '|');
    ss >> amt;
    ss.ignore();
    std::getline(ss, account, '|');
    ss >> time;
    ss.ignore();
    std::getline(ss, desc);
    
    Transaction* trans = new Transaction(type, amt, account, desc);
    trans->timestamp = time;
    return trans;
} 