#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <fstream>
#include <iostream>
#include <utility>

#include "elements.h"

using namespace std;

#define SCALE 10

template<typename Elem>
class HashTable{
public:
    HashTable(int length, ofstream& out): free_index(0), out(out){
        size = length*11/10 + 3;
        symb_table = new Symbol<Elem> [SCALE*size];
        data = new Symbol<Elem>* [size];
        if(!data || !symb_table){
            cout << "Bad allocation!\n";
            exit(0);
        }
        for(int i = 0; i < size; ++i) data[i] = nullptr;
    }

    ~HashTable(){
        delete [] data;
        delete [] symb_table;
    }

    int hash(Elem elem){
        return elem % size;
    }

    void add(Elem elem){
        if(!data[hash(elem)]){
            if(free_index >= SCALE*size){
                cout << "Overfull table!\n";
                out << "Overfull table!\n";
                return;
            }
            cout << "Element is not present!\n";
            out << "Element is not present!\n";
            symb_table[free_index].key = elem;
            data[hash(elem)] = &(symb_table[free_index++]);
        }
        else{
            Symbol<Elem>* symb = data[hash(elem)];
            if (symb->key == elem){
                cout << "Element is present (x"<<symb->count<<")!\n";
                out << "Element is present (x"<<symb->count<<")!\n";
                ++symb->count; return;
            }
            else{
                while(symb->link){
                    symb = symb->link;
                    if (symb->key == elem){
                        cout << "Element is present (x"<<symb->count<<")!\n";
                        out << "Element is present (x"<<symb->count<<")!\n";
                        ++symb->count; return;
                    }
                }
                if(free_index >= SCALE*size){
                    cout << "Overfull table!\n";
                    out << "Overfull table!\n";
                    return;
                }
                cout << "Element is not present!\n";
                out << "Element is not present!\n";
                symb_table[free_index].key = elem;
                symb->link = &(symb_table[free_index++]);
            }
        }
    }

    void printChains(){
        Symbol<Elem>* symb;
        cout << "Chains in hash table of size " << size << ":\n";
        out << "Chains in hash table of size " << size << ":\n";
        for(int i = 0; i < size; ++i){
            cout << "hash = " << i << ": ";
            out << "hash = " << i << ": ";
            if(!data[i]){
                cout << "none\n";
                out << "none\n";
                continue;
            }
            symb = data[i];
            cout << symb->key << " (x" << symb->count << ")";
            out << symb->key << " (x" << symb->count << ")";
            while(symb->link){
                cout << " -> ";
                out << " -> ";
                symb = symb->link;
                cout << symb->key << " (x" << symb->count << ")";
                out << symb->key << " (x" << symb->count << ")";
            }
            cout << "\n";
            out << "\n";
        }
    }

private:
    Symbol<Elem>** data;
    Symbol<Elem>* symb_table;
    int free_index;
	int size;
    ofstream& out;
};

#endif
