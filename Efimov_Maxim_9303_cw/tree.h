#ifndef TREE
#define TREE



template <typename T>
struct Tree{
    T key;
    int size = 1;
    Tree* left;
    Tree* right;
    Tree<T>(const T& value,Tree<T> lt, Tree<T> rt):key(value),left(lt),right(rt),size(1){}
    Tree <T>(){}
    Tree<T>(const T& Key){
        this->key = Key;
        left = nullptr;
        right = nullptr;
    }

};

#endif