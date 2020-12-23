#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <fstream>
#include <iostream>
#include <utility>

#include "elements.h"
#include "colorout.h"

using namespace std;

#define SCALE 10

template<typename Elem>
class HashTable{
public:

HashTable(int length, ofstream& out): free_index(0), out(out){
        size = length*11/10 + 3;
        symb_table = new Symbol<Elem> [SCALE*size];
        data = new Symbol<Elem>* [size];
        for(int i = 0; i < size; ++i) data[i] = nullptr;
}

~HashTable(){
        delete [] data;
        delete [] symb_table;
}

int hash(Elem elem){
        return abs(elem % size);
}

Symbol<Elem>* find(Elem elem){
        cout << "Now searching for '" << elem << "' in the table.\n";
        out << "Now searching for '" << elem << "' in the table.\n";
        cout << "Hash('" << elem << "') = " << hash(elem) << "\n";
        out << "Hash('" << elem << "') = " << hash(elem) << "\n";
        Symbol<Elem>* symb = data[hash(elem)];
        cout << "Exploring the chain #" << hash(elem) << ":\n" << symb;
        out << "Exploring the chain #" << hash(elem) << ":\n" << symb;
        while(symb){
            cout << "Found " << *symb << "\n";
            out << "Found " << *symb << "\n";
            if(elem == symb->key && !symb->deleted){
                    cout << "Element is present!\n";
                    out << "Element is present!\n";
                    return symb;
            }
            symb = symb->link;
        }
        cout << "The end of the chain has been reached.\n";
        out << "The end of the chain has been reached.\n";
        cout << "Element is not present!\n";
        out << "Element is not present!\n";
        return nullptr;
}

void add(Elem elem){
        if((signed char)(elem) < 0){
            color(FOREGROUND_YELLOW);
            cout << "Warning: unusual symbol detected. " <<
                "It may be a part of a long (UTF-16 or UTF-32) symbol, " <<
                "but it will be treated as a separate character.\n";
            out << "Warning: unusual symbol detected. " <<
                            "It may be a part of a long (UTF-16 or UTF-32) symbol, " <<
                            "but it will be treated as a separate character.\n";
            color(FOREGROUND_WHITE);
        }
        cout << "Adding '" << elem << "'\n";
        out << "Adding '" << elem << "'\n";


        Symbol<Elem>* symb = this->find(elem);
        if(symb){
            cout << "Increasing the 'count' value.\n";
            out << "Increasing the 'count' value.\n";
            ++symb->count;
            return;
        }

        cout << "Adding a new element to the previously examined chain.\n";
        out << "Adding a new element to the previously examined chain.\n";
        symb = data[hash(elem)];
        if(!symb){
            //! overflow?
            if(free_index >= SCALE*size){
                color(FOREGROUND_RED);
                cout << "(!)Error: overflow in vector-based symbol table.\n";
                out << "(!)Error: overflow in vector-based symbol table.\n";
                cout << "Operation terminated.\n";
                out << "Operation terminated.\n";
                color(FOREGROUND_WHITE);
                cout << "Try to create a larger table by passing a longer string.\n";
                out << "Try to create a larger table by passing a longer string.\n";
                cout << "Chain remains unchanged: " << data[hash(elem)];
                out << "Chain remains unchanged: " << data[hash(elem)];
                return;
            }
            symb_table[free_index].key = elem;
            data[hash(elem)] = &(symb_table[free_index++]);
            cout << "Chain after adding:\n" << data[hash(elem)];
            out << "Chain after adding:\n" << data[hash(elem)];
            return;
        }
        while(symb->link && !symb->deleted){
            symb = symb->link;
        }

        if(symb->deleted){
            cout << "Encountered a 'deleted' cell. Inserting the new ";
            cout << "element here instead of adding to the end of the chain.\n";
            out << "Encountered a 'deleted' cell. Inserting the new ";
            out << "element here instead of adding to the end of the chain.\n";
            symb->key = elem;
            symb->count = 1;
            symb->deleted = false;
        }
        else{//! overflow?
            if(free_index >= SCALE*size){
                color(FOREGROUND_RED);
                cout << "(!)Error: overflow in vector-based symbol table.\n";
                cout << "Operation terminated.\n";
                out << "(!)Error: overflow in vector-based symbol table.\n";
                out << "Operation terminated.\n";
                color(FOREGROUND_WHITE);
                cout << "Try to create a larger table by passing a longer string.\n";
                cout << "Chain remains unchanged: " << data[hash(elem)];
                out << "Try to create a larger table by passing a longer string.\n";
                out << "Chain remains unchanged: " << data[hash(elem)];
                return;
            }
            symb_table[free_index].key = elem;
            symb->link = &(symb_table[free_index++]);
        }

        cout << "Chain after adding:\n" << data[hash(elem)];
        out << "Chain after adding:\n" << data[hash(elem)];
}

void remove(Elem elem){
        Symbol<Elem>* symb = this->find(elem);
        if(!symb){
            cout << "Nothing to remove.\n";
            out << "Nothing to remove.\n";
            return;
        }
        cout << "Decreasing 'count' value: " << symb->count << " >> " << symb->count-1;
        out << "Decreasing 'count' value: " << symb->count << " >> " << symb->count-1;
        --symb->count;
        cout << "\n";
        out << "\n";
        if(symb->count == 0){
            cout << "Count == 0 => deleting the element.\n";
            out << "Count == 0 => deleting the element.\n";
            symb->deleted = true;
        }
}

void printChains(){
        cout << "Chains in hash table of size " << size << ":\n\n";
        out << "Chains in hash table of size " << size << ":\n\n";

        for(int i = 0; i < size; ++i){
            cout << "hash = " << i << ": ";
            out << "hash = " << i << ": ";
            cout << data[i];
            out << data[i];
        }

        cout << "\n";
        out << "\n";
}

void printInfo(){
    cout << "\n";
    out << "\n";
    cout << "--------------\n";
    out << "--------------\n";
    printChains();
    cout << "Vector-based symbol table:\n";
    out << "Vector-based symbol table:\n";
    for(int i = 0; i < free_index; ++i){
        cout << "index = " << i << ": " << symb_table[i] << "(x" << symb_table[i].count << ")\n";
        out << "index = " << i << ": " << symb_table[i] << "(x" << symb_table[i].count << ")\n";
    }
    cout << "--------------\n";
    cout << "\n";
    out << "--------------\n";
    out << "\n";
}

private:
    Symbol<Elem>** data;
    Symbol<Elem>* symb_table;
    int free_index;
	int size;
    ofstream& out;
};

#endif
