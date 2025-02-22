#ifndef COMMAND_H
#define COMMAND_H

#include "Transaction.h"

class Command {
public:
    virtual ~Command() = default;
    virtual Transaction* execute() = 0;
};

class TransferCommand : public Command {
private:
    std::string sourceAccount;
    std::string targetAccount;
    double amount;

public:
    TransferCommand(const std::string& from, const std::string& to, double amt)
        : sourceAccount(from), targetAccount(to), amount(amt) {}
    
    Transaction* execute() override;
};

class DepositCommand : public Command {
private:
    std::string accountId;
    double amount;

public:
    DepositCommand(const std::string& account, double amt)
        : accountId(account), amount(amt) {}
    
    Transaction* execute() override;
};

class WithdrawCommand : public Command {
private:
    std::string accountId;
    double amount;

public:
    WithdrawCommand(const std::string& account, double amt)
        : accountId(account), amount(amt) {}
    
    Transaction* execute() override;
};

#endif 