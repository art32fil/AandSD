#ifndef BINTREENODE_H
#define BINTREENODE_H
#include <memory>

typedef char Elem;

class TreeNode{
public:
    Elem data;
    std::shared_ptr<TreeNode> left {nullptr};
    std::shared_ptr<TreeNode> right {nullptr};
};

#endif