#include "QueryProcessing.cpp"
using namespace std;
const int FILE_HEADER_SIZE = sizeof(int);
void displayMenu() {
    AuthorsManager* manager = new AuthorsManager();
    BooksManager* bookManager = new BooksManager();
    QueryProcessor* proccessor = new QueryProcessor(manager,bookManager);

    Author author;
    Book book;
    string query;
    while (true) {
        cout << "Library Management System\n";
        cout << "1. Add New Author\n";
        cout << "2. Add New Book\n";
        cout << "3. Update Author Name (Author ID)\n";
        cout << "4. Update Book Title (ISBN)\n";
        cout << "5. Delete Book (ISBN)\n";
        cout << "6. Delete Author (Author ID)\n";
        cout << "7. Print Author (Author ID)\n";
        cout << "8. Print Book (ISBN)\n";
        cout << "9. Write Query\n";
        cout << "10. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Author author;
                cout << "Enter Author name: ";
                cin >> author.authorName;
                cout << "Enter Author ID: ";
                cin >> author.authorId;
                cout << "Enter Author address: ";
                cin >> author.authorAddress;
                manager->saveAuthorToFileWithDelimiter(author);
                break;
            }
            case 2: {
                Book book;
                cout << "Enter Book ISBN: ";
                cin >> book.isbn;
                cout << "Enter Book Title: ";
                cin >> book.title;
                cout << "Enter Author ID: ";
                cin >> book.authorId;
                bookManager->saveBookToFileWithDelimiter(book);
                break;
            }
            case 3: {
                Author author;
                cout << "Enter your ID: ";
                cin >> author.authorId;
                cout << "Enter Author new name: ";
                cin >> author.authorName;
                manager->updateName(author.authorId, author.authorName);
                break;
            }
            case 4: {
                Book book;
                cout << "Enter Book ISBN: ";
                cin >> book.isbn;
                cout << "Enter book new Title: ";
                cin >> book.title;
                bookManager->updateName(book.isbn, book.title);
                break;
            }
            case 5: {
                Book book;
                cout << "Enter Book ISBN: ";
                cin >> book.isbn;
                bookManager->deleteBook(book.isbn);
                break;
            }
            case 6: {
                Author author;
                cout << "Enter your ID: ";
                cin >> author.authorId;
                manager->deleteAuthor(author.authorId);
                break;
            }
            case 7: {
                Author author;
                cout << "Enter your ID: ";
                cin >> author.authorId;
                manager->printAuthorData(author.authorId);
                break;
            }
            case 8: {
                Book book;
                cout << "Enter Book ISBN: ";
                cin >> book.isbn;
                bookManager->printBookData(book.isbn);
                break;
            }
            case 9:
                cout << "Write Query\n";
                cin.ignore();

                getline(cin,query);
                proccessor->processQuery(query);
                // Add your query logic here
                break;
            case 10:
                cout << "Exiting...\n";
                delete manager;
                delete bookManager;
                exit(0);
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
    delete manager;
    delete bookManager;
}

int main() {
    displayMenu();
    return 0;
}
