#ifndef COURSEWORK_HASHTABLE_H
#define COURSEWORK_HASHTABLE_H
#include <iostream>
#include <list>


using namespace std;

//Creating a hashtable class
class HashTable{
private:
    list<int> *table;
    int total_elements;

    [[nodiscard]] int getHash(int key) const{
        return key % total_elements;
    }

public:
    //Contructor
    explicit HashTable(int n){
        total_elements = n;
        table = new list<int>[total_elements];
    }
    //Insertion method
    int insertElement(int key){
        int operation_counter = 1;
        unsigned hash = getHash(abs(key));
        list<int>& valueList = table[hash];
        for(auto& elem : valueList){
            if (elem == key){
                elem = key;
                return operation_counter++;
            }
            operation_counter++;
        }
        int newElem = key;
        table[hash].push_back(newElem);
        return operation_counter;
    }
    //Removal method
    void removeElement(int key){
        int x = getHash(key);

        list<int>::iterator i;
        for (i = table[x].begin(); i != table[x].end(); i++) {
            if (*i == key)
                break;
        }


        if (i != table[x].end())
            table[x].erase(i);
        else{
            cout << "[WARNING] Key not found!\n";
        }

    }
    //Method to print all hash table
    void printAll(){
        for(int i = 0; i < total_elements; i++){
            cout << "Index " << i << ": ";
            for(int j : table[i]) {
                cout << j << " => ";
            }

            cout << endl;
        }
    }
    //Method to print list of values by key
    void printSearch(int key){
        for(int i = 0; i < total_elements; i++){
            if (i == key){
                for(int j : table[i]) {
                    cout << j << " => ";
                }
            }

        }
    }
    //Clear hash table values
    void clear(){
        delete [] table;
        table = new list<int>[this->total_elements];
    }
};


#endif //COURSEWORK_HASHTABLE_H
