#include "TransactionManager.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\n=== Financial Transaction System ===\n";
    std::cout << "1. Make a deposit\n";
    std::cout << "2. Make a withdrawal\n";
    std::cout << "3. Make a transfer\n";
    std::cout << "4. Search transactions by type\n";
    std::cout << "5. Search transactions by account\n";
    std::cout << "6. Search transactions by amount range\n";
    std::cout << "7. Display all transactions\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void handleDeposit(TransactionManager& manager) {
    std::string accountId;
    double amount;
    
    std::cout << "Enter account ID: ";
    std::cin >> accountId;
    
    if (manager.accountExists(accountId)) {
        std::cout << "Current balance: $" << manager.getAccountBalance(accountId) << "\n";
    }
    
    std::cout << "Enter amount to deposit: ";
    std::cin >> amount;
    
    if (amount > 0) {
        manager.executeCommand(new DepositCommand(accountId, amount));
        std::cout << "Deposit successful!\n";
        std::cout << "New balance: $" << manager.getAccountBalance(accountId) << "\n";
    } else {
        std::cout << "Invalid amount. Please enter a positive number.\n";
    }
    clearInputBuffer();
}

void handleWithdrawal(TransactionManager& manager) {
    std::string accountId;
    double amount;
    
    std::cout << "Enter account ID: ";
    std::cin >> accountId;
    
    if (manager.accountExists(accountId)) {
        std::cout << "Current balance: $" << manager.getAccountBalance(accountId) << "\n";
    } else {
        std::cout << "Account does not exist.\n";
        clearInputBuffer();
        return;
    }
    
    std::cout << "Enter amount to withdraw: ";
    std::cin >> amount;
    
    if (amount > 0) {
        if (manager.executeCommand(new WithdrawCommand(accountId, amount))) {
            std::cout << "Withdrawal successful!\n";
            std::cout << "New balance: $" << manager.getAccountBalance(accountId) << "\n";
        } else {
            std::cout << "Insufficient funds!\n";
        }
    } else {
        std::cout << "Invalid amount. Please enter a positive number.\n";
    }
    clearInputBuffer();
}

void handleTransfer(TransactionManager& manager) {
    std::string sourceAccount, targetAccount;
    double amount;
    
    std::cout << "Enter source account ID: ";
    std::cin >> sourceAccount;
    
    if (manager.accountExists(sourceAccount)) {
        std::cout << "Source account balance: $" << manager.getAccountBalance(sourceAccount) << "\n";
    } else {
        std::cout << "Source account does not exist.\n";
        clearInputBuffer();
        return;
    }
    
    std::cout << "Enter target account ID: ";
    std::cin >> targetAccount;
    
    std::cout << "Enter amount to transfer: ";
    std::cin >> amount;
    
    if (amount > 0) {
        if (manager.executeCommand(new TransferCommand(sourceAccount, targetAccount, amount))) {
            std::cout << "Transfer successful!\n";
            std::cout << "Source account new balance: $" << manager.getAccountBalance(sourceAccount) << "\n";
            std::cout << "Target account new balance: $" << manager.getAccountBalance(targetAccount) << "\n";
        } else {
            std::cout << "Transfer failed! Insufficient funds.\n";
        }
    } else {
        std::cout << "Invalid amount. Please enter a positive number.\n";
    }
    clearInputBuffer();
}

void handleSearchByType(TransactionManager& manager) {
    std::string type;
    std::cout << "Enter transaction type (DEPOSIT/WITHDRAW/TRANSFER): ";
    std::cin >> type;
    
    auto results = manager.searchByType(type);
    if (!results.empty()) {
        std::cout << "\nFound " << results.size() << " transactions:\n";
        for (const auto* trans : results) {
            std::cout << "Date: " << trans->getFormattedDateTime()
                      << "\nAmount: $" << trans->getAmount() 
                      << "\nAccount: " << trans->getAccountId()
                      << "\nDescription: " << trans->getDescription()
                      << "\nCurrent Balance: $" << manager.getAccountBalance(trans->getAccountId())
                      << "\n-------------------\n";
        }
    }
    clearInputBuffer();
}

void handleSearchByAccount(TransactionManager& manager) {
    std::string accountId;
    std::cout << "Enter account ID: ";
    std::cin >> accountId;
    
    auto results = manager.searchByAccount(accountId);
    if (!results.empty()) {
        std::cout << "\nFound " << results.size() << " transactions:\n";
        for (const auto* trans : results) {
            std::cout << "Date: " << trans->getFormattedDateTime()
                      << "\nType: " << trans->getOperationType()
                      << "\nAmount: $" << trans->getAmount()
                      << "\nDescription: " << trans->getDescription()
                      << "\nCurrent Balance: $" << manager.getAccountBalance(trans->getAccountId())
                      << "\n-------------------\n";
        }
    }
    clearInputBuffer();
}

void handleSearchByAmount(TransactionManager& manager) {
    double minAmount, maxAmount;
    std::cout << "Enter minimum amount: ";
    std::cin >> minAmount;
    std::cout << "Enter maximum amount: ";
    std::cin >> maxAmount;
    
    auto results = manager.searchByAmount(minAmount, maxAmount);
    if (!results.empty()) {
        std::cout << "\nFound " << results.size() << " transactions:\n";
        for (const auto* trans : results) {
            std::cout << "Date: " << trans->getFormattedDateTime()
                      << "\nType: " << trans->getOperationType()
                      << "\nAmount: $" << trans->getAmount()
                      << "\nAccount: " << trans->getAccountId()
                      << "\nCurrent Balance: $" << manager.getAccountBalance(trans->getAccountId())
                      << "\n-------------------\n";
        }
    }
    clearInputBuffer();
}

int main() {
    TransactionManager manager("transactions.txt");
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                handleDeposit(manager);
                break;
            case 2:
                handleWithdrawal(manager);
                break;
            case 3:
                handleTransfer(manager);
                break;
            case 4:
                handleSearchByType(manager);
                break;
            case 5:
                handleSearchByAccount(manager);
                break;
            case 6:
                handleSearchByAmount(manager);
                break;
            case 7:
                manager.printTransactions();
                break;
            case 0:
                std::cout << "Thank you for using the Financial Transaction System!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
} 