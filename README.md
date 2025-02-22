# Financial Transaction System

A C++ command-line application for managing financial transactions with features for deposits, withdrawals, and transfers between accounts. The system maintains transaction history and account balances persistently.

## Features

### Transaction Operations

- **Deposit**: Add funds to any account
- **Withdrawal**: Remove funds from an account (with balance check)
- **Transfer**: Move funds between accounts
- **Balance Tracking**: Real-time balance updates for all accounts

### Search and Display

- View complete transaction history
- Search transactions by:
  - Transaction type (DEPOSIT/WITHDRAW/TRANSFER)
  - Account ID
  - Amount range

### Data Persistence

- All transactions are saved automatically
- Transaction history is maintained between sessions
- Account balances are preserved

## Getting Started

### Prerequisites

- C++11 compatible compiler (g++)
- Terminal/Command Line Interface

### Installation

1. Clone or download the project files
2. Ensure all source files are in the same directory:
   - main.cpp
   - Transaction.cpp/.h
   - Command.cpp/.h
   - TransactionManager.cpp/.h
   - Account.h

### Running the Program

Execute the start script:

```bash
./start.sh
```

This will compile the program and run it.
