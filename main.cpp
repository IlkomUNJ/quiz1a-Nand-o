#include <iostream>
#include <vector>
#include <string>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"
#include "bank.h"

enum PrimaryPrompt
{
    LOGIN,
    REGISTER,
    EXIT,
    ADMIN_LOGIN
};
enum RegisterPrompt
{
    CREATE_BUYER,
    CREATE_SELLER,
    BACK
};
enum AdminPrompt
{
    ACCOUNT_MANAGEMENT,
    SYSTEM_REPORT,
    BACK_TO_MAIN
};
enum ManagementPrompt
{
    CREATE_NEW_ACCOUNT,
    SEARCH_ACCOUNT,
    REMOVE_ACCOUNT,
    VIEW_ACCOUNT,
    BACK_TO_ADMIN_MENU
};

enum ViewAccountPrompt
{
    VIEW_ALL_BUYER,
    VIEW_ALL_SELLER,
    VIEW_DETAILS_BUYER,
    VIEW_DETAILS_SELLER,
    BACK_TO_MANAGEMENT_MENU
};

using namespace std;

// Header for function

bool checkAdmin(string &username, string &password, const string &ADMIN_USERNAME, const string &ADMIN_PASSWORD, bool &isAdminLogin);
void accountManagementMenu();
void createNewAccount();
void searchById(vector<Buyer> &buyers, vector<seller> &sellers, int id, bool searchSeller = false);
void removeById(vector<Buyer> &buyers, vector<seller> &sellers, int id);
void viewAccount();
void systemReport();

// Deklarasi Awal
vector<BankCustomer> bankCustomers;
Bank bankUtama("Mandiri");
vector<Buyer> buyers;
vector<seller> sellers;

