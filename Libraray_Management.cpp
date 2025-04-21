#include <iostream>
#include <fstream>
using namespace std;

class Library {
    string bookID, title, author, quantity;
    string sID, sTitle;
    fstream file;

public:
    void addBook();
    void displayBooks();
    void searchBook();
    void updateBook();
    void deleteBook();
    void issueBook();
    void returnBook();
} obj;

int main() {
    char choice;

   
        cout << "\n===== Library Management System =====";
        cout << "\n1 - Add Book";
        cout << "\n2 - Display All Books";
        cout << "\n3 - Search Book by ID";
        cout << "\n4 - Update Book";
        cout << "\n5 - Delete Book";
        cout << "\n6 - Issue Book";
        cout << "\n7 - Return Book";
        cout << "\n8 - Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1': obj.addBook(); break;
            case '2': obj.displayBooks(); break;
            case '3': obj.searchBook(); break;
            case '4': obj.updateBook(); break;
            case '5': obj.deleteBook(); break;
            case '6': obj.issueBook(); break;
            case '7': obj.returnBook(); break;
            case '8': cout << "Exiting..."; break;
            default: cout << "Invalid choice!\n"; break;
        }
}

// 1. Add Book
void Library::addBook() {
    cout << "\nEnter Book ID: ";
    getline(cin, bookID);
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Quantity: ";
    getline(cin, quantity);

    file.open("LibraryData.txt", ios::out | ios::app);
    file << bookID << " | " << title << " | " << author << " | " << quantity << "\n";
    file.close();

    cout << "\nBook added successfully!";
}

// 2. Display All Books
void Library::displayBooks() {
    file.open("LibraryData.txt", ios::in);
    cout << "\n--- Book List ---\n";
    cout << "ID\tTitle\tAuthor\tQuantity\n";

    while (getline(file, bookID, '|')) {
        getline(file, title, '|');
        getline(file, author, '|');
        getline(file, quantity);
        cout << bookID << "\t" << title << "\t" << author << "\t" << quantity << "\n";
    }

    file.close();
}

// 3. Search Book
void Library::searchBook() {
    bool found = false;
    cout << "\nEnter Book ID to Search: ";
    getline(cin, sID);

    file.open("LibraryData.txt", ios::in);
    while (getline(file, bookID, '|')) {
        getline(file, title, '|');
        getline(file, author, '|');
        getline(file, quantity);
        if (bookID == sID) {
            cout << "\nBook Found:\n";
            cout << "ID: " << bookID << "\nTitle: " << title << "\nAuthor: " << author << "\nQuantity: " << quantity;
            found = true;
            break;
        }
    }

    if (!found) cout << "\nBook Not Found!";
    file.close();
}

// 4. Update Book
void Library::updateBook() {
    bool found = false;
    cout << "\nEnter Book ID to Update: ";
    getline(cin, sID);

    file.open("LibraryData.txt", ios::in);
    ofstream temp("Temp.txt");

    while (getline(file, bookID, '|')) {
        getline(file, title, '|');
        getline(file, author, '|');
        getline(file, quantity);

        if (bookID == sID) {
            cout << "\nEnter New Title: ";
            getline(cin, title);
            cout << "Enter New Author: ";
            getline(cin, author);
            cout << "Enter New Quantity: ";
            getline(cin, quantity);
            found = true;
        }

        temp << bookID << " | " << title << " | " << author << " | " << quantity << "\n";
    }

    file.close();
    temp.close();
    remove("LibraryData.txt");
    rename("Temp.txt", "LibraryData.txt");

    if (found)
        cout << "\nBook Updated Successfully!";
    else
        cout << "\nBook Not Found!";
}

// 5. Delete Book
void Library::deleteBook() {
    bool found = false;
    cout << "\nEnter Book ID to Delete: ";
    getline(cin, sID);

    file.open("LibraryData.txt", ios::in);
    ofstream temp("Temp.txt");

    while (getline(file, bookID, '|')) {
        getline(file, title, '|');
        getline(file, author, '|');
        getline(file, quantity);

        if (bookID != sID)
            temp << bookID << " | " << title << " | " << author << " | " << quantity << "\n";
        else
            found = true;
    }

    file.close();
    temp.close();
    remove("LibraryData.txt");
    rename("Temp.txt", "LibraryData.txt");

    if (found)
        cout << "\nBook Deleted Successfully!";
    else
        cout << "\nBook Not Found!";
}

// 6. Issue Book
void Library::issueBook() {
    string user;
    cout << "\nEnter Book ID to Issue: ";
    getline(cin, sID);
    cout << "Enter Your Name: ";
    getline(cin, user);

    bool found = false;
    file.open("LibraryData.txt", ios::in);
    ofstream temp("Temp.txt");
    string qty;

    while (getline(file, bookID, '|')) {
        getline(file, title, '|');
        getline(file, author, '|');
        getline(file, quantity);

        if (bookID == sID) {
            int q = stoi(quantity);
            if (q > 0) {
                q--;
                quantity = to_string(q);
                ofstream issue("IssuedBooks.txt", ios::app);
                issue << bookID << " | " << user << "\n";
                issue.close();
                cout << "\nBook Issued to " << user;
            } else {
                cout << "\nBook Not Available!";
            }
            found = true;
        }

        temp << bookID << " | " << title << " | " << author << " | " << quantity << "\n";
    }

    file.close();
    temp.close();
    remove("LibraryData.txt");
    rename("Temp.txt", "LibraryData.txt");

    if (!found) cout << "\nBook Not Found!";
}


void Library::returnBook() {
    string user;
    cout << "\nEnter Book ID to Return: ";
    getline(cin, sID);
    cout << "Enter Your Name: ";
    getline(cin, user);

    bool issued = false;

    // Remove entry from IssuedBooks.txt
    ifstream issueIn("IssuedBooks.txt");
    ofstream tempIssue("TempIssue.txt");

    string bID, uname;
    while (getline(issueIn, bID, '|')) {
        getline(issueIn, uname);
        if (bID == sID && uname == user) {
            issued = true;
            continue; // skip writing this line
        }
        tempIssue << bID << " | " << uname << "\n";
    }
    issueIn.close();
    tempIssue.close();
    remove("IssuedBooks.txt");
    rename("TempIssue.txt", "IssuedBooks.txt");

    // Now increase quantity in LibraryData
    if (issued) {
        file.open("LibraryData.txt", ios::in);
        ofstream temp("Temp.txt");

        while (getline(file, bookID, '|')) {
            getline(file, title, '|');
            getline(file, author, '|');
            getline(file, quantity);

            if (bookID == sID) {
                int q = stoi(quantity);
                q++;
                quantity = to_string(q);
                cout << "\nBook Returned Successfully!";
            }

            temp << bookID << " | " << title << " | " << author << " | " << quantity << "\n";
        }

        file.close();
        temp.close();
        remove("LibraryData.txt");
        rename("Temp.txt", "LibraryData.txt");
    } else {
        cout << "\nNo record found for this user/book!";
    }
}
