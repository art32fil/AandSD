#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <fstream>
#include "TreeNode.h"

class Tree{
private:
    std::shared_ptr<TreeNode> read_node(std::string& tree);
    Elem E;
    int elem_count;
    int path;
    std::vector<int> paths;
    std::shared_ptr<TreeNode> root;
public:
    void SetElem(Elem E);
    void read_tree(std::string& tree);
    void search_elem(std::shared_ptr<TreeNode> cur);
    std::shared_ptr<TreeNode> get_root();
    int get_elem_count();
    int get_min_path();
    bool brackets_check(std::string tree);
};

#endif