int main()
{
    // Default Buyer & Seller
    BankCustomer customer1(1, "Alice", 1000.0);
    BankCustomer customer2(2, "Bob", 2000.0);
    BankCustomer customer3(3, "Charlie", 3000.0);
    Buyer Asep(1, "Asep", "", "", "", &customer1);
    Buyer Budi(2, "Budi", "", "", "", &customer2);
    Buyer Caca(3, "Caca", "", "", "", &customer3);
    seller seller1(Asep, 1, "Store A", "Address A", "Phone A", "Email A");
    seller seller2(Asep, 2, "Store B", "Address B", "Phone B", "Email B");
    seller seller3(Asep, 3, "Store C", "Address C", "Phone C", "Email C");
    bankCustomers.push_back(customer1);
    bankCustomers.push_back(customer2);
    bankCustomers.push_back(customer3);
    buyers.push_back(Asep);
    buyers.push_back(Budi);
    buyers.push_back(Caca);
    sellers.push_back(seller1);
    sellers.push_back(seller2);
    sellers.push_back(seller3);

    // create a loop prompt
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;
    bool isAdminLogin = false;

    while (prompt != EXIT)
    {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt)
        {
        case LOGIN:
            cout << "Login selected." << endl;
            /* if Login is selected, based on authority then provide options:
            assume user is logged in as Buyer for now
            1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
            Will display Buyer, Seller and Banking Account details
            2. Upgrade Account to Seller
            Will prompt user to enter Seller details and create a Seller account linked to Buyer account
            Will reject if a user dont have a banking account linked
            3. Create Banking Account (if not already linked), will be replaced with banking functions
            Must provides: initial deposit amount, Address, Phone number, Email
            Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
            4. Browse Store Functionality
            Will display all stores initially
            Need to select a store to browse each store inventory
            Will display all items in the store inventory
            After selecting an item, will display item details and option to add to cart
            After adding to cart, will notify user item is added to cart
            5. Order Functionality
            Will display all items in cart
            Will provide option to remove item from cart
            Will provide option to checkout
            After checkout invoide will be generated (will go to payment functionality)
            6. Payment Functionality
            Will display all listed invoices
            Pick an invoice to pay
            Will display invoice details and total amount
            Will provide option to pay invoice
            Payment is done through confirmation dialogue
            In confirmation dialogue, will display account balance as precursor
            User will need to manually enter invoice id to pay
            After paying balance will be redacted from buyer and added to the responding seller account
            After payment, order status will be changed to paid
            7. Logout (return to main menu)
            Display confirmation dialogue
            If confirmed, return to main menu
            If not, return to Buyer menu
            8. Delete Account (remove both Buyer and Seller account and relevant banking account)
            Display confirmation dialogue
            If confirmed, delete account and return to main menu
            If not, return to Buyer menu

            assume user is logged in as Seller for now
            9. Check Inventory
            10. Add Item to Inventory
            11. Remove Item from Inventory
            12. View Orders (will display all orders placed to this seller
            Only orders with paid status will be listed
            Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
            extra functions
            9. Exit to main Menu
            10. Exit Program
            **/
            break;
        case REGISTER:
            regPrompt = CREATE_BUYER; // reset regPrompt to CREATE_BUYER when entering register menu
            while (regPrompt != BACK)
            {
                cout << "Register selected. " << endl;
                cout << "Select an option: " << endl;
                cout << "1. Create Buyer Account" << endl;
                cout << "2. Create Seller Account" << endl;
                cout << "3. Back" << endl;
                cout << "Enter your choice: ";
                int regChoice;
                cin >> regChoice;
                regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                switch (regPrompt)
                {
                case CREATE_BUYER:
                    cout << "Create Buyer Account selected." << endl;
                    break;
                case CREATE_SELLER:
                    cout << "Create Seller Account selected." << endl;
                    break;
                case BACK:
                    cout << "Back selected." << endl;
                    break;
                default:
                    cout << "Invalid option." << endl;
                    break;
                }
            }
            /* if register is selected then went throuhh registration process:
            1. Create a new Buyer Account
            Must provides: Name, Home Address, Phone number, Email
            2. Option to create a Seller Account (will be linked to Buyer account)
            Must Provides 1: Home Address, Phone number, Email
            Must provides 2: Store Name, Store Address, Store Phone number, Store Email
            Must provides 3: initial deposit amount
            After finished immediately logged in as Buyer/Seller
            */
            break;
        case EXIT:
            cout << "Exiting." << endl;
            break;
        case ADMIN_LOGIN:
            /* Prompt for username & password then check the entries with our hard coded features */
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (checkAdmin(username, password, ADMIN_USERNAME, ADMIN_PASSWORD, isAdminLogin))
            {
                AdminPrompt adminChoice = ACCOUNT_MANAGEMENT;
                while (adminChoice != BACK_TO_MAIN)
                {
                    cout << "\n===== ADMIN MENU =====" << endl;
                    cout << "1. Account Management" << endl;
                    cout << "2. System Report" << endl;
                    cout << "3. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    int choice;
                    cin >> choice;
                    adminChoice = static_cast<AdminPrompt>(choice - 1);

                    switch (adminChoice)
                    {
                    case ACCOUNT_MANAGEMENT:
                        cout << "Account Management selected." << endl;
                        accountManagementMenu();
                        break;

                    case SYSTEM_REPORT:
                        cout << "System Report selected." << endl;
                        systemReport();
                        break;

                    case BACK_TO_MAIN:
                        cout << "Back to Main Menu" << endl;
                        break;

                    default:
                        cout << "Invalid option." << endl;
                        break;
                    }
                }
            }
            /** After login create a sub prompt that provides the following features
            1. Account Management
                - View All Buyers, Sellers
                - View All details of Buyers, Sellers
                - Seek certain buyer of seller based on Name / account Id / address / phone number
                - Create new buyer/seller/Bank account
                - Remove buyer/seller based on ID (all related info will be deleted)
            2. System Report
                - Total number of Buyers, Sellers
                - Total number of Banking Accounts
            */
            break;
        default:
            cout << "Invalid option." << endl;
            break;
        }
        cout << endl;
    }

    // BankCustomer customer1(1, "Alice", 1000.0);
    // Buyer buyer1(1, customer1.getName(), customer1);
    return 1;
}

// Library Function

bool checkAdmin(string &username, string &password, const string &ADMIN_USERNAME, const string &ADMIN_PASSWORD, bool &isAdminLogin)
{
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        isAdminLogin = true;
        return true;
    }
    else
    {
        isAdminLogin = false;
        cout << "Invalid username or password. Please try again." << endl;
        return false;
    }
}

