#include <iostream>

using namespace std;

const int MAX_BOOKS = 100;
const char* CATEGORIES[] = {"Fiction", "Non-fiction"};

void myStrcpy(char* dest, const char* src) {
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

int myStrcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

bool isAlphanumeric(const char* str) {
    bool hasLetter = false;
    bool hasDigit = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            hasDigit = true;
        } else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
            hasLetter = true;
        } else {
            return false;
        }
    }
    return hasLetter && hasDigit;
}


bool isNumeric(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false; 
        }
    }
    return true; 
}


class IBook {
public:
    virtual void setBook(const char* i, const char* is, const char* t, const char* a, const char* e, const char* p, const char* c) = 0;
    virtual const char* getId() const = 0;
    virtual const char* getCategory() const = 0;
    virtual void displayBook() const = 0;
    virtual void editBook(const char* is, const char* t, const char* a, const char* e, const char* p, const char* c) = 0;
    virtual ~IBook() {}
};


class Book : public IBook {
private:
    char id[20], isbn[20], title[100], author[100], edition[20], publication[100], category[20];

public:
    void setBook(const char* i, const char* is, const char* t, const char* a, const char* e, const char* p, const char* c) override {
        myStrcpy(id, i);
        myStrcpy(isbn, is);
        myStrcpy(title, t);
        myStrcpy(author, a);
        myStrcpy(edition, e);
        myStrcpy(publication, p);
        myStrcpy(category, c);
    }
    
    const char* getId() const override { return id; }
    const char* getCategory() const override { return category; }
    
    void displayBook() const override {
        cout << "| " << id << " | " << isbn << " | " << title << " | " << author << " | " << edition << " | " << publication << " | " << category << " |" << endl;
    }
    
    void editBook(const char* is, const char* t, const char* a, const char* e, const char* p, const char* c) override {
        myStrcpy(isbn, is);
        myStrcpy(title, t);
        myStrcpy(author, a);
        myStrcpy(edition, e);
        myStrcpy(publication, p);
        myStrcpy(category, c);
    }
};


class ILibrary {
public:
    virtual void addBook() = 0;
    virtual void editBook() = 0;
    virtual void searchBook() = 0;
    virtual void deleteBook() = 0;
    virtual void viewBooksByCategory() = 0;
    virtual void viewAllBooks() = 0;
    virtual ~ILibrary() {}
};


class Library : public ILibrary {
private:
    Book books[MAX_BOOKS];
    int bookCount;

public:
    Library() : bookCount(0) {}

    bool isValidCategory(const char* cat) {
        for (int i = 0; i < 2; i++) {
            if (myStrcmp(CATEGORIES[i], cat) == 0) return true;
        }
        return false;
    }

    bool isDuplicateId(const char* id) {
        for (int i = 0; i < bookCount; i++) {
            if (myStrcmp(books[i].getId(), id) == 0) return true;
        }
        return false;
    }

