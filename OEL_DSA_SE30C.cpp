#include <iostream> // For input/output
#include <string>   // For strings
#include <fstream>  // For file operations
#include <ctime>    // For getting date/time
#include <limits>   // For numeric limits
using namespace std;

// Define the structure for a Book
struct Book {
    string title;    // Book title
    string author;   // Book author
    string isbn;     // Book ISBN code
    bool available;  // Is the book available to borrow?
};

// Define the structure for a User
struct User {
    int id;         // Unique user ID
    string name;    // User's name
    string phone;   // User's phone number
};

// Define the structure for a Transaction
struct Transaction {
    int userId;         // ID of the user performing the transaction
    string isbn;        // ISBN of the book
    string action;      // Borrowed or Returned
    string date;        // Date of the transaction
    string userName;    // Name of the user
    string userPhone;   // Phone number of the user
};

// Arrays to store books, users, and transactions
Book books[200];
User users[200];
Transaction transactions[400];

// Counters to track number of books, users, and transactions
int bookCount = 0;
int userCount = 0;
int transCount = 0;

// Function to get the current date in YYYY-MM-DD format
string getDate() {
    time_t now = time(0);           // Get current time
    tm* t = localtime(&now);        // Convert to local time structure
    return to_string(1900 + t->tm_year) + "-" + // Year
           to_string(1 + t->tm_mon) + "-" +    // Month (0-based, so +1)
           to_string(t->tm_mday);             // Day
}

// Function to find a book by its ISBN
int findBook(string isbn) {
    for (int i = 0; i < bookCount; i++) // Loop through all books
        if (books[i].isbn == isbn)      // If ISBN matches
            return i;                   // Return index
    return -1;                          // If not found, return -1
}

// Function to find a user by their ID
int findUser(int id) {
    for (int i = 0; i < userCount; i++) // Loop through all users
        if (users[i].id == id)          // If ID matches
            return i;                   // Return index
    return -1;                          // If not found
}

// Function to add a new book manually
void addBook() {
    cin.ignore();                        // Clear input buffer
    cout << "Enter title: ";
    getline(cin, books[bookCount].title); // Read book title
    cout << "Enter author: ";
    getline(cin, books[bookCount].author); // Read book author
    cout << "Enter ISBN: ";
    getline(cin, books[bookCount].isbn);   // Read ISBN
    books[bookCount].available = true;     // Mark book as available
    bookCount++;                           // Increment book count
    cout << "Book added." << endl;         // Confirm addition
}

// Function to add a new user manually
void addUser() {
    cout << "Enter user ID: ";
    cin >> users[userCount].id;           // Read user ID
    cin.ignore();                          // Clear input buffer
    cout << "Enter name: ";
    getline(cin, users[userCount].name);  // Read user name
    cout << "Enter phone: ";
    getline(cin, users[userCount].phone); // Read phone number
    userCount++;                           // Increment user count
    cout << "User added." << endl;         // Confirm addition
}

// Function to borrow a book
void borrowBook() {
    int uid;                               // Store user ID
    string isbn;                            // Store ISBN
    cout << "Enter user ID: ";
    cin >> uid;                             // Read user ID
    cout << "Enter book ISBN: ";
    cin >> isbn;                            // Read ISBN

    int u = findUser(uid);                  // Find user index
    int b = findBook(isbn);                 // Find book index

    if (u == -1) { cout << "User not found." << endl; return; } // User validation
    if (b == -1) { cout << "Book not found." << endl; return; } // Book validation
    if (!books[b].available) { cout << "Book already borrowed." << endl; return; } // Already borrowed

    books[b].available = false;             // Mark book as borrowed
    transactions[transCount].userId = uid;  // Record user ID
    transactions[transCount].isbn = isbn;   // Record book ISBN
    transactions[transCount].action = "Borrowed"; // Record action
    transactions[transCount].date = getDate();    // Record current date
    transactions[transCount].userName = users[u].name; // Store user name
    transactions[transCount].userPhone = users[u].phone; // Store user phone
    transCount++;                           // Increment transaction count

    cout << "Book borrowed." << endl;       // Confirm borrowing
}