void createNewAccount()
{
    cout << "\n===== CREATE ACCOUNT =====" << endl;
    string name, address, phone, email;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your home address: ";
    getline(cin, address);

    cout << "Enter your phone number: ";
    getline(cin, phone);

    cout << "Enter your email: ";
    getline(cin, email);

    double initialDeposit;
    cout << "Enter initial deposit amount: $";
    cin >> initialDeposit;

    int newId = bankCustomers.size() + 1;
    BankCustomer newBankCustomer(newId, name, initialDeposit);
    bankCustomers.push_back(newBankCustomer);

    Buyer newBuyer(newId, name, address, phone, email, &bankCustomers.back());
    buyers.push_back(newBuyer);

    cout << "Registration successful!" << endl;
    cout << "Bank account created with balance: $" << initialDeposit << endl;

    char createSeller;
    cout << "Do you want to create a seller account? (y/n): ";
    cin >> createSeller;

    if (createSeller == 'y' || createSeller == 'Y')
    {
        cout << "Enter store name: ";
        cin.ignore();
        string storeName;
        getline(cin, storeName);

        cout << "Enter store address: ";
        string storeAddress;
        getline(cin, storeAddress);

        cout << "Enter store phone: ";
        string storePhone;
        getline(cin, storePhone);

        cout << "Enter store email: ";
        string storeEmail;
        getline(cin, storeEmail);

        // Create seller account
        seller newSeller(newBuyer, newId, storeName, storeAddress, storePhone, storeEmail);
        sellers.push_back(newSeller);

        cout << "Seller account created successfully!" << endl;
    }
}

