#!/bin/bash

# Compile the program
g++ -std=c++11 main.cpp Transaction.cpp Command.cpp TransactionManager.cpp -o financial_program

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "\nCompilation successful! Running the program...\n"
    # Run the program
    ./financial_program
else
    echo -e "\nCompilation failed! Please check the errors above.\n"
fi 