//ZAQ Bank System
//Zulqarnain Saeed  


#include <iostream>
#include <fstream>
using namespace std;


//this one is saving customers in file
void saveCustomers(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int userCount) {
    ofstream fout("customers.txt");
    for (int i = 0; i < userCount; i++) {
        fout << names[i] << ',' << accNums[i] << ',' << pins[i] << ',' << balances[i] << ','
            << cnics[i] << ',' << ages[i] << ',' << incomes[i] << '\n';
    }
    fout.close();
}
//this one is loading customer from files into arrays and variables
void loadCustomers(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int* userCount) {
    ifstream fin("customers.txt");
    *userCount = 0;
    while (fin.getline(names[*userCount], 50, ',')) {
        fin.getline(accNums[*userCount], 20, ',');
        fin.getline(pins[*userCount], 20, ',');
        fin >> balances[*userCount];
        fin.ignore();
        fin.getline(cnics[*userCount], 20, ',');
        fin >> ages[*userCount];
        fin.ignore();
        fin >> incomes[*userCount];
        fin.ignore();
        (*userCount)++;
    }
    fin.close();
}
//this one is use for search operation if we want index of customer
int getUserIndexByAcc(const char acc[], char accNums[][20], int userCount) {
    for (int i = 0; i < userCount; i++) {
        int match = 1;
        int j = 0;
        while (acc[j] != '\0' || accNums[i][j] != '\0') {
            if (acc[j] != accNums[i][j]) {
                match = 0;
                break;
            }
            j++;
        }
        if (match) return i;
    }
    return -1;
}
//this one is recording transaction in file
void recordTransaction(const char acc[], const char type[], int amount) {
    ofstream fout("transactions.txt", ios::app);
    fout << acc << ',' << type << ',' << amount << '\n';
    fout.close();
}
//this will show all account information
void viewAccountInfo(int index, char names[][50], char accNums[][20], char cnics[][20],
    int ages[], int incomes[], int balances[]) {
    cout << "\nName: " << names[index] << endl;
    cout << "Account Number: " << accNums[index] << endl;
    cout << "CNIC: " << cnics[index] << endl;
    cout << "Age: " << ages[index] << endl;
    cout << "Income: Rs. " << incomes[index] << endl;
    cout << "Balance: Rs. " << balances[index] << endl;
}
//this will show you the transaction history
void viewTransactionHistory(const char acc[]) {
    ifstream fin("transactions.txt");
    char line[100];
    cout << "\n--- Transaction History ---\n";
    while (fin.getline(line, 100)) {
        int match = 1;
        int i = 0;
        while (acc[i] != '\0') {
            if (line[i] != acc[i]) {
                match = 0;
                break;
            }
            i++;
        }
        if (match && line[i] == ',') {
            cout << line << endl;
        }
    }
    fin.close();
}

//this is chatbot that answer queries
void showChatbot() {
    int choice;

    cout << "\n--- Chatbot Assistance ---\n";
    cout << "1. How to deposit money?\n";
    cout << "2. How to change PIN?\n";
    cout << "3. How to check balance?\n";
    cout << "4. How to transfer money?\n";
    cout << "5. How to apply for a loan?\n";
    cout << "6. How to use currency converter?\n";
    cout << "7. How to view transaction history?\n";
    cout << "8. How to update account information?\n";

    cout << "\nEnter the number of the question you want to ask: ";
    cin >> choice;

    cout << "\nAnswer:\n";
    switch (choice) {
    case 1:
        cout << "Go to 'Deposit' option in your panel and enter the amount to deposit.\n";
        break;
    case 2:
        cout << "Select 'Change PIN', then enter a new valid PIN (min 8 chars with '@', '#' or '$').\n";
        break;
    case 3:
        cout << "Choose 'Check Balance' in the customer panel to see your current balance.\n";
        break;
    case 4:
        cout << "Select 'Transfer Money', enter receiver's account number and the amount to send.\n";
        break;
    case 5:
        cout << "Go to 'Loan Check' option. If your income is above 30000 and age > 19, you're eligible.\n";
        break;
    case 6:
        cout << "Choose 'Currency Convert' and enter amount + desired currency to convert it into PKR.\n";
        break;
    case 7:
        cout << "Go to 'Transaction History' to view all past deposits, withdrawals, and transfers.\n";
        break;
    case 8:
        cout << "Only bank employees can update account info via the 'Update Info' option in employee panel.\n";
        break;
    default:
        cout << "Invalid question number.\n";
    }
}

