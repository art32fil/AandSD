#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

#define DValue -1

using namespace std;

template<typename K, typename V>
// Класс элемента хеш-таблицы
class HashNode {
public:
    V value;
    K key;

    // Конструктор класса
    HashNode(K key, V value){
        this->value = value;
        this->key = key;
    }
};

template<typename K, typename V>
// Класс хеш-таблицы
class HashMap {
private:
    HashNode<K,V> **arr;
    int capacity;
    int size;
    HashNode<K,V> *undef;

public:
    // Конструктор класса
    HashMap(int cap){
        this->capacity = cap;
        this->size = 0;
        arr = new HashNode<K,V>*[capacity];

        for(int i = 0; i < capacity; i++)
            arr[i] = NULL;

        undef = new HashNode<K,V>(-1, DValue);
    }

    int hashCode(K key) { // Метод для получения хэша элемента таблицы по ключу
        return key % capacity;
    }

    int insertNode(K key, V value) { // Метод вставки элемента в хеш-таблицу
        auto *temp = new HashNode<K,V>(key, value);

        int hashIndex = hashCode(key);
        int counter = 0;

        while(arr[hashIndex] != NULL && arr[hashIndex]->key != -1) {
            hashIndex++;
            hashIndex %= capacity;
            counter++;
        }

        if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1) {
            size++;
            arr[hashIndex] = temp;
        }
        return counter;
    }

    V deleteNode(int key) { // Метод удаления элемента из хеш-таблицы по ключу
        int hashIndex = hashCode(key);

        while(arr[hashIndex] != NULL) {
            if(arr[hashIndex]->key == key) {
                HashNode<K,V> *temp = arr[hashIndex];

                arr[hashIndex] = undef;

                size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }

        return DValue;
    }

    void display() { // Метод для вывода хеш-таблицы
        cout << "Hash table is:\n";
        for (int i = 0; i < capacity; i++) {
            if(arr[i] != NULL && arr[i]->key != -1)
                cout << "key = " << arr[i]->key
                     <<" value = "<< arr[i]->value << endl;
        }
    }

    void resize(int new_capacity) { // Метод для изменения размера хеш-таблицы и её очистки
        this->capacity = new_capacity;
        delete [] arr;
        arr = new HashNode<K,V>*[capacity];
        for(int i = 0; i < capacity; i++)
            arr[i] = NULL;
        size = 0;
    }

    int sizeofMap() { // Метод для вывода размера хеш-таблицы
        cout << "Size is " << size << endl;
        return size;
    }
};