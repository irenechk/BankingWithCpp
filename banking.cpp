#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    double principal;
    double rate;
    double time;
    double interest;

public:

    // Create account
    void createAccount() {
        cout << "\nEnter Customer Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        if(cin.fail()){
            cout << "Invalid account number!\n";
            cin.clear();
            cin.ignore(1000,'\n');
            return;
        }

        cout << "Enter Deposit Amount (Principal ₹): ";
        cin >> principal;

        if(principal < 0){
            cout << "Deposit cannot be negative!\n";
            principal = 0;
        }
    }

    // Input interest details
    void inputInterestDetails() {
        cout << "\nEnter Rate of Interest (% per annum): ";
        cin >> rate;

        if(rate < 0){
            cout << "Rate cannot be negative!\n";
            rate = 0;
        }

        cout << "Enter Time Period (in years): ";
        cin >> time;

        if(time < 0){
            cout << "Time cannot be negative!\n";
            time = 0;
        }
    }

    // Calculate simple interest
    void calculateInterest() {
        interest = (principal * rate * time) / 100;
    }

    // Display result
    void displayInterest() {
        cout << fixed << setprecision(2);
        cout << "\n----- Interest Details -----\n";
        cout << "Customer Name: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Principal Amount: ₹" << principal << endl;
        cout << "Simple Interest: ₹" << interest << endl;
        cout << "Total Amount After Interest: ₹" << principal + interest << endl;
    }

    // Deposit money
    void depositMoney() {
        int acc;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> acc;

        if(acc != accountNumber){
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter amount to deposit: ₹";
        cin >> amount;

        if(amount <= 0){
            cout << "Invalid deposit amount!\n";
            return;
        }

        principal += amount;
        cout << "Deposit successful! New Balance: ₹" << principal << endl;
    }

    // Withdraw money
    void withdrawMoney() {
        int acc;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> acc;

        if(acc != accountNumber){
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter amount to withdraw: ₹";
        cin >> amount;

        if(amount <= 0){
            cout << "Invalid withdrawal amount!\n";
            return;
        }

        if(amount > principal){
            cout << "Insufficient balance!\n";
            return;
        }

        principal -= amount;
        cout << "Withdrawal successful! Remaining Balance: ₹" << principal << endl;
    }

    // Search account
    void searchAccount() {
        int acc;

        cout << "\nEnter Account Number to search: ";
        cin >> acc;

        if(acc == accountNumber){
            cout << "\nAccount Found!\n";
            cout << "Customer Name: " << name << endl;
            cout << "Account Number: " << accountNumber << endl;
            cout << "Balance: ₹" << principal << endl;
        }
        else{
            cout << "Account not found!\n";
        }
    }

    // Save data to file
    void saveRecord() {
        ofstream file("bank_records.txt", ios::app);

        if(file.is_open()) {
            file << "Name: " << name
                 << " | Account No: " << accountNumber
                 << " | Principal: ₹" << principal
                 << " | Rate: " << rate
                 << "% | Time: " << time
                 << " years | Interest: ₹" << interest
                 << " | Total: ₹" << principal + interest
                 << endl;

            file.close();
            cout << "\nRecord saved successfully!\n";
        } else {
            cout << "\nError saving record.\n";
        }
    }

    // View saved records
    void viewRecords() {
        ifstream file("bank_records.txt");
        string line;

        cout << "\n====== BANK RECORDS ======\n";

        if(file.is_open()) {
            while(getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "No records found.\n";
        }
    }
};

int main() {

    BankAccount account;
    int choice;

    do {
        cout << "\n======= MINI BANKING SYSTEM =======\n";
        cout << "1. Create Account\n";
        cout << "2. Calculate Simple Interest\n";
        cout << "3. View Saved Records\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Search Account\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()){
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(1000,'\n');
            continue;
        }

        switch(choice) {

            case 1:
                account.createAccount();
                break;

            case 2:
                account.inputInterestDetails();
                account.calculateInterest();
                account.displayInterest();
                account.saveRecord();
                break;

            case 3:
                account.viewRecords();
                break;

            case 4:
                account.depositMoney();
                break;

            case 5:
                account.withdrawMoney();
                break;

            case 6:
                account.searchAccount();
                break;

            case 7:
                cout << "\nThank you for using the banking system!\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } while(choice != 7);

    return 0;
}
