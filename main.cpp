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
class Author {
    public:
        string authorId;
        string authorName;
        string authorAddress;
        Author(string authorId,string authorName,string authorAddress){
            this->authorId = authorId;
            this->authorName = authorName;
            this->authorAddress = authorAddress;

        }
        Author(){
            
        }
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


private:
    void saveAuthorToFile(const Author& author, std::ostream& out) {
        saveStringWithLength(author.authorId, out);
        saveStringWithLength(author.authorName, out);
        saveStringWithLength(author.authorAddress, out);
        out.put('|'); // Delimiter
    }

    Author* loadAuthorFromFile(std::istream& in) {
        Author* author = new Author(loadStringWithLength(in), loadStringWithLength(in),loadStringWithLength(in));
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
    vector<Author*> demoAuthers = {
        new Author("001","hatem","maadi"),
        new Author("002","tolba","maadi"),
        new Author("003","ahmed","maadi"),
        new Author("004","mohamed","maadi"),
    };
    for(auto a : demoAuthers){
        fileSystem.saveAuthorToFileWithDelimiter(*a,"authors.txt");
    }
    vector<Author> loadedAuthors = fileSystem.loadAuthorsFromFile("authors.txt");

    cout << "Loaded Authors:\n";
    for (const auto& author : loadedAuthors) {
        std::cout << "Author: " << author.authorName << ", Address: " << author.authorAddress << std::endl;
    }

    return 0;
}
