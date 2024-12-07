#include <bits/stdc++.h>
using namespace std;

class Account {
private:
    double balance;
    long account_number;
    string account_holder_name;
    string account_type;
    string bank_name;
    int maximum_deposit;
    int current_deposit = 0;
    int maximum_withdrawal;
    int current_withdrawal = 0;
    vector<string> transactions;

public:
    Account(double balance, long account_number, string account_holder_name, string account_type, string bank_name, int maximum_deposit, int maximum_withdrawal) {
        this->balance = balance;
        this->account_number = account_number;
        this->account_holder_name = account_holder_name;
        this->account_type = account_type;
        this->bank_name = bank_name;
        this->maximum_deposit = maximum_deposit;
        this->maximum_withdrawal = maximum_withdrawal;
    }

    double get_balance() const {
        return balance;
    }

    void add_deposit(int deposit) {
        current_deposit += deposit;
        balance += deposit;
        transactions.emplace_back("Amount deposited: " + to_string(deposit));
    }

    void add_withdrawal(int withdrawal) {
        current_withdrawal += withdrawal;
        balance -= withdrawal;
        transactions.emplace_back("Amount withdrawn: " + to_string(withdrawal));
    }

    int get_current_deposit() const {
        return current_deposit;
    }

    int get_current_withdrawal() const {
        return current_withdrawal;
    }

    int get_maximum_deposit() const {
        return maximum_deposit;
    }

    int get_maximum_withdrawal() const {
        return maximum_withdrawal;
    }

    const vector<string>& get_transactions() const {
        return transactions;
    }
};

class ATM {
private:
    string service_provider_name;
    int reserve;
    int atm_id;
    int minimum_deposit = 100;
    int minimum_withdrawal = 100;
    int maximum_reserve = 200000;
    string location;

public:
    ATM(string name, int reserve, int atm_id, string location)
        : service_provider_name(name), reserve(reserve), atm_id(atm_id), location(location) {}

    void deposit(int amount, Account& account) {
        if (reserve + amount > maximum_reserve || account.get_current_deposit() + amount > account.get_maximum_deposit()) {
            cout << "Cannot deposit. Exceeds limits.\n";
        } else {
            reserve += amount;
            account.add_deposit(amount);
            cout << "Deposit successful.\n";
        }
    }

    void withdraw(int amount, Account& account) {
        if (amount % 100 != 0) {
            cout << "Enter amount in multiples of 100.\n";
        } else if (amount > reserve) {
            cout << "ATM has insufficient cash.\n";
        } else if (account.get_current_withdrawal() + amount > account.get_maximum_withdrawal() || account.get_balance() < amount) {
            cout << "Cannot withdraw. Check limits or balance.\n";
        } else {
            reserve -= amount;
            account.add_withdrawal(amount);
            cout << "Withdrawal successful.\n";
        }
    }

    void check_balance(const Account& account) const {
        cout << "Account balance: " << account.get_balance() << " Rs\n";
    }

    void check_statement(const Account& account) const {
        cout << "Last 5 Transactions:\n";
        const vector<string>& transactions = account.get_transactions();
        int count = transactions.size();
        for (int i = max(0, count - 5); i < count; ++i) {
            cout << transactions[i] << "\n";
        }
    }

    string get_location() const {
        return location;
    }

    string get_service_provider_name() const {
        return service_provider_name;
    }

    int get_atm_id() const {
        return atm_id;
    }
};

void welcome(ATM& atm, Account& account) {
    cout << "Welcome to ATM of " << atm.get_service_provider_name() << " at " << atm.get_location() << ".\n";
    cout << "ATM ID: " << atm.get_atm_id() << "\n";
    while (true) {
        cout << "Please choose an option:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Balance Inquiry\n";
        cout << "4. View Mini Statement\n";
        cout << "5. Exit\n";

        int option;
        cin >> option;
        switch (option) {
            case 1: {
                cout << "Enter amount to deposit: ";
                int deposit_amount;
                cin >> deposit_amount;
                atm.deposit(deposit_amount, account);
                break;
            }
            case 2: {
                cout << "Enter amount to withdraw: ";
                int withdraw_amount;
                cin >> withdraw_amount;
                atm.withdraw(withdraw_amount, account);
                break;
            }
            case 3:
                atm.check_balance(account);
                break;
            case 4:
                atm.check_statement(account);
                break;
            case 5:
                cout << "Thank you! Goodbye.\n";
                return;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}

int main() {
    ATM atm("Axis Bank", 100000, 1000, "Tirupur");
    Account account(10000, 100000001, "Ajith Kumar", "Savings", "KVB", 50000, 5000);
    welcome(atm, account);
    return 0;
}
