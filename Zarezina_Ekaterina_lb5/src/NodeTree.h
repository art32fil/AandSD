#ifndef NODETREE_H
#define NODETREE_H

#include <memory>

template<typename T> class Tree;

template<typename T> class NodeTree{
public:    
    friend class Tree<T>;
    
    
    std::shared_ptr<NodeTree> _left;
    std::shared_ptr<NodeTree> _right;
    std::weak_ptr<NodeTree> _parent;
    int _ind;
    
    NodeTree(std::shared_ptr<NodeTree> left, std::shared_ptr<NodeTree> right, const std::shared_ptr<NodeTree>& parent, int ind): _left(std::move(left)),  _right(std::move(right)), _parent(parent),_ind(ind){}
};

#endif
