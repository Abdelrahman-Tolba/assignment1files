//
// Created by abdel on 12/8/2023.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

struct Author {
    std::string authorId;
    std::string authorName;
    std::string authorAddress;
};

struct Book {
    std::string ISBN;
    std::string authorId;
    std::string bookTitle;
};

class QueryProcessor {
public:
    QueryProcessor(std::vector<Author>& authors, std::vector<Book>& books)
            : authors(authors), books(books) {}

    void processQuery(const std::string& query) {
        std::istringstream stream(query);
        std::string keyword;
        stream >> keyword;

        // Convert the keyword to lowercase for case-insensitive comparison
        std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

        if (keyword == "select") {
            processSelectQuery(stream);
        } else {
            std::cout << "Invalid query" << std::endl;
        }
    }

private:
    void processSelectQuery(std::istringstream& stream) {
        std::string selectKeyword;
        std::string attribute;
        std::string fromKeyword;
        std::string entity;
        std::string whereKeyword;
        std::string conditionAttribute;
        std::string conditionValue;

        stream >> selectKeyword;
        stream >> attribute;
        stream >> fromKeyword;
        stream >> entity;
        stream >> whereKeyword;
        stream >> conditionAttribute;
        stream.ignore(); // Ignore the single quote
        std::getline(stream, conditionValue, '\'');

        // Convert attribute and conditionAttribute to lowercase for case-insensitive comparison
        std::transform(attribute.begin(), attribute.end(), attribute.begin(), ::tolower);
        std::transform(conditionAttribute.begin(), conditionAttribute.end(), conditionAttribute.begin(), ::tolower);

        if (entity == "authors") {
            processAuthorQuery(attribute, conditionAttribute, conditionValue);
        } else if (entity == "books") {
            processBookQuery(attribute, conditionAttribute, conditionValue);
        } else {
            std::cout << "Invalid entity in query" << std::endl;
        }
    }

    void processAuthorQuery(const std::string& attribute, const std::string& conditionAttribute, const std::string& conditionValue) {
        if (attribute == "all") {
            // Select all from Authors
            for (const auto& author : authors) {
                if (authorMatchesCondition(author, conditionAttribute, conditionValue)) {
                    printAuthor(author);
                }
            }
        } else if (attribute == "authorname") {
            // Select Author Name from Authors
            for (const auto& author : authors) {
                if (authorMatchesCondition(author, conditionAttribute, conditionValue)) {
                    std::cout << "Author Name: " << author.authorName << std::endl;
                }
            }
        } else {
            std::cout << "Invalid attribute in query" << std::endl;
        }
    }

    void processBookQuery(const std::string& attribute, const std::string& conditionAttribute, const std::string& conditionValue) {
        if (attribute == "all") {
            // Select all from Books
            for (const auto& book : books) {
                if (bookMatchesCondition(book, conditionAttribute, conditionValue)) {
                    printBook(book);
                }
            }
        } else {
            std::cout << "Invalid attribute in query" << std::endl;
        }
    }

    bool authorMatchesCondition(const Author& author, const std::string& conditionAttribute, const std::string& conditionValue) const {
        if (conditionAttribute == "authorid") {
            return author.authorId == conditionValue;
        } else {
            std::cout << "Invalid condition attribute in query" << std::endl;
            return false;
        }
    }

    bool bookMatchesCondition(const Book& book, const std::string& conditionAttribute, const std::string& conditionValue) const {
        if (conditionAttribute == "authorid") {
            return book.authorId == conditionValue;
        } else {
            std::cout << "Invalid condition attribute in query" << std::endl;
            return false;
        }
    }

    void printAuthor(const Author& author) const {
        std::cout << "Author ID: " << author.authorId << ", Author Name: " << author.authorName
                  << ", Author Address: " << author.authorAddress << std::endl;
    }

    void printBook(const Book& book) const {
        std::cout << "ISBN: " << book.ISBN << ", Author ID: " << book.authorId
                  << ", Book Title: " << book.bookTitle << std::endl;
    }

    std::vector<Author>& authors;
    std::vector<Book>& books;
};

int main() {
    std::vector<Author> authors = {
            {"A001", "John Doe", "123 Main Street"},
            {"A002", "Jane Smith", "456 Oak Avenue"}
    };

    std::vector<Book> books = {
            {"B001", "A001", "The Book Title"},
            {"B002", "A002", "Another Book"}
    };

    QueryProcessor queryProcessor(authors, books);

    // Example queries
    queryProcessor.processQuery("Select all from Authors where Author ID='A001';");
    queryProcessor.processQuery("Select Author Name from Authors where Author ID='A002';");
    queryProcessor.processQuery("Select all from Books where Author ID='A001';");

    return 0;
}
