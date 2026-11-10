#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string customerName;
    double balance;
    int successfulDeposits;
    int successfulWithdrawals;
    int rejectedTransactions;
    bool created;

public:
    BankAccount()
        : accountNumber(""), customerName(""), balance(0.0),
          successfulDeposits(0), successfulWithdrawals(0),
          rejectedTransactions(0), created(false) {}

    bool isCreated() const { return created; }

    bool createAccount(const string& accNo, const string& name, double openingBalance) {
        if (accNo.empty() || name.empty()) {
            cout << "Error: Account number and customer name cannot be empty.\n";
            return false;
        }
        if (openingBalance < 0) {
            cout << "Error: Opening balance cannot be negative. Account not created.\n";
            return false;
        }
        accountNumber = accNo;
        customerName = name;
        balance = openingBalance;
        successfulDeposits = 0;
        successfulWithdrawals = 0;
        rejectedTransactions = 0;
        created = true;
        cout << "Account created successfully. Balance: " << balance << "\n";
        return true;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            ++rejectedTransactions;
            cout << "Rejected: invalid amount. Deposit must be greater than zero.\n";
            return;
        }
        balance += amount;
        ++successfulDeposits;
        cout << "Deposit successful. New balance: " << balance << "\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            ++rejectedTransactions;
            cout << "Rejected: invalid amount. Withdrawal must be greater than zero.\n";
            return;
        }
        if (amount > balance) {
            ++rejectedTransactions;
            cout << "Rejected: insufficient balance. Available: " << balance << "\n";
            return;
        }
        balance -= amount;
        ++successfulWithdrawals;
        cout << "Withdrawal successful. New balance: " << balance << "\n";
    }

    void checkBalance() const {
        cout << "Current balance: " << balance << "\n";
    }

    void displayAccount() const {
        cout << "Account Number : " << accountNumber << "\n"
             << "Customer Name  : " << customerName << "\n"
             << "Current Balance: " << balance << "\n";
    }

    void displayTransactionSummary() const {
        cout << "Successful deposits   : " << successfulDeposits << "\n"
             << "Successful withdrawals: " << successfulWithdrawals << "\n"
             << "Rejected transactions : " << rejectedTransactions << "\n"
             << "Final balance         : " << balance << "\n";
    }
};

template <typename T>
bool readNumber(T& value) {
    if (cin >> value) {
        return true;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

void showMenu() {
    cout << "\n===== SecureBank Menu =====\n"
         << "1. Create Account\n"
         << "2. Deposit Money\n"
         << "3. Withdraw Money\n"
         << "4. Balance Enquiry\n"
         << "5. Display Account Details\n"
         << "6. Display Transaction Summary\n"
         << "7. Exit\n"
         << "Enter choice: ";
}

int main() {
    BankAccount account;
    int choice = 0;

    cout << fixed << setprecision(2);

    do {
        showMenu();
        if (!readNumber(choice)) {
            cout << "Invalid menu choice. Please enter a number from 1 to 7.\n";
            choice = 0;
            continue;
        }

        if (choice >= 2 && choice <= 6 && !account.isCreated()) {
            cout << "Error: Please create an account first (option 1).\n";
            continue;
        }

        switch (choice) {
        case 1: {
            if (account.isCreated()) {
                cout << "An account already exists. Only one account is supported.\n";
                break;
            }
            string accNo, name;
            double opening;
            cout << "Enter account number: ";
            cin >> accNo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter customer name: ";
            getline(cin, name);
            cout << "Enter opening balance: ";
            if (!readNumber(opening)) {
                cout << "Error: Invalid amount entered. Account not created.\n";
                break;
            }
            account.createAccount(accNo, name, opening);
            break;
        }
        case 2: {
            double amount;
            cout << "Enter deposit amount: ";
            if (!readNumber(amount)) {
                cout << "Error: Invalid input. Please enter a number.\n";
                break;
            }
            account.deposit(amount);
            break;
        }
        case 3: {
            double amount;
            cout << "Enter withdrawal amount: ";
            if (!readNumber(amount)) {
                cout << "Error: Invalid input. Please enter a number.\n";
                break;
            }
            account.withdraw(amount);
            break;
        }
        case 4:
            account.checkBalance();
            break;
        case 5:
            account.displayAccount();
            break;
        case 6:
            account.displayTransactionSummary();
            break;
        case 7:
            cout << "Thank you for using SecureBank. Goodbye!\n";
            break;
        default:
            cout << "Invalid menu choice. Please enter a number from 1 to 7.\n";
        }
    } while (choice != 7);

    return 0;
}