void searchById(vector<Buyer> &buyers, vector<seller> &sellers, int id, bool searchSeller)
{
    bool found = false;

    if (searchSeller)
    {
        for (size_t i = 0; i < sellers.size(); i++)
        {
            if (sellers[i].getId() == id)
            {
                cout << "Seller ID: " << sellers[i].getId() << endl;
                cout << "Name: " << sellers[i].getName() << endl;
                cout << "Address: " << sellers[i].getAddress() << endl;
                cout << "Phone: " << sellers[i].getPhone() << endl;
                cout << "Email: " << sellers[i].getEmail() << endl;
                cout << "Store Name: " << sellers[i].getStoreName() << endl;
                cout << "Store Address: " << sellers[i].getStoreAddress() << endl;
                cout << "Store Phone: " << sellers[i].getStorePhone() << endl;
                cout << "Store Email: " << sellers[i].getStoreEmail() << endl;
                found = true;
                break;
            }
        }
    }

    for (size_t i = 0; i < buyers.size(); i++)
    {
        if (buyers[i].getId() == id)
        {
            cout << "Buyer ID: " << buyers[i].getId() << endl;
            cout << "Name: " << buyers[i].getName() << endl;
            cout << "Address: " << buyers[i].getAddress() << endl;
            cout << "Phone: " << buyers[i].getPhone() << endl;
            cout << "Email: " << buyers[i].getEmail() << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "No account found with ID: " << id << endl;
    }
}

// Ganti fungsi removeById Anda dengan yang ini
void removeById(vector<Buyer> &buyers, vector<seller> &sellers, vector<BankCustomer> &bankCustomers, int id)
{
    bool found = false;

    // 1. Hapus dari vector 'sellers' terlebih dahulu
    for (auto it = sellers.begin(); it != sellers.end(); ) {
        if (it->getId() == id) {
            it = sellers.erase(it); // erase() mengembalikan iterator ke elemen berikutnya
            found = true;
        } else {
            ++it; // Hanya increment jika tidak ada elemen yang dihapus
        }
    }

    // 2. Hapus dari vector 'buyers'
    for (auto it = buyers.begin(); it != buyers.end(); ) {
        if (it->getId() == id) {
            it = buyers.erase(it);
            found = true;
        } else {
            ++it;
        }
    }

    // 3. Hapus dari vector 'bankCustomers'
    for (auto it = bankCustomers.begin(); it != bankCustomers.end(); ) {
        if (it->getId() == id) {
            it = bankCustomers.erase(it);
            found = true;
        } else {
            ++it;
        }
    }

    if (found) {
        cout << "Account with ID " << id << " has been removed successfully." << endl;
    } else {
        cout << "Account with ID " << id << " not found." << endl;
    }
}

void viewAccount()
{
    ViewAccountPrompt viewChoice = VIEW_ALL_BUYER;
    while (viewChoice != BACK_TO_MANAGEMENT_MENU)
    {
        cout << "\n===== VIEW ACCOUNT =====" << endl;
        cout << "1. View All Buyers" << endl;
        cout << "2. View All Sellers" << endl;
        cout << "3. View Details of Buyer" << endl;
        cout << "4. View Details of Seller" << endl;
        cout << "5. Back to Management Menu" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        viewChoice = static_cast<ViewAccountPrompt>(choice - 1);

        switch (viewChoice)
        {
        case VIEW_ALL_BUYER:
            cout << "\nView All Buyers selected." << endl;
            for (size_t i = 0; i < buyers.size(); i++)
            {
                cout << "Buyer ID: " << buyers[i].getId() << endl;
                cout << "Name: " << buyers[i].getName() << endl;
                cout << endl;
            }
            break;

        case VIEW_ALL_SELLER:
            cout << "\nView All Sellers selected." << endl;
            for (size_t i = 0; i < sellers.size(); i++)
            {
                cout << "Seller ID: " << sellers[i].getId() << endl;
                cout << "storeName: " << sellers[i].getStoreName() << endl;
                cout << endl;
            }
            break;

        case VIEW_DETAILS_BUYER:
            cout << "\nView Details of Buyer selected." << endl;
            for (size_t i = 0; i < buyers.size(); i++)
            {
                cout << "Buyer ID: " << buyers[i].getId() << endl;
                cout << "Name: " << buyers[i].getName() << endl;
                cout << "Address: " << buyers[i].getAddress() << endl;
                cout << "Phone: " << buyers[i].getPhone() << endl;
                cout << "Email: " << buyers[i].getEmail() << endl;
                cout << "Account Type: Buyer" << endl;
                cout << endl;
            }
            break;

        case VIEW_DETAILS_SELLER:
            cout << "\nView Details of Seller selected." << endl;
            for (size_t i = 0; i < sellers.size(); i++)
            {
                cout << "Seller ID: " << sellers[i].getId() << endl;
                cout << "storeName: " << sellers[i].getStoreName() << endl;
                cout << "storeAddress: " << sellers[i].getStoreAddress() << endl;
                cout << "storePhone: " << sellers[i].getStorePhone() << endl;
                cout << "storeEmail: " << sellers[i].getStoreEmail() << endl;
                cout << endl;
            }
            break;

        case BACK_TO_MANAGEMENT_MENU:
            cout << "Back to Management Menu" << endl;
        }
    }
}

void accountManagementMenu()
{
    ManagementPrompt managementChoice = CREATE_NEW_ACCOUNT;
    while (managementChoice != BACK_TO_ADMIN_MENU)
    {
        cout << "\n===== ACCOUNT MANAGEMENT =====" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Search Account" << endl;
        cout << "3. Remove Account" << endl;
        cout << "4. View Account" << endl;
        cout << "5. Back to Admin Menu" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        managementChoice = static_cast<ManagementPrompt>(choice - 1);

        switch (managementChoice)
        {
        case CREATE_NEW_ACCOUNT:
            cout << "Create New Account selected." << endl;
            createNewAccount();
            break;

        case SEARCH_ACCOUNT:
            cout << "Search Account selected." << endl;
            int searchId;
            cout << "Enter account ID to search: ";
            cin >> searchId;

            cout << "Do you search seller account? (y/n): ";
            char isSeller;
            cin >> isSeller;

            cout << "Search Result: ";
            if (isSeller == 'y' || isSeller == 'Y')
            {
                searchById(buyers, sellers, searchId, true);
            }

            searchById(buyers, sellers, searchId, false);
            break;

        case REMOVE_ACCOUNT:
            cout << "Remove Account selected." << endl;
            int removeId;
            cout << "Enter account ID to remove: ";
            cin >> removeId;
            removeById(buyers, sellers, bankCustomers, removeId);
            break;

        case VIEW_ACCOUNT:
            cout << "View All selected." << endl;
            viewAccount();
            break;

        case BACK_TO_ADMIN_MENU:
            cout << "Back to Admin Menu" << endl;
            break;

        default:
            cout << "Invalid option." << endl;
            break;
        }
    }
}

void systemReport() {
    cout << "\n===== SYSTEM REPORT =====" << endl;
    cout << "Total number of Buyers: " << buyers.size() << endl;
    cout << "Total number of Sellers: " << sellers.size() << endl;
    cout << "Total number of Banking Accounts: " << bankCustomers.size() << endl;
    cout << endl;
};
