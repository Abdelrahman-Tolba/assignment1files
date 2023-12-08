#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class AvailListElement{
    public:
        int size;
        int offset;
        AvailListElement* next;
            AvailListElement(int offset, int size) : offset(offset), size(size), next(nullptr) {}

};
class AvailList {
private:
    string filename;
    char delimiter;
    AvailListElement* head;

public:
    AvailList(string filename, char delimiter) : filename(filename), delimiter(delimiter),head(nullptr){
        loadDataFromFile();
    }

    ~AvailList() {
        saveDataToFile();
    }
    void insertEelement(AvailListElement* item){
        if(head == nullptr){

            head = item;
            return;
        }

        AvailListElement* current = head;
        while(current->next){
            current = current->next;
        }
        current->next = item;

    }
    void loadDataFromFile() {
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t pos = line.find(delimiter);
            if (pos != string::npos) {
                int offset = stoi(line.substr(0, pos));
                int size = stoi(line.substr(pos + 1));
                insertEelement(new AvailListElement(offset,size));
            }
        }

        file.close();
    }

    void saveDataToFile() const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }
        AvailListElement* current = head;
        while (current){
            file << current->offset << delimiter << current->size << endl;
            current = current->next;
        }
        file.close();
    }

    // Function to get offset by ID
    int getValidOffset(int size) {
        int defaultOffset = -1;
        AvailListElement* current = head;
        AvailListElement* prev = nullptr;
        while(current){
            if(current->size >= size){
                if(current != head){
                    prev->next = current->next;
                }else{
                    head = nullptr;
                }
                return current->offset;
            }
            prev = current;
            current = current->next;
        }
        return defaultOffset;
    }
    
    // Function to put a new entry into the map by specifying both ID and offset
    void putEntry(int offset,int size) {
        insertEelement(new AvailListElement(offset,size));
    }
};
