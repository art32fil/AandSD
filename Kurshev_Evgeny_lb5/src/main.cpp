#include <iostream>
#include <set>

typedef struct Elem{
    int size;
    int x;
    struct Elem* left;
    struct Elem* rigth;
}Elem;

int leo(int x){
    if(x == 1)
        return 1;
    else{
        if(x == 2)
            return 1;
        else
            return leo(x - 2) + leo(x - 1) + 1;
    }
}

Elem* make_new(int x){
    Elem* new_elem = new Elem;
    new_elem->left = nullptr;
    new_elem->rigth = nullptr;
    new_elem->x = x;
    new_elem->size = 1;
    return new_elem;
}

Elem* union_elem(int x, Elem* left, Elem* rigth){
    Elem* new_elem = new Elem;
    new_elem->left = left;
    new_elem->rigth = rigth;
    new_elem->x = x;
    new_elem->size = left->size + rigth->size + 1;
    return new_elem;
}

int make_tree_leo(Elem** p, const int* x, int n, std::set <int>& s){
    int size = 1;
    Elem* new_elem = make_new(x[0]);
    p[0] = new_elem;
    for(int i = 1; i < n; i++){
        if(size == 1){
            size += 1;
            p = (Elem**)realloc(p, size * sizeof(Elem*));
            p[1] = make_new(x[i]);
        }
        else{
            if(s.find(p[size - 1]->size + p[size - 2]->size + 1) != s.end()){
                Elem* tmp = union_elem(x[i], p[size - 2], p[size - 1]);
                size -= 1;
                p[size] = nullptr;
                p = (Elem**)realloc(p, size * sizeof(Elem*));
                p[size - 1] = tmp;
            }
            else{
                size += 1;
                p = (Elem**)realloc(p, size * sizeof(Elem*));
                p[size - 1] = make_new(x[i]);
            }
        }
    }
    return size;
}

bool check(Elem* p){
    if((p->left != nullptr) && (p->rigth != nullptr)){
        if((p->x >= p->left->x) && (p->x >= p->rigth->x)){
            return true * check(p->left) * check(p->rigth);
        }
        else
            return false;
    }
    else
        return true;

}

void print(Elem *t, int u) {
    if (t == nullptr)
        return;
    else {
        print(t->rigth, ++u);
        for (int i = 0; i < u; ++i)
            std::cout << "|";
        std::cout << t->x << '\n';
        u--;
        print(t->left, ++u);
    }
}

void leo_chain(std::set<int>& s, int x){
    int k = 1;
    int max = leo(1);
    while(x >= max){
        s.insert(max);
        k += 1;
        max = leo(k);
    }
}

void print_tree(Elem* tree, int n){
    if(tree != nullptr) {
        printf("Current level = %d\n", n);
        printf("Elem = %d\n\n", tree->x);
        print_tree(tree->left, n + 1);
        print_tree(tree->rigth, n + 1);
    }
}

int main() {
    int size;
    std::cout << "Enter size of sorting array: ";
    std::cin >> size;
    int *arr;
    if (size >= 1) {
        arr = new int[size];
        std::cout << "Enter your array: ";
        for (int i = 0; i < size; i++)
            std::cin >> arr[i];
    }
    else
        std::cout << "Error! Size < 1!!\n";
    std::set <int> chain;
    leo_chain(chain, size);
    Elem** p = new Elem*[1];
    int n = make_tree_leo(p, arr, size, chain);
    for(int i = 0; i < n; i++){
        print(p[i], 0);
        std::cout << "END!\n\n\n";
    }
    int k = 0;
    for(int i = 0; i < n; i++)
        if(check(p[i]))
            k += 1;
    if(k == n)
        std::cout << "LEO!!\n";
    else
        std::cout << "Not LEO((\n";
    return 0;
}