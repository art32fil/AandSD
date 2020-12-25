#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <stack>


template <class Type>
class Head_AVL_Tree;

template <class Type>
class Node_AVL_Tree {
public:
    friend class Head_AVL_Tree<Type>;

    bool is_contain(Type, int);
    int set_height();
    int set_balance();

    class Node_AVL_Tree<Type>* insert(Type, int& count_o);
    class Node_AVL_Tree<Type>* remove(Type, int& count_o);
    class Node_AVL_Tree<Type>* remove_min(int& count_o);
    class Node_AVL_Tree<Type>* find_min(int& count_o);
    class Node_AVL_Tree<Type>* left_rotate(int& count_o);
    class Node_AVL_Tree<Type>* right_rotate(int& count_o);
    class Node_AVL_Tree<Type>* make_balance(int& count_o);
    class Node_AVL_Tree<Type>* get_r();
    class Node_AVL_Tree<Type>* get_l();
    Type get_d();
    void set_rot(bool);
    bool get_rot();
    int countDeep(Node_AVL_Tree<Type>* node);
    Node_AVL_Tree();
    ~Node_AVL_Tree();

private:

    bool rotate = false;
    int height;
    int balance;
    Type data;
    class Node_AVL_Tree<Type>* left;
    class Node_AVL_Tree<Type>* right;
};


template <class Type>
class Head_AVL_Tree {
public:
    Head_AVL_Tree();
    ~Head_AVL_Tree();
    void insert(Type);
    void print_tree(Node_AVL_Tree<Type>* node, int level);
    bool is_contain(Type);
    void remove(Type);
    Node_AVL_Tree<Type>* get_head();
    int get_o();
    void reset_o();
private:
    int count_o = 0;
    class Node_AVL_Tree<Type>* head;
};