    void addBook() override {
        if (bookCount >= MAX_BOOKS) {
            cout << "Library is full!" << endl;
            return;
        }
        char id[20], isbn[20], title[100], author[100], edition[20], publication[100], category[20];
        
        do {
            cout << "Enter Category (Fiction/Non-fiction): ";
            cin >> category;
            if (!isValidCategory(category)) cout << "Category not found! Try again." << endl;
        } while (!isValidCategory(category));
        
        do {
            cout << "Enter ID (Alphanumeric only): ";
            cin >> id;
            if (!isAlphanumeric(id)) {
                cout << "Invalid ID! Only alphanumeric characters allowed, and it must contain both letters and digits." << endl;
            } else if (isDuplicateId(id)) {
                cout << "Duplicate ID! Enter another." << endl;
            } else {
                break;
            }
        } while (true);
        
        do {
            cout << "Enter ISBN: ";
            cin >> isbn;
            if (!isNumeric(isbn)) {
                cout << "Invalid ISBN! Only numeric characters are allowed." << endl;
            } else {
                break;
            }
        } while (true);
        
        cin.ignore();
        cout << "Enter Title: "; cin.getline(title, 100);
        cout << "Enter Author: "; cin.getline(author, 100);
        cout << "Enter Edition: "; cin.getline(edition, 20);
        cout << "Enter Publication: "; cin.getline(publication, 100);
        
        books[bookCount].setBook(id, isbn, title, author, edition, publication, category);
        bookCount++;
        cout << "Book added successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void editBook() override {
        char id[20];
        cout << "Enter Book ID to edit: "; cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (myStrcmp(books[i].getId(), id) == 0) {
                char isbn[20], title[100], author[100], edition[20], publication[100], category[20];
                do {
                    cout << "Enter new ISBN: "; cin >> isbn;
                    if (!isNumeric(isbn)) {
                        cout << "Invalid ISBN! Only numeric characters are allowed." << endl;
                    } else {
                        break;
                    }
                } while (true);
                
                cin.ignore();
                cout << "Enter new Title: "; cin.getline(title, 100);
                cout << "Enter new Author: "; cin.getline(author, 100);
                cout << "Enter new Edition: "; cin.getline(edition, 20);
                cout << "Enter new Publication: "; cin.getline(publication, 100);
                cout << "Enter new Category (Fiction/Non-fiction): "; cin >> category;
                if (isValidCategory(category)) {
                    books[i].editBook(isbn, title, author, edition, publication, category);
                    cout << "Book edited successfully!" << endl;
                } else {
                    cout << "Invalid category! Book not edited." << endl;
                }
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Book not found!" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void searchBook() override {
        char id[20];
        cout << "Enter Book ID to search: ";
        cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (myStrcmp(books[i].getId(), id) == 0) {
                cout << "Book found:" << endl;
                books[i].displayBook();
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Book not found!" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void deleteBook() override {
        char id[20];
        cout << "Enter Book ID to delete: ";
        cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (myStrcmp(books[i].getId(), id) == 0) {
                cout << "Book details:" << endl;
                books[i].displayBook();
                char confirm;
                cout << "Do you want to delete this book? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    for (int j = i; j < bookCount - 1; j++) {
                        books[j] = books[j + 1];
                    }
                    bookCount--;
                    cout << "Book deleted successfully!" << endl;
                } else {
                    cout << "Book not deleted." << endl;
                }
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Book not found!" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void viewBooksByCategory() override {
        char category[20];
        cout << "Enter Category (Fiction/Non-fiction): ";
        cin >> category;
        if (!isValidCategory(category)) {
            cout << "Category not found!" << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            return;
        }
        cout << "Books in category " << category << ":" << endl;
        cout << "| ID | ISBN | Title | Author | Edition | Publication | Category |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (myStrcmp(books[i].getCategory(), category) == 0) {
                books[i].displayBook();
                found = true;
            }
        }
        if (!found) {
            cout << "No books found in this category." << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    void viewAllBooks() override {
        if (bookCount == 0) {
            cout << "No books in the library." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            return;
        }
        cout << "All books in the library:" << endl;
        cout << "| ID | ISBN | Title | Author | Edition | Publication | Category |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        for (int i = 0; i < bookCount; i++) {
            books[i].displayBook();
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }
};

int main() {
    Library lib;
    int choice;
    do {
        cout << "\n1 - Add Book" << endl;
        cout << "2 - Edit Book" << endl;
        cout << "3 - Search Book" << endl;
        cout << "4 - Delete Book" << endl;
        cout << "5 - View Books by Category" << endl;
        cout << "6 - View All Books" << endl;
        cout << "7 - Exit" << endl;
        cout << "Enter your choice: ";

        
        string input;
        cin >> input;

        
        bool validInput = true;
        for (char c : input) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            choice = 0; 
            for (char c : input) {
                choice = choice * 10 + (c - '0'); 
            }
        } else {
            cout << "Invalid choice! Please enter a number." << endl;
            continue; 
        }

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.editBook();
                break;
            case 3:
                lib.searchBook();
                break;
            case 4:
                lib.deleteBook();
                break;
            case 5:
                lib.viewBooksByCategory();
                break;
            case 6:
                lib.viewAllBooks();
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}