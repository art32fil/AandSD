#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class HashTable{
private:
    list<int> *table;
    int total_elements;

    // Hash function to calculate hash for a value:
    [[nodiscard]] int getHash(int key) const{
        return key % total_elements;
    }

public:
    // Constructor to create a hash table with 'n' indices:
    explicit HashTable(int n){
        total_elements = n;
        table = new list<int>[total_elements];
    }

    // Insert data in the hash table:
    void insertElement(int key){
        table[getHash(key)].push_back(key);
    }

    // Remove data from the hash table:
    void removeElement(int key, ofstream &output){
        int x = getHash(key);

        list<int>::iterator i;
        for (i = table[x].begin(); i != table[x].end(); i++) {
            // Check if the iterator points to the required item:
            if (*i == key)
                break;
        }

        // If the item was found in the list, then delete it:
        if (i != table[x].end())
            table[x].erase(i);
        else{
            output<<"[WARNING] Key not found!\n";
            cout << "[WARNING] Key not found!\n";
        }

    }

    void printAll(ofstream &output){
        // Traverse each index:
        for(int i = 0; i < total_elements; i++){
            output << "Index " << i << ": ";
            cout << "Index " << i << ": ";
            // Traverse the list at current index:
            for(int j : table[i]) {
                output << j << " => ";
                cout << j << " => ";
            }

            output << endl;
            cout << endl;
        }
    }

    void printSearch(int key, ofstream &output){
        for(int i = 0; i < total_elements; i++){
            if (i == key){
                for(int j : table[i]) {
                    output << j << " => ";
                    cout << j << " => ";
                }
            }

        }
    }
};


void checkStr(std::string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])&&str[i]!=' '&&str[i] != '-') {
            str.erase(i, 1);
            i -= 1;
        }
    }
}

int main() {
    vector<int> nums;
    // Create a hash table with 3 indices:
    HashTable ht(5);

    // Declare the data to be stored in the hash table:
    ifstream input("./tests/input.txt");
    ofstream output("./tests/result.txt");
    std::string numbers;
    int value;
    input>>noskipws;
    if(!input){
        output<<"Can't open this file!";
        return 0;
    }
    std::getline(input, numbers);
    checkStr(numbers);
    std::stringstream ss(numbers);
    while (ss >> value) {
        nums.push_back(value);
        if (ss.peek() == ' ') {
            ss.ignore();
        }
    }
    for(int i : nums) {
        ht.insertElement(i);
    }
    while(true){
        output << "\nMENU:\n"
                  "1: Print HashTable\n"
                  "2: Add element\n"
                  "3: Delete element\n"
                  "4: Print elements by key\n"
                  "Another key: Quit\n";
        cout << "\nMENU:\n"
                  "1: Print HashTable\n"
                  "2: Add element\n"
                  "3: Delete element\n"
                  "4: Print elements by key\n"
                  "Another key: Quit\n";
        int choose;
        std::cin >> choose;
        output << choose << endl;
        switch (choose) {
            case 1:
                output << "[INFO]Hash Table" << endl;
                cout << "[INFO]Hash Table" << endl;
                ht.printAll((ofstream &) output);
                break;
            case 2:
                int addValue;
                output << "[QUESTION]Which value you want to insert?\n";
                cout << "[QUESTION]Which value you want to insert?\n";
                std::cin >> addValue;
                output << addValue << endl;
                cout << addValue << endl;
                ht.insertElement(addValue);
                output << endl << "[INFO]After adding " << addValue << '\n';
                cout << endl << "[INFO]After adding " << addValue << '\n';
                ht.printAll((ofstream &) output);
                break;
            case 3:
                int rmValue;
                output << "[QUESTION]Which value you want to delete?\n";
                cout << "[QUESTION]Which value you want to delete?\n";
                std::cin >> rmValue;
                output << rmValue << endl;
                cout << rmValue << endl;
                ht.removeElement(rmValue, (ofstream &) output);
                output << endl << "[INFO]After removal " << rmValue << '\n';
                cout << endl << "[INFO]After removal " << rmValue << '\n';
                ht.printAll((ofstream &) output);
                break;
            case 4:
                int lsValue;
                output << "[QUESTION]Which key you want to look?\n";
                cout << "[QUESTION]Which key you want to look?\n";
                std::cin >> lsValue;
                output << lsValue << endl << endl;
                cout << lsValue << endl << endl;
                ht.printSearch(lsValue, output);
                break;
            default:
                return 0;
        }

    }


}
