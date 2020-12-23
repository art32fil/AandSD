#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int count_iter = 0;

class BinSearchTree{
private:
    struct Node{
        int data;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node(int el): data(el), left(nullptr), right(nullptr) {}
    };
        
    void add(shared_ptr<Node> &node, int el){
        if (!node){
            count_iter++;
            node = make_shared<Node>(el);
            return;
        }
        if (el < node->data){
            count_iter++;
            add(node->left, el);
        }
        else if (el > node->data){
            count_iter++;
            add(node->right, el);
        }
    }

    int findMin(shared_ptr<Node> node){
        auto cur = node;
        while (cur->left){
            cur = cur->left;
        }
        return cur->data;
    }

    int findMax(shared_ptr<Node> node){
        auto cur = node;
        while (cur->right){
            cur = cur->right;
        }
        return cur->data;
    }

    void deleteEl(shared_ptr<Node>& node, int el){
        if (!node){
            cout << "Данного элемента нет в дереве\n";
            return;
        }
        if (el > node->data){
            count_iter++;
            deleteEl(node->right, el);
        }
        else if (el < node->data){
            count_iter++;
            deleteEl(node->left, el);
        }
        else{
            count_iter++;
            if (node->right){
                int tmp = findMin(node->right);
                deleteEl(node->right, tmp);
                node->data = tmp;
            }
            else if (node->left){
                int tmp = findMax(node->left);
                deleteEl(node->left, tmp);
                node->data = tmp;
            }
            else{
                node = nullptr;
            }
        }
    }

    void print(shared_ptr<Node> node, int color, int level){
        if (node){
            print(node->right, 2, level+5);
            for (int i = 0; i<level; i++){
                cout << "\033[0;0m ";
            }
            if (color == 1)
                cout << "\033[1;34m" << node->data << "\033[0;0m" << '\n';
            else if (color == 2)
                cout << "\033[1;31m" << node->data << "\033[0;0m" << '\n';
            else
                cout << "\033[1;32m" << node->data << "\033[0;0m" << '\n';
            print(node->left, 3, level+5);
        }
    }

    shared_ptr<Node> head;
public:
    BinSearchTree(): head(nullptr) {};
    ~BinSearchTree() = default;

    void addElem(int el){
        add(head, el);
    }

    void deleteElem(int el){
        deleteEl(head, el);
    }

    bool isEmpty(){
        if (head)
            return false;
        else
            return true;
    }

    void printTree(){
        if (head)
            print(head, 1, 0);
        else
            cout << "В дереве нет элементов";
    }

};

vector<int> generate(int n){
    int val;
    vector<int> vec;
    for (int i = 0; i<n; i++){
        val = rand()%11000;
        vec.push_back(val);
    }
    return vec;
}

vector<int> generateWorst(int n){
    int val;
    vector<int> vec;
    for (int i = 0; i<n; i++){
        val = rand()%11000;
        vec.push_back(val);
    }
    sort(vec.begin(), vec.end());
    return vec;
}

int main(){
    srand(time(0));
    string name;
    int mode;
    cout << "Выберите способ создания дерева:\n1 - Считать из файла\n2 - Сгенерировать случайное дерево\n";
    cin >> mode;
    switch(mode){
        case 1:{
            cout << "Введите название файла: ";
            cin >> name;
            ifstream fin(name);
            BinSearchTree* bst = new BinSearchTree();
            vector<int> vec;
            int elem, m;
            int start, end;
            char opt = 'y';
            cout << "Исходная последовательность элементов: ";
            while(!fin.eof()){
                fin >> elem;
                cout << elem << " ";
                bst->addElem(elem);
                vec.push_back(elem);
            }
            cout << '\n';
            bst->printTree();

            count_iter = 0;
            cout << "1 - Добавить случайный элемент\n2 - Удалить случайный элемент\n";
            cin >> m;
            if (m == 1){
                int tmp = rand()%12500;
                cout << "Добавление элемента " << tmp << '\n';
                start = clock();
                bst->addElem(tmp);
                end = clock();
                bst->printTree();
                cout << "Время, затраченное на добавление - " << fixed << (double)(end-start)/CLOCKS_PER_SEC << " s\n";
                cout << "Количество итераций - " << count_iter << '\n';
            }
            else{
                int tmp = vec[rand()%vec.size()];
                cout << "Удаление элемента " << tmp << '\n';
                start = clock();
                bst->deleteElem(tmp);
                end = clock();
                bst->printTree();
                cout << "Время, затраченное на удаление - " << fixed << (double)(end-start)/CLOCKS_PER_SEC << " s\n";
                cout << "Количество итераций - " << count_iter << '\n';
            }
            delete bst;
            break;
        }
        case 2:{
            int n;
            int m;
            int start, end;
            vector<int> vec;
            BinSearchTree* bst = new BinSearchTree();
            cout << "    1 - Генерация в \"среднем\" случае\n    2 - Генерация в \"худшем\" случае\n";
            cin >> m;
            cout << "Введите размер последовательности: ";
            cin >> n;

            if (m == 1)
                vec = generate(n);
            else
                vec = generateWorst(n);
            
            cout << "Исходная последовательность: ";
            for (int i = 0; i<n; i++){
                bst->addElem(vec[i]);
                cout << vec[i] << " ";
            }
            cout << '\n';

            bst->printTree();
            count_iter = 0;
            cout << "1 - Добавить случайный элемент\n2 - Удалить случайный элемент\n";
            cin >> m;
            if (m == 1){
                int tmp = rand()%11500;
                cout << "Добавление элемента " << tmp << '\n';
                start = clock();
                bst->addElem(tmp);
                end = clock();
                bst->printTree();
                cout << "Время, затраченное на добавление - " << fixed << (double)(end-start)/CLOCKS_PER_SEC << " s\n";
                cout << "Количество итераций - " << count_iter << '\n';
            }
            else{
                int tmp = vec[rand()%n];
                cout << "Удаление элемента " << tmp << '\n';
                start = clock();
                bst->deleteElem(tmp);
                end = clock();
                bst->printTree();
                cout << "Время, затраченное на удаление - " << fixed << (double)(end-start)/CLOCKS_PER_SEC << " s\n";
                cout << "Количество итераций - " << count_iter << '\n';
            }

            delete bst;
            break;
        }
        default:
            break;
    }
    return 0;
}