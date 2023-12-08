#include "Authors.cpp"
using namespace std;
class Book
{

    
public:
    string isbn;
    string title;
    string authorId;
    Book(string isbn, string title, string authorId)
    {
        this->isbn = isbn;
        this->title = title;
        this->authorId = authorId;
    }
    Book()
    {
    }
};
class BooksManager
{
private:
    string dataFileName = "books.txt";
    string primaryIndexFileName = "bookPrimaryIndex.txt";
    string secondaryIndexFileName = "bookSecondaryIndex.txt";
    string availListFileName = "bookAvailList.txt";

    char delimeter = '|';
    PrimaryIndex *primaryIndex;
    SecondaryIndex *secondaryIndex;

    AvailList *avaiList;


public:
    BooksManager()
    {
        primaryIndex = new PrimaryIndex(primaryIndexFileName, delimeter);
        avaiList = new AvailList(availListFileName,delimeter);
        secondaryIndex = new SecondaryIndex(secondaryIndexFileName,delimeter);
    }
    void saveBookToFileWithDelimiter(Book book)
    {
        if(primaryIndex->getOffsetById(book.isbn) != -1){
            cout << "ID Must Be Unique" << endl;
            return;
        }
        int new_record_size = book.isbn.size() + book.title.size() + book.authorId.size() + 3;
        int validOffsetFromAvailList = avaiList->getValidOffset(new_record_size);
        if(validOffsetFromAvailList != -1){
            fstream outFile(dataFileName);

            string data = getNumberStringWithPadding(new_record_size, 2) + delimeter + book.isbn + delimeter
                    + book.title + delimeter
                    + book.authorId;
            
            primaryIndex->putEntry(book.isbn, validOffsetFromAvailList);
            outFile.seekp(validOffsetFromAvailList,std::ios::beg);
            for(char c : data){
                outFile.put(c);
                validOffsetFromAvailList += 1;
                outFile.seekp(validOffsetFromAvailList,std::ios::beg);
            }
            outFile.seekg(validOffsetFromAvailList,std::ios::beg);
            while(char(outFile.get()) != '\n'){
                outFile.seekp(validOffsetFromAvailList,std::ios::beg);
                outFile.put('_');
                validOffsetFromAvailList += 1;
                outFile.seekg(validOffsetFromAvailList,std::ios::beg);
            }
        }else{
            ofstream outFile(dataFileName, std::ios::app);
            outFile << getNumberStringWithPadding(new_record_size, 2) << delimeter << book.isbn << delimeter
                    << book.title << delimeter
                    << book.authorId << endl;
            int lastOffset = getlastOffset(dataFileName);
            primaryIndex->putEntry(book.isbn, lastOffset);
            updatelastOffset(dataFileName, lastOffset + new_record_size + 4);
        }
        secondaryIndex->putEntry(book.authorId,book.isbn);
    }
    void deleteBook(string id)
    {
        int getBookOffset = primaryIndex->getOffsetById(id);
        if (getBookOffset != -1)
        {
            fstream file(dataFileName);

            if (file.is_open())
            {
                // Move the file pointer to the corresponding offset
                file.seekg(getBookOffset);
                cout << getBookOffset << endl;

                string authorData;
                getline(file, authorData);
                stringstream ss(authorData);
                string size;
                string authorId;
                getline(ss, size, '|');
                getline(ss, authorId, '|');
                getline(ss, authorId, '|');
                getline(ss, authorId, '|');

                int sizeInt = stringToNumber(size);
                avaiList->putEntry(getBookOffset,sizeInt);
                primaryIndex->removeEntry(id);
                secondaryIndex->removeEntry(authorId,id);
                file.seekp(getBookOffset,std::ios::beg);
                file.put('*');
                file.close();
            }
    }
    }
    void updateName(string id,string name)
    {
        int getBookOffset = primaryIndex->getOffsetById(id);
        if (getBookOffset != -1)
        {
            fstream file(dataFileName);

            if (file.is_open())
            {
                // Move the file pointer to the corresponding offset
                file.seekg(getBookOffset);
                cout << getBookOffset << endl;

                string authorData;
                getline(file, authorData);
                stringstream ss(authorData);
                string oldSize;
                string oldId;
                string oldName;
                string oldAuthorID;
                getline(ss, oldSize, '|');
                getline(ss, oldId, '|');
                getline(ss, oldName, '|');
                getline(ss, oldAuthorID, '|');
                Book* newBook = new Book(id,name,oldAuthorID);
                deleteBook(id);
                saveBookToFileWithDelimiter(*newBook);
                file.close();
            }
    }
    }
    void printBookData(string id)
    {
        int getBookOffset = primaryIndex->getOffsetById(id);

        if (getBookOffset != -1)
        {
            fstream file(dataFileName);

            if (file.is_open())
            {
                // Move the file pointer to the corresponding offset
                file.seekg(getBookOffset);

                // Read the book data
                string authorData;
                getline(file, authorData);

                // Print or process the book data as needed
                cout << "Book Data for ID " << id << ": " << authorData << endl;

                file.close();
            }
            else
            {
                cerr << "Error: Unable to open file " << dataFileName << endl;
            }
        }
        else
        {
            cerr << "Error: Unable to get offset for ID " << id << endl;
        }
    }
    ~BooksManager()
    {
        delete primaryIndex;
        delete avaiList;
        delete secondaryIndex;
    }
};