// Function to return a book
void returnBook() {
    int uid;                               // Store user ID
    string isbn;                            // Store ISBN
    cout << "Enter user ID: ";
    cin >> uid;                             // Read user ID
    cout << "Enter book ISBN: ";
    cin >> isbn;                            // Read ISBN

    int b = findBook(isbn);                 // Find book
    if (b == -1) { cout << "Book not found." << endl; return; } // Validation
    if (books[b].available) { cout << "This book was never borrowed." << endl; return; } // Cannot return available book

    int u = findUser(uid);                  // Find user
    if (u == -1) { cout << "User not found." << endl; return; } // Validation

    books[b].available = true;              // Mark book as available
    transactions[transCount].userId = uid;  // Record transaction
    transactions[transCount].isbn = isbn;
    transactions[transCount].action = "Returned";
    transactions[transCount].date = getDate();
    transactions[transCount].userName = users[u].name;
    transactions[transCount].userPhone = users[u].phone;
    transCount++;                           // Increment transaction count

    cout << "Book returned." << endl;       // Confirm return
}

// Display all books
void showBooks() {
    cout << endl << "TITLE                AUTHOR               ISBN        STATUS" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < bookCount; i++) {                  // Loop through all books
        int tspace = (books[i].title.length() < 20 ? 20 - books[i].title.length() : 1); // Padding for title
        int aspace = (books[i].author.length() < 20 ? 20 - books[i].author.length() : 1); // Padding for author
        cout << books[i].title << string(tspace, ' ')      // Print title
             << books[i].author << string(aspace, ' ')    // Print author
             << books[i].isbn << "   "                    // Print ISBN
             << (books[i].available ? "Available" : "Borrowed") << endl; // Print status
    }
}

// Display all users
void showUsers() {
    cout << endl << "ID    NAME                PHONE" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < userCount; i++) {                // Loop through all users
        int nspace = (users[i].name.length() < 20 ? 20 - users[i].name.length() : 1); // Padding for name
        cout << users[i].id << "    "                    // Print user ID
             << users[i].name << string(nspace, ' ')    // Print name
             << users[i].phone << endl;                 // Print phone
    }
}

// Display all transactions
void showTransactions() {
    cout << endl << "DATE        USER     NAME                PHONE       ISBN      ACTION" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    for (int i = 0; i < transCount; i++) {             // Loop through all transactions
        int nspace = (transactions[i].userName.length() < 20 ? 20 - transactions[i].userName.length() : 1); // Padding
        cout << transactions[i].date << "   "           // Print date
             << transactions[i].userId << "     "      // Print user ID
             << transactions[i].userName << string(nspace, ' ') // Print user name
             << transactions[i].userPhone << "   "     // Print phone
             << transactions[i].isbn << "   "          // Print ISBN
             << transactions[i].action << endl;       // Print action
    }
}

// Import books from file
void importBooks() {
    string file;
    cout << "Enter books file name: ";
    cin >> file;
    ifstream fin(file);                                // Open file
    if (!fin) { cout << "File not found." << endl; return; } // Check file

    string title, author, isbn;                        // Temp vars
    while (getline(fin, title, ',') && getline(fin, author, ',') && getline(fin, isbn)) {
        books[bookCount].title = title;               // Assign title
        books[bookCount].author = author;             // Assign author
        books[bookCount].isbn = isbn;                 // Assign ISBN
        books[bookCount].available = true;            // New book available
        bookCount++;                                  // Increment count
    }
    fin.close();                                      // Close file
    cout << "Books imported." << endl;                // Confirm
}

// Import users from file
void importUsers() {
    string file;
    cout << "Enter users file name: ";
    cin >> file;
    ifstream fin(file);
    if (!fin) { cout << "File not found." << endl; return; }

    string id, name, phone;
    while (getline(fin, id, ',') && getline(fin, name, ',') && getline(fin, phone)) {
        users[userCount].id = stoi(id);               // Convert and assign ID
        users[userCount].name = name;                 // Assign name
        users[userCount].phone = phone;               // Assign phone
        userCount++;                                  // Increment count
    }
    fin.close();
    cout << "Users imported." << endl;
}