template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::get_r() {
    return right;
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::get_l() {
    return left;
}

template <class Type>
Type Node_AVL_Tree<Type>::get_d() {
    return data;
}


template <class Type>
void Node_AVL_Tree<Type>::set_rot(bool rot) {
    rotate = rot;
}

template <class Type>
bool Node_AVL_Tree<Type>::get_rot() {
    return rotate;
}



template <class Type>
Node_AVL_Tree<Type>::Node_AVL_Tree() {
    left = nullptr;
    right = nullptr;
}

template <class Type>
Node_AVL_Tree<Type>::~Node_AVL_Tree() { // ������� ������ ��� ������
    if (left)
        delete left;
    if (right)
        delete right;
}

template <class Type>
int Node_AVL_Tree<Type>::countDeep(Node_AVL_Tree<Type>* node)
{
    if (node == nullptr)
        return 0;
    int cl = countDeep(node->get_l());
    int cr = countDeep(node->get_r());
    return 1 + ((cl > cr) ? cl : cr);
}

template <class Type>
bool Node_AVL_Tree<Type>::is_contain(Type desired, int depth) { //�������� ���� �� ������� � ������
    if (data == desired)
        return true;
    if (left && data > desired) {
        std::cout << "find in left" << std::endl;
        if (left->is_contain(desired, depth + 1))
            return true;
    }
    if (right && data < desired) {
        std::cout << "find in right" << std::endl;
        return right->is_contain(desired, depth + 1);
    }
    return false;
}



template <class Type>
int countDeep(Node_AVL_Tree<Type>* node)
{
    if (node == nullptr)
        return 0;
    int cl = countDeep(node->get_l());
    int cr = countDeep(node->get_r());
    return 1 + ((cl > cr) ? cl : cr);
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::remove(Type to_remove, int& count_o) {//�������� ��������
    count_o++;
    if (data == to_remove) {
        if (!left && !right) {
            delete this;
            return nullptr;
        }
        if (!right) {
            class Node_AVL_Tree<Type>* temp = left;

            this->left = nullptr;
            delete this;
            return temp;
        }

        class Node_AVL_Tree<Type>* new_root;
        new_root = new Node_AVL_Tree<Type>;
        new_root->left = (right->find_min(count_o)->left);
        new_root->right = (right->find_min(count_o)->right);
        new_root->data = (right->find_min(count_o)->data);
        new_root->balance = (right->find_min(count_o)->balance);

        right = right->remove_min(count_o);
        new_root->left = left;
        new_root->right = right;
        new_root->height = set_height();
        new_root->balance = set_balance();
        return new_root->make_balance(count_o);
    }
    if (data < to_remove) {
        right = right->remove(to_remove, count_o);
    }

    if (data > to_remove) {
        left = left->remove(to_remove, count_o);
    }
    height = set_height();
    balance = set_balance();
    return make_balance(count_o);
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::find_min(int& count_o) {
    //count_o++;
    return left ? left->find_min(count_o) : this;
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::remove_min(int& count_o) {//�������� ������������ ��������
    count_o++;
    if (!left) {
        class Node_AVL_Tree<Type>* temp = right;
        this->right = nullptr;
        delete this;
        return temp;
    }
    left = left->remove_min(count_o);
    count_o++;
    height = set_height();
    balance = set_balance();
    return make_balance(count_o);
}

template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::insert(Type value, int& count_o) { // �������
    count_o++;
    if (value >= data) {
        if (!right) {
            right = new Node_AVL_Tree<Type>; // ������� ������ ���� ��� ������� ��� � ������� ������������� ������
            right->data = value;
            right->height = 1;
        }
        else {
            right = right->insert(value, count_o);
        }
    }
    if (value < data) {
        if (!left) {
            left = new Node_AVL_Tree<Type>;
            left->data = value;
            left->height = 1;
        }
        else {
            left = left->insert(value, count_o);
        }
    }
    height = set_height();
    balance = set_balance();
    return make_balance(count_o); // ������������ �� �������� �� ��������
}


template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::right_rotate(int& count_o) {
    count_o++;
    std::cout << "right rotate around element: " << this->data << std::endl;
    Node_AVL_Tree<Type>* temp;
    temp = left;

    temp->rotate = true;
    if (temp->left != nullptr)
        temp->left->rotate = true;
    if (temp->right != nullptr)
        temp->right->rotate = true;

    left = temp->right;
    this->height = this->set_height();
    this->balance = this->set_balance();
    if (temp->left) {
        temp->left->height = temp->left->set_height();
        temp->left->balance = temp->left->set_balance();
    }
    temp->right = this;
    temp->height = temp->set_height();
    temp->balance = temp->set_balance();
    return temp;
}


template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::left_rotate(int& count_o) {
    count_o++;
    std::cout << "left rotate around element: " << this->data << std::endl;
    Node_AVL_Tree<Type>* temp;
    temp = right;

    temp->rotate = true;
    if (temp->left != nullptr)
        temp->left->rotate = true;
    if (temp->right != nullptr)
        temp->right->rotate = true;

    right = temp->left;
    this->height = this->set_height();
    this->balance = this->set_balance();
    if (temp->right) {
        temp->right->height = temp->right->set_height();
        temp->right->balance = temp->right->set_balance();
    }
    temp->left = this;
    temp->height = temp->set_height();
    temp->balance = temp->set_balance();
    return temp;
}


template <class Type>
class Node_AVL_Tree<Type>* Node_AVL_Tree<Type>::make_balance(int& count_o) {//��������� ������� � ������
    Node_AVL_Tree<Type>* temp;
    temp = this;
    if (balance == 2) {
        if (right->balance == -1) {
            temp->right = right->right_rotate(count_o);
        }
        temp = left_rotate(count_o);
    }
    if (balance == -2) {
        if (left->balance == 1) {
            temp->left = left->left_rotate(count_o);
        }
        temp = right_rotate(count_o);
    }
    return temp;
}

template <class Type>
int Node_AVL_Tree<Type>::set_height() { // ��������� ������
    if (!left && !right)
        return 1;
    if (!left)
        return (right->height + 1);
    if (!right)
        return (left->height + 1);
    if (left->height >= right->height)
        return (1 + left->height);
    if (left->height < right->height)
        return (1 + right->height);
    return 0;
}

template <class Type>
int Node_AVL_Tree<Type>::set_balance() { // ��������� ������� � �������
    if (!left && !right)
        return 0;
    if (!left)
        return right->height;
    if (!right)
        return (left->height * (-1));
    return (right->height - left->height);
}

template <class Type>
Head_AVL_Tree<Type>::Head_AVL_Tree() {
    head = nullptr;
}

template <class Type>
Head_AVL_Tree<Type>::~Head_AVL_Tree() {
    delete head;
}

template <class Type>
Node_AVL_Tree<Type>* Head_AVL_Tree<Type>::get_head() {
    return this->head;
}

template <class Type>
int Head_AVL_Tree<Type>::get_o() {
    return this->count_o;
}

template <class Type>
void Head_AVL_Tree<Type>::reset_o() {
    this->count_o = 0;
}


//------------------ print ------------------//

template <class Type>
void Head_AVL_Tree<Type>::print_tree(Node_AVL_Tree<Type>*  node, int level) {
    if (node)
    {
        print_tree(node->get_r(), level + 1);

        for (int i = 0; i < level; i++) {
            std::cout << "   ";
        }
        std::cout << node->get_d() << std::endl;

        print_tree(node->get_l(), level + 1);
    }
}

//------------------ print ------------------//

template <class Type>
void Head_AVL_Tree<Type>::insert(Type value) {
    if (!head) {
        Node_AVL_Tree<Type>* temp = new Node_AVL_Tree<Type>;
        temp->data = value;
        temp->height = 1;
        head = temp;
        return;
    }
    //  this->count_o++;
    head = head->insert(value, this->count_o);
}

template <class Type>
bool Head_AVL_Tree<Type>::is_contain(Type desired) {
    if (!head)
        return false;
    if (head->data == desired) {
        std::cout << "this element is root" << std::endl;
        return true;
    }
    if (head->left && head->data > desired) {
        std::cout << "find in left " << std::endl;
        return head->left->is_contain(desired, 1);
    }
    if (head->right && head->data < desired) {
        std::cout << "find in right " << std::endl;
        return head->right->is_contain(desired, 1);
    }
    return false;
}

template <class Type>
void Head_AVL_Tree<Type>::remove(Type to_remove) {
    count_o++;
    head = head->remove(to_remove, this->count_o);
}

#endif
