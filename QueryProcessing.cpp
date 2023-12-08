//
// Created by abdel on 12/8/2023.
//

#include "books.cpp"
using namespace std;

class QueryProcessor {
public:
    AuthorsManager* manager;
    BooksManager* booksManager;

    QueryProcessor(AuthorsManager* manager,BooksManager* booksManager) : manager(manager),booksManager(booksManager) {}

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
        // std::string selectKeyword;
        std::string attribute;
        std::string fromKeyword;
        std::string entity;
        std::string whereKeyword;
        std::string conditionAttribute;
        std::string conditionValue;
        std::string equalSign;


        // stream >> selectKeyword;
        stream >> attribute;
        stream >> fromKeyword;
        stream >> entity;
        stream >> whereKeyword;
        stream >> conditionAttribute;
        stream >> equalSign;
        stream >> conditionValue;

        

        // Convert attribute and conditionAttribute to lowercase for case-insensitive comparison
        std::transform(attribute.begin(), attribute.end(), attribute.begin(), ::tolower);
        std::transform(conditionAttribute.begin(), conditionAttribute.end(), conditionAttribute.begin(), ::tolower);
        conditionValue = trim(conditionValue);
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
            if(conditionAttribute == "authorid"){
                manager->printAuthorData(conditionValue);
            }else if(conditionAttribute == "authorname"){
                manager->getAllAuthorsWithName(conditionValue);
            }
        } else if (attribute == "authorname") {
            // Select Author Name from Authors
            if(conditionAttribute == "authorid"){
                manager->printAuthorData(conditionValue,true);
            }else if(conditionAttribute == "authorname"){
                manager->getAllAuthorsWithName(conditionValue,true);
            }
        } else {
            std::cout << "Invalid attribute in query" << std::endl;
        }
    }

    void processBookQuery(const std::string& attribute, const std::string& conditionAttribute, const std::string& conditionValue) {
        if (attribute == "all") {
            if(conditionAttribute == "isbn"){
                booksManager->printBookData(conditionValue);
            }else if(conditionAttribute == "authorid"){
                booksManager->getAllAuthorsWithAuthorId(conditionValue);
            }
        }else {
            std::cout << "Invalid attribute in query" << std::endl;
        }
    }



};

