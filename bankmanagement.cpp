#include <iostream>
#include <fstream>
#include <string>

struct Account {
    int accountNumber;
    std::string accountHolderName;
    double balance;
    Account* next;
};

class Bank {
private:
    Account* head;

public:
    Bank();
    ~Bank();

    void createAccount();
    void depositMoney();
    Account* searchAccount(int accountNumber);
    void checkBalance();
    void withdrawMoney();
    void transferMoney();
    void saveAccountDetails(Account* account);
    void saveTransaction(int accountNumber, std::string transactionType, double amount);
};

Bank::Bank() {
    head = nullptr;
}

Bank::~Bank() {
    Bank::~Bank(); {
    Account* current = head;
    while (current != nullptr) {
        Account* next = current->next;
        delete current;
        current = next;
    }
}

}

void Bank::createAccount() {
    Account* newAccount = new Account;
    std::cout << "Enter Account Number: ";
    std::cin >> newAccount->accountNumber;
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter Account Holder Name: ";
    std::getline(std::cin, newAccount->accountHolderName);
    newAccount->balance = 0.0;
    newAccount->next = head;
    head = newAccount;
    saveAccountDetails(newAccount);
    std::cout << "Account created successfully." << std::endl;
}

void Bank::depositMoney() {
    int accountNumber;
    double amount;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    Account* account = searchAccount(accountNumber);
    if (account != nullptr) {
        std::cout << "Enter Deposit Amount: ";
        std::cin >> amount;
        account->balance += amount;
        saveTransaction(accountNumber, "Deposit", amount);
        saveAccountDetails(account);
        std::cout << "Amount deposited successfully." << std::endl;
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

Account* Bank::searchAccount(int accountNumber) {
    Account* current = head;
    while (current != nullptr) {
        if (current->accountNumber == accountNumber) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Bank::checkBalance() {
    int accountNumber;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    Account* account = searchAccount(accountNumber);
    if (account != nullptr) {
        std::cout << "Account Holder: " << account->accountHolderName << std::endl;
        std::cout << "Account Balance: " << account->balance << std::endl;
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

void Bank::withdrawMoney() {
    int accountNumber;
    double amount;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    Account* account = searchAccount(accountNumber);
    if (account != nullptr) {
        std::cout << "Enter Withdrawal Amount: ";
        std::cin >> amount;
        if (account->balance >= amount) {
            account->balance -= amount;
            saveTransaction(accountNumber, "Withdrawal", amount);
            saveAccountDetails(account);
            std::cout << "Amount withdrawn successfully." << std::endl;
        } else {
            std::cout << "Insufficient balance." << std::endl;
        }
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

void Bank::transferMoney() {
    int fromAccountNumber, toAccountNumber;
    double amount;
    std::cout << "Enter From Account Number: ";
    std::cin >> fromAccountNumber;
    std::cout << "Enter To Account Number: ";
    std::cin >> toAccountNumber;
    Account* fromAccount = searchAccount(fromAccountNumber);
    Account* toAccount = searchAccount(toAccountNumber);
    if (fromAccount != nullptr && toAccount != nullptr) {
        std::cout << "Enter Transfer Amount: ";
        std::cin >> amount;
        if (fromAccount->balance >= amount) {
            fromAccount->balance -= amount;
            toAccount->balance += amount;
            saveTransaction(fromAccountNumber, "Transfer (To: " + std::to_string(toAccountNumber) + ")", amount);
            saveTransaction(toAccountNumber, "Transfer (From: " + std::to_string(fromAccountNumber) + ")", amount);
            saveAccountDetails(fromAccount);
            saveAccountDetails(toAccount);
            std::cout << "Amount transferred successfully." << std::endl;
        } else {
            std::cout << "Insufficient balance for transfer." << std::endl;
        }
    } else {
        std::cout << "Invalid account numbers." << std::endl;
    }
}

void Bank::saveAccountDetails(Account* account) {
    std::ofstream outfile("accounts.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "Account Number: " << account->accountNumber << "\n";
        outfile << "Account Holder Name: " << account->accountHolderName << "\n";
        outfile << "Balance: " << account->balance << "\n";
        outfile << "-------------------------\n";
        outfile.close();
        std::cout << "Account details saved successfully." << std::endl;
    } else {
        std::cout << "Unable to save account details." << std::endl;
    }
}

void Bank::saveTransaction(int accountNumber, std::string transactionType, double amount) {
    std::ofstream outfile("transactions.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "Account Number: " << accountNumber << "\n";
        outfile << "Transaction Type: " << transactionType << "\n";
        outfile << "Amount: " << amount << "\n";
        outfile << "-------------------------\n";
        outfile.close();
        std::cout << "Transaction saved successfully." << std::endl;
    } else {
        std::cout << "Unable to save transaction." << std::endl;
    }
}

int main() {
    Bank bank;
    int choice;
    do {
        std::cout << "\nBank Management System Menu:\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Transfer Money\n";
        std::cout << "5. Check Balance\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositMoney();
                break;
            case 3:
                bank.withdrawMoney
();
                break;
            case 4:
                bank.transferMoney();
                break;
            case 5:
                bank.checkBalance();
                break;
            case 6:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
