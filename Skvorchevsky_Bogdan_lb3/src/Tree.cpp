#include "Tree.h"
    
void Tree::SetElem(Elem E){
    this->E = E;
    this->path = 0;
    this->elem_count = 0;
}

void Tree::read_tree(std::string& tree){
    this->root = read_node(tree);
}

std::shared_ptr<TreeNode> Tree::read_node(std::string& tree){
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>();
    int i = 0;
    if(tree.length() < 3){
        return nullptr;
    }
    if (tree.length() == 3){
        node->left = nullptr;
        node->right = nullptr;
        do {
            node->data = tree[i];
            i++;
        } while(!isalnum(node->data));
        return node;
    }
    std::stack<Elem> Stack;
    int index = 2;
    int cur_index = index;
    while (cur_index < tree.length()){
        if (tree[cur_index] == '('){
            Stack.push(tree[cur_index]);
         }
        if (tree[cur_index] == ')'){
            if (Stack.empty()){
                break;
            }
            Stack.pop();
        }
        cur_index++;
        if (Stack.empty()){
            cur_index--;
            break;
        }
    }
    std::string left, right;
    left.insert(0, tree, index, cur_index-index+1);
    right.insert(0, tree, cur_index+1, tree.length()-1-cur_index);
    node->left = read_node(left);
    node->right = read_node(right);
    i = 0;
    do {
        node->data = tree[i];
        i++;
    } while(!isalnum(node->data));
    return node;
}

void Tree::search_elem(std::shared_ptr<TreeNode> cur){
    if (cur){
        this->path += 1;
        search_elem(cur->left);
        if (cur->data == this->E){
            this->elem_count++;
            this->paths.push_back(this->path);
        }
        this->path += 1;
        search_elem(cur->right);
    }
	    this->path -= 1;
}

std::shared_ptr<TreeNode> Tree::get_root(){
    return this->root;
}
int Tree::get_elem_count(){
    return this->elem_count;
}
int Tree::get_min_path(){
    int min_path = this->paths.back();
    this->paths.pop_back();
    while(!this->paths.empty()){
        if (min_path > this->paths.back()){
            min_path = this->paths.back();
        }
        this->paths.pop_back();
    }
    return min_path; 
}

bool Tree::brackets_check(std::string tree) {
    int opened = 0;
    int closed = 0;
    for(char i : tree){
        if (i == '(')
            opened += 1;
        if (i == ')')
            closed += 1;
    }
    return opened == closed;
}