//this is currency converter if you want to check money in another formate
void currencyConverter() {
    double amount; int choice;
    cout << "\n--- Currency Converter ---\nEnter amount: "; cin >> amount;
    cout << "Select currency:\n1. USD\n2. GBP\n3. EUR\n4. INR\nChoice: "; cin >> choice;
    double pkr = 0;
    if (choice == 1) pkr = amount * 278;
    else if (choice == 2) pkr = amount * 351;
    else if (choice == 3) pkr = amount * 297;
    else if (choice == 4) pkr = amount * 3.34;
    else { cout << "Invalid choice."; return; }
    cout << "Equivalent in PKR: Rs. " << pkr << endl;
}
//this is loan eligibility checker 
void checkLoanEligibility(int index, int incomes[], int ages[]) {
    if (incomes[index] >= 30000 && ages[index] > 19)
        cout << "You are eligible for a loan.\n";
    else
        cout << "You are not eligible for a loan.\n";
}
//this will transfer money from one account to other
void transferMoney(int senderIndex, char accNums[][20], char pins[][20], int balances[],
    char names[][50], char cnics[][20], int ages[], int incomes[],
    int userCount) {
    char recvAcc[20];
    int amount;

    cout << "Enter receiver account number: ";
    cin >> recvAcc;

    int recvIndex = getUserIndexByAcc(recvAcc, accNums, userCount);
    if (recvIndex == -1) {
        cout << "Receiver not found.\n";
        return;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    if (amount > balances[senderIndex]) {
        cout << "Insufficient funds.\n";
        return;
    }

    balances[senderIndex] -= amount;
    balances[recvIndex] += amount;

    saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, userCount);

    recordTransaction(accNums[senderIndex], "TransferOut", amount);
    recordTransaction(accNums[recvIndex], "TransferIn", amount);

    cout << "Transfer successful.\n";
}

//checking the validity of pin
int isValidPIN(const char pin[]) {
    int length = 0, hasSpecial = 0;
    for (int i = 0; pin[i] != '\0'; i++) {
        length++;
        if (pin[i] == '@' || pin[i] == '#' || pin[i] == '$') {
            hasSpecial = 1;
        }
    }
    return (length >= 8 && hasSpecial);

}
//this is the customer menu
void customerMenu(int index, char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int userCount) {
    int choice;

    do {
        cout << "\n--- Customer Panel ---\n";
        cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. View Info\n5. Change PIN\n6. Chatbot\n7. Currency Convert\n";
        cout << "8. Loan Check\n9. Transfer Money\n10. Transaction History\n11. Logout\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int* ptr = &balances[index];
            cout << "Current Balance: Rs. " << *ptr << endl;
        }
        else if (choice == 2) {
            int amt;
            cout << "Enter amount to deposit: ";
            cin >> amt;
            balances[index] += amt;

            saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, userCount);
            recordTransaction(accNums[index], "Deposit", amt);
            cout << "Deposited successfully.\n";
        }
        else if (choice == 3) {
            int amt;
            cout << "Enter amount to withdraw: ";
            cin >> amt;

            if (amt <= balances[index]) {
                balances[index] -= amt;
                saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, userCount);
                recordTransaction(accNums[index], "Withdraw", amt);
                cout << "Withdrawn successfully.\n";
            }
            else {
                cout << "Insufficient balance.\n";
            }
        }
        else if (choice == 4) {
            viewAccountInfo(index, names, accNums, cnics, ages, incomes, balances);
        }
        else if (choice == 5) {
            char newPin[20];
            cout << "Enter new PIN: ";
            cin >> newPin;

            if (!isValidPIN(newPin)) {
                cout << "PIN must be at least 8 characters long and contain '@', '#' or '$'.\n";
            }
            else {
                int i = 0;
                while (newPin[i] != '\0') {
                    pins[index][i] = newPin[i];
                    i++;
                }
                pins[index][i] = '\0';

                saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, userCount);
                cout << "PIN changed.\n";
            }
        }
        else if (choice == 6) {
            showChatbot();
        }
        else if (choice == 7) {
            currencyConverter();
        }
        else if (choice == 8) {
            checkLoanEligibility(index, incomes, ages);
        }
        else if (choice == 9) {
            transferMoney(index, accNums, pins, balances, names, cnics, ages, incomes, userCount);

        }
        else if (choice == 10) {
            viewTransactionHistory(accNums[index]);
        }

    } while (choice != 11);
}





