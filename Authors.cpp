#include <bits/stdc++.h>
#include "PrimaryIndex.cpp"
#include "SecondaryIndex.cpp"
#include "availList.cpp"

using namespace std;
class Author
{
private:
    string dataFileName = "authors.txt";
    string primaryIndexFileName = "autherPrimaryIndex.txt";
    string secondaryIndexFileName = "authorSecondaryIndex.txt";
    string secondaryIndexFileNameLines = "authorSecondaryIndexLinks.txt";

    string delimeter = "|";
    
public:
    string authorId;
    string authorName;
    string authorAddress;
    Author(string authorId, string authorName, string authorAddress)
    {
        this->authorId = authorId;
        this->authorName = authorName;
        this->authorAddress = authorAddress;
    }
    Author()
    {
    }
};
class AuthorsManager
{
private:
    string dataFileName = "authors.txt";
    string primaryIndexFileName = "autherPrimaryIndex.txt";
    string availListFileName = "autherAvailList.txt";
    string secondaryIndexFileName = "authorSecondaryIndex.txt";
    string secondaryIndexFileNameLines = "authorSecondaryIndexLinks.txt";
    char delimeter = '|';
    PrimaryIndex *primaryIndex;
    SecondaryIndex *secondaryIndex;

    AvailList *avaiList;


public:
    AuthorsManager()
    {
        primaryIndex = new PrimaryIndex(primaryIndexFileName, delimeter);
        avaiList = new AvailList(availListFileName,delimeter);
        secondaryIndex = new SecondaryIndex(secondaryIndexFileName,delimeter);
    }
    void saveAuthorToFileWithDelimiter(Author author)
    {
        if(primaryIndex->getOffsetById(author.authorId) != -1){
            cout << "ID Must Be Unique" << endl;
            return;
        }
        int new_record_size = author.authorId.size() + author.authorName.size() + author.authorAddress.size() + 3;
        int validOffsetFromAvailList = avaiList->getValidOffset(new_record_size);
        if(validOffsetFromAvailList != -1){
            fstream outFile(dataFileName);

            string data = getNumberStringWithPadding(new_record_size, 2) + delimeter + author.authorId + delimeter
                    + author.authorName + delimeter
                    + author.authorAddress;
            
            primaryIndex->putEntry(author.authorId, validOffsetFromAvailList);
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
            outFile << getNumberStringWithPadding(new_record_size, 2) << delimeter << author.authorId << delimeter
                    << author.authorName << delimeter
                    << author.authorAddress << endl;
            int lastOffset = getlastOffset(dataFileName);
            primaryIndex->putEntry(author.authorId, lastOffset);
            updatelastOffset(dataFileName, lastOffset + new_record_size + 4);
        }
        secondaryIndex->putEntry(author.authorName,author.authorId);
    }
    void deleteAuthor(string id)
    {
        int getAuthorOffset = primaryIndex->getOffsetById(id);
        if (getAuthorOffset != -1)
        {
            fstream file(dataFileName);

            if (file.is_open())
            {
                // Move the file pointer to the corresponding offset
                file.seekg(getAuthorOffset);
                cout << getAuthorOffset << endl;

                string authorData;
                getline(file, authorData);
                stringstream ss(authorData);
                string size;
                string name;
                getline(ss, size, '|');
                getline(ss, name, '|');
                getline(ss, name, '|');
                int sizeInt = stringToNumber(size);
                avaiList->putEntry(getAuthorOffset,sizeInt);
                primaryIndex->removeEntry(id);
                secondaryIndex->removeEntry(name,id);
                file.seekp(getAuthorOffset,std::ios::beg);
                file.put('*');
                file.close();
            }
    }
    }
    void updateName(string id,string name)
    {
        int getAuthorOffset = primaryIndex->getOffsetById(id);
        if (getAuthorOffset != -1)
        {
            fstream file(dataFileName);

            if (file.is_open())
            {
                file.seekg(getAuthorOffset);
                cout << getAuthorOffset << endl;
                string authorData;
                getline(file,authorData);
                stringstream ss(authorData);
                string oldSize;
                string oldId;
                string oldName;
                string oldAddress;
                getline(ss, oldSize, '|');
                getline(ss, oldId, '|');
                getline(ss, oldName, '|');
                getline(ss, oldAddress, '|');
                Author* newAuthor = new Author(id,name,oldAddress);
                deleteAuthor(id);
                saveAuthorToFileWithDelimiter(*newAuthor);
                file.close();
            }
    }
    }
    void printAuthorData(string id,bool onlyName = false)
    {
        int getAuthorOffset = primaryIndex->getOffsetById(id);

        if (getAuthorOffset != -1)
        {
            fstream file(dataFileName);

            if (file.is_open())
            {
                // Move the file pointer to the corresponding offset
                file.seekg(getAuthorOffset + 2);

                // Read the author data
                string authorData;
                getline(file, authorData);
                stringstream ss(authorData);
                string oldSize;
                string oldId;
                string oldName;
                string oldAddress;
                getline(ss, oldSize, '|');
                getline(ss, oldId, '|');
                getline(ss, oldName, '|');
                getline(ss, oldAddress, '_');
                if(!onlyName){
                    cout << oldId << " ";
                }
                    cout << oldName << " ";
                if(!onlyName){
                    cout << oldAddress << " ";
                }

                file.close();
            }
            else
            {
                cerr << "Error: Unable to open file " << dataFileName << endl;
            }
        }
        else
        {
            cerr << "Error: Unable to get offset for ID " << id.size() << endl;
        }
    }
    void getAllAuthorsWithName(string name,bool onlyName = false){
        for(string id : secondaryIndex->getIdsFromName(name)){
            printAuthorData(id,onlyName);
        }
    }
    ~AuthorsManager()
    {
        delete primaryIndex;
        delete avaiList;
        delete secondaryIndex;
    }
};
