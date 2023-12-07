#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const int FILE_HEADER_SIZE = sizeof(int);
int lastOffset(string filename){

};
int offsetValVar(int lastoffset,int prevlinesize){
    return lastoffset+prevlinesize+2;
}
//int offsetvalFixed(int rnn)
struct Author {
    string authorId;
    string authorName;
    string authorAddress;
};
struct Book {
    string ISBN;
    string authorId;
    string bookTitle;
};
class FileSystem {
public:
    void saveAuthorToFileWithDelimiter(const Author& author,const std::string& filename) {
        ofstream outFile(filename, std::ios::app);
        outFile <<author.authorId.size()+author.authorName.size()+author.authorAddress.size()+3<<'|'<< author.authorId<<'|'
            << author.authorName <<'|'
            << author.authorAddress << endl;
    }
    vector<Author> loadAuthorsFromFile(const std::string& filename) {
        vector<Author> loadedAuthors;
        ifstream inFile(filename);

        if (!inFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return loadedAuthors;
        }

        while (inFile >> ws && !inFile.eof()) {
            loadedAuthors.push_back(loadAuthorFromFileWithDelimiter(inFile, '|'));
        }

        inFile.close();
        return loadedAuthors;
    }

    Author loadAuthorFromFileWithDelimiter(std::istream& in, char delimiter) {
        Author author;
        int authorIdSize;
        in >> authorIdSize;
        in.ignore();
        author.authorId.resize(authorIdSize);
        in.read(&author.authorId[0], authorIdSize);
        in.ignore();
        int authorNameSize;
        in >> authorNameSize;
        in.ignore();
        author.authorName.resize(authorNameSize);
        in.read(&author.authorName[0], authorNameSize);
        in.ignore();
        int authorAddressSize;
        in >> authorAddressSize;
        in.ignore();
        author.authorAddress.resize(authorAddressSize);
        in.read(&author.authorAddress[0], authorAddressSize);
        in.ignore();
        return author;
    }
    void saveBooksToFile(const std::vector<Book>& books, const std::string& filename) {
        ofstream outFile(filename, std::ios::app);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        for (const auto& book : books) {
            saveBooksToFileWithDelimiter(book, outFile, '|');
        }
        outFile.close();
    }

    void saveBooksToFileWithDelimiter(const Book& books, std::ostream& out, char delimiter) {
        out <<books.ISBN.size()+books.bookTitle.size()+books.authorId.size()+3<<delimiter<< books.ISBN<<delimiter
            << books.bookTitle <<delimiter
            << books.authorId << endl;
    }
    vector<Book> loadBooksFromFile(const std::string& filename) {
        vector<Book> loadedBooks;
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return loadedBooks;
        }

        while (inFile >> std::ws && !inFile.eof()) {
            loadedBooks.push_back(loadBookFromFileWithDelimiter(inFile, '|'));
        }

        inFile.close();
        return loadedBooks;
    }

    Book loadBookFromFileWithDelimiter(std::istream& in, char delimiter) {
        Book book;
        int ISBNSize;
        in >> ISBNSize;
        in.ignore();
        book.ISBN.resize(ISBNSize);
        in.read(&book.ISBN[0], ISBNSize);
        in.ignore();
        int bookTitleSize;
        in >> bookTitleSize;
        in.ignore();
        book.bookTitle.resize(bookTitleSize);
        in.read(&book.bookTitle[0], bookTitleSize);
        in.ignore();
        int authorIdSize;
        in >> authorIdSize;
        in.ignore();
        book.authorId.resize(authorIdSize);
        in.read(&book.authorId[0], authorIdSize);
        in.ignore();
        return book;
    }
private:
    void saveAuthorToFile(const Author& author, std::ostream& out) {
        saveStringWithLength(author.authorId, out);
        saveStringWithLength(author.authorName, out);
        saveStringWithLength(author.authorAddress, out);
        out.put('|'); // Delimiter
    }

    Author loadAuthorFromFile(std::istream& in) {
        Author author;
        author.authorId = loadStringWithLength(in);
        author.authorName = loadStringWithLength(in);
        author.authorAddress = loadStringWithLength(in);
        in.ignore(); // Ignore the delimiter
        return author;
    }

    void saveBookToFile(const Book& book, std::ostream& out) {
        saveStringWithLength(book.ISBN, out);
        saveStringWithLength(book.authorId, out);
        saveStringWithLength(book.bookTitle, out);
        out.put('|'); // Delimiter
    }

    Book loadBookFromFile(std::istream& in) {
        Book book;
        book.ISBN = loadStringWithLength(in);
        book.authorId = loadStringWithLength(in);
        book.bookTitle = loadStringWithLength(in);
        in.ignore(); // Ignore the delimiter
        return book;
    }

    void saveStringWithLength(const std::string& str, std::ostream& out) {
        int length = str.length();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(str.c_str(), length);
    }

    std::string loadStringWithLength(std::istream& in) {
        int length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        std::string str;
        str.resize(length);
        in.read(&str[0], length);
        return str;
    }
};

int main() {
    FileSystem fileSystem;
//    Author ahmed;
//    ahmed.authorId="0070";
//    ahmed.authorAddress="btengan";
//    ahmed.authorName="ahmed";
//    fileSystem.saveAuthorToFileWithDelimiter(ahmed,"authors.txt");
    std::vector<Book> books = {
            {"B001", "A001", "The Book Title"},
            {"B002", "A002", "Another Book"}
    };
//    fileSystem.saveAuthorsToFile(authors, "authors.txt");
    fileSystem.saveBooksToFile(books, "books.txt");
    vector<Author> loadedAuthors = fileSystem.loadAuthorsFromFile("authors.txt");
    vector<Book> loadedBooks = fileSystem.loadBooksFromFile("books.txt");
    cout << "Loaded Authors:\n";
    for (const auto& author : loadedAuthors) {
        std::cout << "Author: " << author.authorName << ", Address: " << author.authorAddress << std::endl;
    }
    cout << "\nLoaded Books:\n";
    for (const auto& book : loadedBooks) {
        cout << "Title: " << book.bookTitle << ", ISBN: " << book.ISBN << std::endl;
    }
    return 0;
}