//customer login page
void loginCustomer(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int userCount) {
    char acc[20], pin[20];
    cout << "Enter Account Number: ";
    cin >> acc;
    cout << "Enter PIN: ";
    cin >> pin;

    int index = getUserIndexByAcc(acc, accNums, userCount);
    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    int match = 1, i = 0;
    while (pin[i] != '\0' || pins[index][i] != '\0') {
        if (pin[i] != pins[index][i]) {
            match = 0;
            break;
        }
        i++;
    }

    if (match)
        customerMenu(index, names, accNums, pins, cnics, balances, ages, incomes, userCount);
    else
        cout << "Incorrect PIN.\n";
}
//employee login page
bool employeeLogin() {
    char username[30], password[20];

    cout << "Enter employee username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check special character in username
    int hasSpecialInUsername = 0;
    for (int i = 0; username[i] != '\0'; i++) {
        if (username[i] == '@' || username[i] == '#' || username[i] == '$') {
            hasSpecialInUsername = 1;
            break;
        }
    }

    // Check password length and special character
    int passLength = 0, hasSpecialInPassword = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        passLength++;
        if (password[i] == '@' || password[i] == '#' || password[i] == '$') {
            hasSpecialInPassword = 1;
        }
    }

    // Display validation errors
    bool hasError = false;
    if (!hasSpecialInUsername) {
        cout << "Username must contain a special character (@, #, or $).\n";
        hasError = true;
    }
    if (passLength <= 8) {
        cout << "Password length must be greater than 8.\n";
        hasError = true;
    }
    if (!hasSpecialInPassword) {
        cout << "Password must contain at least one special character (@, #, or $).\n";
        hasError = true;
    }
    if (hasError) return false;

    // Match credentials
    const char correctUsername[] = "admin@123";
    const char correctPassword[] = "admin@12345";

    int usernameMatch = 1, passwordMatch = 1;
    int i = 0;
    while (username[i] != '\0' || correctUsername[i] != '\0') {
        if (username[i] != correctUsername[i]) {
            usernameMatch = 0;
            break;
        }
        i++;
    }

    i = 0;
    while (password[i] != '\0' || correctPassword[i] != '\0') {
        if (password[i] != correctPassword[i]) {
            passwordMatch = 0;
            break;
        }
        i++;
    }

    if (usernameMatch && passwordMatch) {
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Invalid employee credentials.\n";
        return false;
    }
}


//create account option 
void createAccount(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int* userCount, int maxUsers) {
    if (*userCount >= maxUsers) {
        cout << "Bank is full.\n";
        return;
    }

    cout << "Enter full name: ";
    cin.ignore();
    cin.getline(names[*userCount], 50);

    cout << "Enter CNIC: ";
    cin >> cnics[*userCount];

    cout << "Enter Age: ";
    cin >> ages[*userCount];

    cout << "Enter Monthly Income: ";
    cin >> incomes[*userCount];

    cout << "Set Account Number: ";
    cin >> accNums[*userCount];

    char newPin[20];
    cout << "Set PIN (min 8 chars + special char): ";
    cin >> newPin;

    if (!isValidPIN(newPin)) {
        cout << "Invalid PIN format.\n";
        return;
    }

    // Copy PIN manually
    int i = 0;
    while (newPin[i] != '\0') {
        pins[*userCount][i] = newPin[i];
        i++;
    }
    pins[*userCount][i] = '\0';

    balances[*userCount] = 0;
    (*userCount)++;

    saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, *userCount);

    cout << "Account created successfully.\n";
}
//this will show all the accounts
void viewAllAccounts(char names[][50], char accNums[][20], int balances[], int userCount) {
    cout << "\nAll Accounts:\n";
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << names[i] << " | " << accNums[i] << " | Rs. " << balances[i] << "\n";
    }
}