// Import transactions from file
void importTransactions() {
    string file;
    cout << "Enter transactions file: ";
    cin >> file;
    ifstream fin(file);
    if (!fin) { cout << "File not found." << endl; return; }

    string id, isbn, action, date, name, phone;
    while (getline(fin, id, ',') && getline(fin, isbn, ',') && getline(fin, action, ',') &&
           getline(fin, date, ',') && getline(fin, name, ',') && getline(fin, phone)) {
        transactions[transCount].userId = stoi(id);   // Assign ID
        transactions[transCount].isbn = isbn;        // Assign ISBN
        transactions[transCount].action = action;    // Assign action
        transactions[transCount].date = date;        // Assign date
        transactions[transCount].userName = name;    // Assign name
        transactions[transCount].userPhone = phone;  // Assign phone

        int b = findBook(isbn);                       // Find book
        if (b != -1) {                                // If book exists
            if (action == "Borrowed") books[b].available = false;
            else if (action == "Returned") books[b].available = true;
        }
        transCount++;                                 // Increment transaction count
    }
    fin.close();
    cout << "Transactions imported." << endl;
}

// Search books
void searchBooks() {
    int choice;
    cout << "Search book by: 1. Title 2. Author 3. ISBN" << endl;
    cout << "Choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    string key;
    cout << "Enter search keyword: ";
    getline(cin, key);
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if ((choice == 1 && books[i].title.find(key) != string::npos) ||
            (choice == 2 && books[i].author.find(key) != string::npos) ||
            (choice == 3 && books[i].isbn.find(key) != string::npos)) {
            cout << books[i].title << " | " << books[i].author
                 << " | " << books[i].isbn
                 << " | " << (books[i].available ? "Available" : "Borrowed") << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching book found." << endl;
}

// Search users
void searchUsers() {
    int choice;
    cout << "Search user by: 1. ID 2. Name" << endl;
    cout << "Choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    bool found = false;
    if (choice == 1) {
        int uid;
        cout << "Enter user ID: ";
        cin >> uid;
        int u = findUser(uid);
        if (u != -1) {
            cout << users[u].id << " | " << users[u].name << " | " << users[u].phone << endl;
            found = true;
        }
    } else if (choice == 2) {
        string key;
        cout << "Enter name keyword: ";
        getline(cin, key);
        for (int i = 0; i < userCount; i++) {
            if (users[i].name.find(key) != string::npos) {
                cout << users[i].id << " | " << users[i].name << " | " << users[i].phone << endl;
                found = true;
            }
        }
    }
    if (!found) cout << "No matching user found." << endl;
}

// Sort books
void sortBooks() {
    int choice;
    cout << "Sort books by: 1. Title 2. Author" << endl;
    cout << "Choice: ";
    cin >> choice;
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = i + 1; j < bookCount; j++) {
            if ((choice == 1 && books[i].title > books[j].title) ||
                (choice == 2 && books[i].author > books[j].author)) {
                swap(books[i], books[j]); // Swap books
            }
        }
    }
    cout << "Books sorted." << endl;
}

// Main program
int main() {
    int ch;
    while (true) {
        cout << endl << "==== LIBRARY SYSTEM ====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Add User" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Show Books" << endl;
        cout << "6. Show Users" << endl;
        cout << "7. Show Transactions" << endl;
        cout << "8. Import Books" << endl;
        cout << "9. Import Users" << endl;
        cout << "10. Import Transactions" << endl;
        cout << "11. Search Books" << endl;
        cout << "12. Search Users" << endl;
        cout << "13. Sort Books" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) addBook();
        else if (ch == 2) addUser();
        else if (ch == 3) borrowBook();
        else if (ch == 4) returnBook();
        else if (ch == 5) showBooks();
        else if (ch == 6) showUsers();
        else if (ch == 7) showTransactions();
        else if (ch == 8) importBooks();
        else if (ch == 9) importUsers();
        else if (ch == 10) importTransactions();
        else if (ch == 11) searchBooks();
        else if (ch == 12) searchUsers();
        else if (ch == 13) sortBooks();
        else if (ch == 0) break;
        else cout << "Invalid choice." << endl;
    }
    return 0; // Exit program
}
