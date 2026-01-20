#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class BankAccount {
protected:
    int accNo;
    string name;
    double balance;

public:
    BankAccount(int a, string n, double b) {
        accNo = a;
        name = n;
        balance = b;
    }

    virtual ~BankAccount() {}

    int getAccNo() {
        return accNo;
    }

    void deposit(double amt) {
        balance += amt;
        cout << "Deposit Successful!\n";
    }

    virtual void withdraw(double amt) {
        if (amt <= balance) {
            balance -= amt;
            cout << "Withdraw Successful!\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    virtual void calculateInterest() = 0;

    void showInfo() {
        cout << "\nAccount No  : " << accNo;
        cout << "\nHolder Name: " << name;
        cout << "\nBalance    : " << balance << endl;
    }
};


class Savings : public BankAccount {
    double rate;

public:
    Savings(int a, string n, double b, double r)
        : BankAccount(a, n, b) {
        rate = r;
    }

    void calculateInterest() override {
        double interest = balance * rate / 100;
        cout << "Savings Interest: " << interest << endl;
    }
};


class Checking : public BankAccount {
    double overdraft;

public:
    Checking(int a, string n, double b, double o)
        : BankAccount(a, n, b) {
        overdraft = o;
    }

    void withdraw(double amt) override {
        if (amt <= balance + overdraft) {
            balance -= amt;
            cout << "Withdraw Successful (Overdraft Used)\n";
        } else {
            cout << "Overdraft Limit Exceeded!\n";
        }
    }

    void calculateInterest() override {
        cout << "Checking Account has no interest.\n";
    }
};

class FixedDeposit : public BankAccount {
    int months;

public:
    FixedDeposit(int a, string n, double b, int m)
        : BankAccount(a, n, b) {
        months = m;
    }

    void calculateInterest() override {
        double interest = balance * 0.07 * months / 12;
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

BankAccount* findAccount(vector<unique_ptr<BankAccount>>& list, int no) {
    for (auto& acc : list) {
        if (acc->getAccNo() == no)
            return acc.get();
    }
    return nullptr;
}


int main() {
    vector<unique_ptr<BankAccount>> accounts;
    int choice;

    do {
        cout << "\n--- BANK MENU ---\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Deposit\n";
        cout << "5. Withdraw\n";
        cout << "6. Display Info\n";
        cout << "7. Calculate Interest\n";
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        int accNo, months;
        string name;
        double bal, rate, overdraft, amt;

        BankAccount* acc = nullptr;

        switch (choice) {
        case 1:
            cout << "Enter Acc No: ";
            cin >> accNo;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Balance: ";
            cin >> bal;
            cout << "Enter Interest Rate: ";
            cin >> rate;

            accounts.push_back(make_unique<Savings>(accNo, name, bal, rate));
            break;

        case 2:
            cout << "Enter Acc No: ";
            cin >> accNo;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Balance: ";
            cin >> bal;
            cout << "Enter Overdraft Limit: ";
            cin >> overdraft;

            accounts.push_back(make_unique<Checking>(accNo, name, bal, overdraft));
            break;

        case 3:
            cout << "Enter Acc No: ";
            cin >> accNo;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Balance: ";
            cin >> bal;
            cout << "Enter Term (Months): ";
            cin >> months;

            accounts.push_back(make_unique<FixedDeposit>(accNo, name, bal, months));
            break;

        case 4:
            cout << "Enter Acc No: ";
            cin >> accNo;
            acc = findAccount(accounts, accNo);
            if (acc) {
                cout << "Enter Amount: ";
                cin >> amt;
                acc->deposit(amt);
            } else {
                cout << "Account Not Found!\n";
            }
            break;

        case 5:
            cout << "Enter Acc No: ";
            cin >> accNo;
            acc = findAccount(accounts, accNo);
            if (acc) {
                cout << "Enter Amount: ";
                cin >> amt;
                acc->withdraw(amt);
            } else {
                cout << "Account Not Found!\n";
            }
            break;

        case 6:
            cout << "Enter Acc No: ";
            cin >> accNo;
            acc = findAccount(accounts, accNo);
            if (acc)
                acc->showInfo();
            else
                cout << "Account Not Found!\n";
            break;

        case 7:
            cout << "Enter Acc No: ";
            cin >> accNo;
            acc = findAccount(accounts, accNo);
            if (acc)
                acc->calculateInterest();
            else
                cout << "Account Not Found!\n";
            break;
        }

    } while (choice != 0);

    return 0;
}