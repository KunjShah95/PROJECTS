#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
class Transaction {
public:
    std::string date;
    std::string description;
    double amount;
    std::string type; // "income" or "expense"

    Transaction(std::string d, std::string desc, double amt, std::string t)
        : date(d), description(desc), amount(amt), type(t) {}
};

class FinanceManager {
private:
    std::vector<Transaction> transactions;
    const std::string filename = "transactions.txt";

    void loadTransactions() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string date, description, type;
            double amount;
            while (file >> date >> description >> amount >> type) {
                transactions.emplace_back(date, description, amount, type);
            }
            file.close();
        }
    }

    void saveTransactions() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& transaction : transactions) {
                file << transaction.date << " "
                     << transaction.description << " "
                     << transaction.amount << " "
                     << transaction.type << "\n";
            }
            file.close();
        }
    }

public:
    FinanceManager() {
        loadTransactions();
    }

    ~FinanceManager() {
        saveTransactions();
    }

    void addTransaction() {
        std::string date, description, type;
        double amount;

        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
        std::cout << "Enter description: ";
        std::cin.ignore();
        std::getline(std::cin, description);
        std::cout << "Enter amount: ";
        std::cin >> amount;
        std::cout << "Enter type (income/expense): ";
        std::cin >> type;

        transactions.emplace_back(date, description, amount, type);
        std::cout << "Transaction added successfully!\n";
    }

    void viewTransactions() {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Date\t\tDescription\t\tAmount\tType\n";
        std::cout << "---------------------------------------------------\n";
        for (const auto& transaction : transactions) {
            std::cout << transaction.date << "\t" 
                      << transaction.description << "\t\t" 
                      << transaction.amount << "\t" 
                      << transaction.type << "\n";
        }
    }

    void deleteTransaction() {
        std::string date;
        std::cout << "Enter the date of the transaction to delete (YYYY-MM-DD): ";
        std::cin >> date;

        transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
            [&date](Transaction& t) { return t.date == date; }
            ));

        auto it = transactions.end();
        if (it != transactions.end()) {
            transactions.erase(it, transactions.end());
            std::cout << "Transaction deleted successfully!\n";
        } else {
            std::cout << "Transaction not found!\n";
        }
    }

    void generateReport() {
        double totalIncome = 0.0;
        double totalExpense = 0.0;

        for (const auto& transaction : transactions) {
            if (transaction.type == "income") {
                totalIncome += transaction.amount;
            } else if (transaction.type == "expense") {
                totalExpense += transaction.amount;
            }
        }

        std::cout << "Total Income: $" << totalIncome << "\n";
        std::cout << "Total Expense: $" << totalExpense << "\n";
        std::cout << "Net Savings: $" << (totalIncome - totalExpense) << "\n";
    }
};
int main() {
    FinanceManager manager;
    int choice;

    do {
        std::cout << "\nPersonal Finance Manager\n";
        std::cout << "1. Add Transaction\n";
        std::cout << "2. View Transactions\n";
        std::cout << "3. Delete Transaction\n";
        std::cout << "4. Generate Report\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager.addTransaction();
                break;
            case 2:
                manager.viewTransactions();
                break;
            case 3:
                manager.deleteTransaction();
                break;
            case 4:
                manager.generateReport();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}