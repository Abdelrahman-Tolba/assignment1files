#include <bits/stdc++.h>
using namespace std;
int stringToNumber(string str) {
    return stoi(str);
}
    template<typename t>
    void LinkedListinsertEelement(t* item,t* head){
        if(head == nullptr){
            cout << "sacmasclaskmcasssscccccrrr" << endl;
            head = item;
            return;
        }
        t* current = head;
        while(current->next){
            current = current->next;
        }
        current->next = item;
    }
string getNumberStringWithPadding(int n,int padding_size){
    string numberString = std::to_string(n);

    // Calculate the padding needed
    int padding_needed = padding_size - numberString.length();

    // Add padding if needed
    if (padding_needed > 0) {
        numberString = std::string(padding_needed, '0') + numberString;
    }

    return numberString;
}
int getlastOffset(string filename){
    ifstream inFile(filename, std::ios::in);
    int start = 9;
    inFile.seekg(start);
    string num = "";
    while(inFile.get() != '_'){
        num += inFile.get();
        start += 1;
        inFile.seekg(start);
    }
    return stringToNumber(num);
}
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r;");
    size_t end = str.find_last_not_of(" \t\n\r;");

    if (start == std::string::npos || end == std::string::npos) {
        return "";  // String contains only whitespace
    }

    return str.substr(start, end - start + 1);
}
void updatelastOffset(string filename,int lastOffset){
    fstream inFile(filename);
    int start = 10;
    string lastOffsetWithPadding = getNumberStringWithPadding(lastOffset,2);
    inFile.seekp(start);
    for(const char c : lastOffsetWithPadding){
        inFile.put(c);
        start += 1;
    }
}
int offsetValVar(int lastoffset,int prevlinesize){
    return lastoffset+prevlinesize+2;
}