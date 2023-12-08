#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;


class PrimaryIndex {
private:
    map<string, int> primaryKeyToOffset;
    string filename;
    char delimiter;

public:
    PrimaryIndex(string filename, char delimiter) : filename(filename), delimiter(delimiter) {
        loadDataFromFile();
    }

    ~PrimaryIndex() {
        cout << "askcaslcmasca" << endl;
        saveDataToFile();
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
                string id = line.substr(0, pos);
                int offset = stoi(line.substr(pos + 1));
                primaryKeyToOffset[id] = offset;
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

        for (const auto& pair : primaryKeyToOffset) {
            file << pair.first << delimiter << pair.second << endl;
        }

        file.close();
    }

    // Function to get offset by ID
    int getOffsetById(const string& id) const {
        auto it = primaryKeyToOffset.find(id);
        if (it != primaryKeyToOffset.end()) {
            return it->second;
        } else {
            // Return a special value or throw an exception to indicate that the ID was not found
            cerr << "Error: ID not found." << endl;
            return -1; // Or throw an exception
        }
    }

    // Function to put a new entry into the map by specifying both ID and offset
    void putEntry(const string& id, int offset) {
        primaryKeyToOffset[id] = offset;
    }
    void removeEntry(string id){
        auto it = primaryKeyToOffset.find(id);
        if (it != primaryKeyToOffset.end()) {
            primaryKeyToOffset.erase(it);
        }
    }
};