//this will search for specific customer
void searchCustomer(char accNums[][20], char names[][50], char cnics[][20],
    int balances[], int ages[], int incomes[], int userCount) {
    char acc[20];
    cout << "Enter account number to search: ";
    cin >> acc;

    int index = getUserIndexByAcc(acc, accNums, userCount);
    if (index == -1)
        cout << "Customer not found.\n";
    else
        viewAccountInfo(index, names, accNums, cnics, ages, incomes, balances);
}
//this will change customer information if you want
void updateInfo(char accNums[][20], char names[][50], char cnics[][20],
    int balances[], int ages[], int incomes[], char pins[][20],
    int userCount) {
    char acc[20];
    cout << "Enter account number to update: ";
    cin >> acc;

    int index = getUserIndexByAcc(acc, accNums, userCount);
    if (index == -1) {
        cout << "Customer not found.\n";
        return;
    }

    cout << "Enter new name: ";
    cin.ignore();
    cin.getline(names[index], 50);

    cout << "Enter new CNIC: ";
    cin >> cnics[index];

    saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, userCount);
    cout << "Info updated.\n";
}
//this will delete the account 
void deleteAccount(char accNums[][20], char names[][50], char cnics[][20], char pins[][20],
    int balances[], int ages[], int incomes[], int* userCount) {
    char acc[20];
    cout << "Enter account number to delete: ";
    cin >> acc;

    int index = getUserIndexByAcc(acc, accNums, *userCount);
    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    for (int i = index; i < (*userCount) - 1; i++) {
        for (int j = 0; j < 50; j++) names[i][j] = names[i + 1][j];
        for (int j = 0; j < 20; j++) {
            accNums[i][j] = accNums[i + 1][j];
            pins[i][j] = pins[i + 1][j];
            cnics[i][j] = cnics[i + 1][j];
        }
        balances[i] = balances[i + 1];
        ages[i] = ages[i + 1];
        incomes[i] = incomes[i + 1];
    }

    (*userCount)--;

    saveCustomers(names, accNums, pins, cnics, balances, ages, incomes, *userCount);
    cout << "Account deleted.\n";
}
//this will show the total balance of bank
void viewTotalBalance(int balances[], int userCount) {
    int total = 0;
    for (int i = 0; i < userCount; i++) {
        total += balances[i];
    }
    cout << "Total Bank Balance: Rs. " << total << "\n";
}
//this will sort the customers in order of alphabatics
void sortByName(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int userCount) {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (names[i][0] > names[j][0]) {
                for (int k = 0; k < 50; k++) {
                    char temp = names[i][k];
                    names[i][k] = names[j][k];
                    names[j][k] = temp;
                }
                for (int k = 0; k < 20; k++) {
                    char temp = accNums[i][k];
                    accNums[i][k] = accNums[j][k];
                    accNums[j][k] = temp;

                    temp = pins[i][k];
                    pins[i][k] = pins[j][k];
                    pins[j][k] = temp;

                    temp = cnics[i][k];
                    cnics[i][k] = cnics[j][k];
                    cnics[j][k] = temp;
                }

                int tempInt = balances[i];
                balances[i] = balances[j];
                balances[j] = tempInt;

                tempInt = ages[i];
                ages[i] = ages[j];
                ages[j] = tempInt;

                tempInt = incomes[i];
                incomes[i] = incomes[j];
                incomes[j] = tempInt;
            }
        }
    }

    viewAllAccounts(names, accNums, balances, userCount);
}
//this will sort on base of bank balance
void sortByBalance(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int userCount) {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (balances[i] > balances[j]) {
                for (int k = 0; k < 50; k++) {
                    char temp = names[i][k];
                    names[i][k] = names[j][k];
                    names[j][k] = temp;
                }
                for (int k = 0; k < 20; k++) {
                    char temp = accNums[i][k];
                    accNums[i][k] = accNums[j][k];
                    accNums[j][k] = temp;

                    temp = pins[i][k];
                    pins[i][k] = pins[j][k];
                    pins[j][k] = temp;

                    temp = cnics[i][k];
                    cnics[i][k] = cnics[j][k];
                    cnics[j][k] = temp;
                }

                int tempInt = balances[i];
                balances[i] = balances[j];
                balances[j] = tempInt;

                tempInt = ages[i];
                ages[i] = ages[j];
                ages[j] = tempInt;

                tempInt = incomes[i];
                incomes[i] = incomes[j];
                incomes[j] = tempInt;
            }
        }
    }

    viewAllAccounts(names, accNums, balances, userCount);
}


