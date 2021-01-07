#ifndef NODETREE_H
#define NODETREE_H

template<typename T> class Tree;

template<typename T> class NodeTree{
    friend class Tree<T>;
    
    T _data;
    NodeTree<T>* _left;
    NodeTree<T>* _right;
    
public:
    NodeTree():_left(nullptr), _right(nullptr){}
    NodeTree(const T &data): _data(data), _left(nullptr), _right(nullptr){}
    
    T getData() const {
        return _data;
    }
    
};

#endif
