#include "util.cpp"
using namespace std;
class SecondaryIndexListElement
{
public:
    string id;
    int index;
    SecondaryIndexListElement *next;
    SecondaryIndexListElement(string id) : id(id), next(nullptr) {}
};
class SecondaryIndexList
{
public:
    SecondaryIndexList() : head(nullptr) {}
    SecondaryIndexListElement *head;
    void insertEelement(SecondaryIndexListElement *item)
    {
        if (head == nullptr)
        {
            head = item;
            return;
        }

        SecondaryIndexListElement *current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = item;
    }
    void removeItem(string id){
        SecondaryIndexListElement* current = head;
        SecondaryIndexListElement* prev = nullptr;
        while(current){
            if(current->id == id){
                if(current != head){
                    prev->next = current->next;
                }else{
                    head = head->next;
                }
            }
            prev = current;
            current = current->next;
        }
    }

    vector<SecondaryIndexListElement *> getItems()
    {
        vector<SecondaryIndexListElement *> res;
        SecondaryIndexListElement *current = head;
        while (current)
        {
            res.push_back(current);
            current = current->next;
        }
        return res;
    }
};
class SecondaryIndex
{
private:
    map<string, SecondaryIndexList *> secondaryKeyToHead;
    string filename;

    char delimiter;

public:
    SecondaryIndex(string filename, char delimiter) : filename(filename), delimiter(delimiter)
    {
        loadDataFromFile();
    }

    ~SecondaryIndex()
    {
        // cout << "askcaslcmasca" << endl;
        saveDataToFile();
    }

    void loadDataFromFile()
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(delimiter);
            if (pos != string::npos)
            {
                string name = line.substr(0, pos);
                string ids = line.substr(pos + 1);
                std::istringstream iss(ids);
                std::string substring;
                SecondaryIndexList *list = new SecondaryIndexList();

                while (std::getline(iss, substring, ',')) {
                    list->insertEelement(new SecondaryIndexListElement(substring));
                }
                secondaryKeyToHead[name] = list;
            }
        }
        file.close();
    }

    void saveDataToFile() const
    {
        ofstream file(filename);
        cout << "1"  << endl;
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }
        for (const auto &pair : secondaryKeyToHead)
        {
            vector<SecondaryIndexListElement *> items = pair.second->getItems();
            string data = pair.first + delimiter;
            for (auto item : items)
            {
                data += item->id + ",";
            }
            file << data << endl;
        }

        file.close();
    }

    vector<string> getIdsFromName(string name) {
        
        vector<SecondaryIndexListElement *> elements =  secondaryKeyToHead[name]->getItems();
        vector<string> ids;
        for(auto item : elements){
            ids.push_back(item->id);
        }
        return ids;
    }

    // Function to put a new entry into the map by specifying both ID and offset
    void putEntry(const string &name, string id)
    {
        if(secondaryKeyToHead.find(name) == secondaryKeyToHead.end()){
            secondaryKeyToHead[name] = new SecondaryIndexList();
        }
        secondaryKeyToHead[name]->insertEelement(new SecondaryIndexListElement(id));
    }
    void removeEntry(string name,string id){
        cout << name << " , " << id;
        secondaryKeyToHead[name]->removeItem(id);
    }

};