//this will show maximum and minimum balance account in bank
void minMaxBalanceHolder(char names[][50], int balances[], int userCount) {
    if (userCount == 0) return;

    int min = 0, max = 0;
    for (int i = 1; i < userCount; i++) {
        if (balances[i] < balances[min]) min = i;
        if (balances[i] > balances[max]) max = i;
    }

    cout << "Lowest Balance: " << names[min] << " | Rs. " << balances[min] << "\n";
    cout << "Highest Balance: " << names[max] << " | Rs. " << balances[max] << "\n";
}
//this is emplyee menue page
void employeeMenu(char names[][50], char accNums[][20], char pins[][20], char cnics[][20],
    int balances[], int ages[], int incomes[], int* userCount, int maxUsers) {
    int ch;
    do {
        cout << "\n--- Employee Panel ---\n";
        cout << "1. Create Account\n2. View All Accounts\n3. Search Customer\n4. Update Info\n";
        cout << "5. Delete Account\n6. View Total Balance\n7. Sort by Name\n8. Sort by Balance\n";
        cout << "9. Min/Max Balance\n10. Logout\nEnter choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            createAccount(names, accNums, pins, cnics, balances, ages, incomes, userCount, maxUsers);
            break;
        case 2:
            viewAllAccounts(names, accNums, balances, *userCount);
            break;
        case 3:
            searchCustomer(accNums, names, cnics, balances, ages, incomes, *userCount);
            break;
        case 4:
            updateInfo(accNums, names, cnics, balances, ages, incomes, pins, *userCount);
            break;
        case 5:
            deleteAccount(accNums, names, cnics, pins, balances, ages, incomes, userCount);
            break;
        case 6:
            viewTotalBalance(balances, *userCount);
            break;
        case 7:
            sortByName(names, accNums, pins, cnics, balances, ages, incomes, *userCount);
            break;
        case 8:
            sortByBalance(names, accNums, pins, cnics, balances, ages, incomes, *userCount);
            break;
        case 9:
            minMaxBalanceHolder(names, balances, *userCount);
            break;
        case 10:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (ch != 10);
}
void credentials() {
    cout << "Employee :" << endl;
    cout << "Username:" << " admin@123" << " Password:" << " admin@12345" << endl;
    cout << endl;
    cout << "Customer 1:" << endl;
    cout << "Name:" << " Baber Ali " << "Account number:" << " 1000" << " Pin:" << " baberali@" << endl;
    cout << endl;
    cout << "Customer 2:" << endl;
    cout << "Name:" << " Darya Khan " << "Account number:" << " 1002" << " Pin:" << " daryakhan@" << endl;

}
//this is function for the structure of bank
void drawBankFront() {
    cout << "\n";
    cout << "     ============================================================================\n";
    cout << "     ||                               Z A Q   B A N K                          ||\n";
    cout << "     ============================================================================\n";
    cout << "     ||    [=========]     [=========]     [=========]     [=========]         ||\n";
    cout << "     ||    |         |     |         |     |         |     |         |         ||\n";
    cout << "     ||    |   ATM   |     | Window  |     |  Office |     |   Door  |         ||\n";
    cout << "     ||    |_________|     |_________|     |_________|     |_________|         ||\n";
    cout << "     ||                                                                        ||\n";
    cout << "     ||=========================|   WELCOME TO ZAQ BANK   |==================||\n";
    cout << "     ||                                                                        ||\n";
    cout << "     ||                            Serving with Trust Since 2025               ||\n";
    cout << "     ||========================================================================||\n";
    cout << "     ||                                                                        ||\n";
    cout << "     ============================================================================\n";
    cout << "\n";
}


//main function

int main() {
    const int MAX_USERS = 100;
    char names[MAX_USERS][50];
    char accNums[MAX_USERS][20];
    char pins[MAX_USERS][20];
    char cnics[MAX_USERS][20];
    int balances[MAX_USERS];
    int ages[MAX_USERS];
    int incomes[MAX_USERS];
    int userCount = 0;

    loadCustomers(names, accNums, pins, cnics, balances, ages, incomes, &userCount);
    drawBankFront();
    int choice;
    do {


        cout << "======= WELCOME ========" << endl;
        cout << "1. Login as Customer\n2. Login as Employee\n3. Credentials to login\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loginCustomer(names, accNums, pins, cnics, balances, ages, incomes, userCount);
            break;

        case 2:
            if (employeeLogin()) {
                employeeMenu(names, accNums, pins, cnics, balances, ages, incomes, &userCount, MAX_USERS);
            }
            break;
        case 3:
            credentials();
                break;
        case 4:
            cout << "Exiting Program.\n";
            break;

        default:
            cout << "Invalid option.\n";
        }

    } while (choice != 4);

    return 0;
}
