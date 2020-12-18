#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define DValue -1

using namespace std;

template<typename K, typename V>

class HashNode {
public:
    V value;
    K key;

    HashNode(K key, V value){
        this->value = value;
        this->key = key;
    }
};

template<typename K, typename V>

class HashMap {
    HashNode<K,V> **arr;
    int capacity;
    int size;
    HashNode<K,V> *undef;

public:
    HashMap(){
        capacity = 20;
        size = 0;
        arr = new HashNode<K,V>*[capacity];

        for(int i = 0; i < capacity; i++)
            arr[i] = NULL;

        undef = new HashNode<K,V>(-1, DValue);
    }
    int hashCode(K key) {
        return key % capacity;
    }

    void insertNode(K key, V value) {
        auto *temp = new HashNode<K,V>(key, value);

        int hashIndex = hashCode(key);
        int stmp = get(key);
        while(arr[hashIndex] != NULL && stmp != DValue
              && arr[hashIndex]->key != -1) {
            hashIndex++;
            hashIndex %= capacity;
            stmp = get(key);
        }

        if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
            size++;
        arr[hashIndex] = temp;
    }

    V deleteNode(int key) {
        int hashIndex = hashCode(key);

        while(arr[hashIndex] != NULL) {
            if(arr[hashIndex]->key == key) {
                HashNode<K,V> *temp = arr[hashIndex];

                cout << "Deleted node with a key = " << arr[hashIndex]->key << " and value = " << arr[hashIndex]->value << endl;
                arr[hashIndex] = undef;

                size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }

        cout << "The item to delete was not found\n";
        return DValue;
    }

    V get(int key) {
        int hashIndex = hashCode(key);
        int counter = 0;
        vector<V> found_values;

        while(arr[hashIndex] != NULL) {
            if(counter++ > capacity)
                return NULL;
            if(arr[hashIndex]->key == key) {
                found_values.push_back(arr[hashIndex]->value);
            }
            hashIndex++;
            hashIndex %= capacity;
            counter += 1;
        }
        if (found_values.empty()) {
            cout << "Value is not found\n";
            return DValue;
        }
        else{
            cout << found_values.size() << " values found:\n";
            for (V i : found_values)
                cout << "Value is " << i << endl;
            return found_values[0];
        }
    }

    int sizeofMap() {
        cout << "Size is " << size << endl;
        return size;
    }

    bool isEmpty() {
        if (size == 0) {
            cout << "Hash table is empty\n";
            return true;
        }
        else{
            cout << "Hash table is not empty\n";
            return false;
        }
    }

    void display() {
        cout << "Hash table is:\n";
        for(int i = 0 ; i < capacity ; i++) {
            if(arr[i] != NULL && arr[i]->key != -1)
                cout << "key = " << arr[i]->key
                     <<" value = "<< arr[i]->value << endl;
        }
    }
};

vector<std::string> split(std::string text)
{
    std::replace(text.begin(), text.end(), ',', ' ');
    std::istringstream is(text);
    std::string word;
    std::vector<std::string> vs;
    while (is >> word) vs.push_back(word);
    return vs;
}

int main() {

    auto *h = new HashMap<int, int>;

    ifstream in("input.txt");
    string tmp;
    getline(in, tmp);
    vector<std::string> vs = split(tmp);
    for (const string& ss : vs){
        int ind = ss.find(':');
        h->insertNode(atoi(ss.substr(0, ind).c_str()), atoi(ss.substr(ind + 1).c_str()));
    }
    cout << "Menu:\n"
            "1 Get size of table\n"
            "2 Add data\n"
            "3 Delete data by the key\n"
            "4 Check the table for emptiness\n"
            "5 Get data by the key\n"
            "6 Show table\n";

    char c = getchar();
    while (c != 'q') {
        if (c == '1') {
            h->sizeofMap();
            c = NULL;
            fflush(stdin);
        }
        if (c == '2'){
            cout << "Enter the key and value separated by a space\n";
            int a, b;
            cin >> a >> b;
            h->insertNode(a, b);
            c = NULL;
            fflush(stdin);
        }
        if (c == '3'){
            cout << "Enter the key of the value to delete\n";
            int tt;
            cin >> tt;
            h->deleteNode(tt);
            c = NULL;
            fflush(stdin);
        }
        if (c == '4'){
            h->isEmpty();
            c = NULL;
            fflush(stdin);
        }
        if (c == '5'){
            cout << "Enter the key of the value\n";
            int tm;
            cin >> tm;
            h->get(tm);
            c = NULL;
            fflush(stdin);
        }
        if (c == '6'){
            h->display();
            c = NULL;
            fflush(stdin);
        }
        c = NULL;
        fflush(stdin);
        c = getchar();
    }

    return 0;
}
