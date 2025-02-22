#include "Command.h"

Transaction* TransferCommand::execute() {
    // In a real system, you would verify accounts and balances here
    std::string description = "Transfer from " + sourceAccount + " to " + targetAccount;
    return new Transaction("TRANSFER", amount, sourceAccount, description);
}

Transaction* DepositCommand::execute() {
    std::string description = "Deposit to account " + accountId;
    return new Transaction("DEPOSIT", amount, accountId, description);
}

Transaction* WithdrawCommand::execute() {
    std::string description = "Withdrawal from account " + accountId;
    return new Transaction("WITHDRAW", amount, accountId, description);
} 