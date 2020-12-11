#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

class Treap;
class TreapNode;
typedef pair<TreapNode*, TreapNode*> Pair;          // Pair(this, another)
bool isNumber(char c);
vector<int> readVector();

class TreapNode
{
public:
    int key, priority, count;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int key)
    {
        this->key = key;
        this->priority = rand();
        left = nullptr;
        right = nullptr;
        count = 1;
    }

    ~TreapNode(){}
};

class Treap
{
public:
    TreapNode* root = nullptr;

    Treap(TreapNode* root = nullptr) { this->root = root; }
    Treap(vector<int> keys)
    {
        for (int i=0; i < keys.size(); i++)
            add(keys[i]);
    }

    ~Treap() { destruct(root); }
    void print() { printNode(this->root); }

    TreapNode* find(int key, TreapNode* root)
    {
        if (root == nullptr)
            return nullptr;
        else if (key < root->key)
            return find(key, root->left);
        else if (key > root->key)
            return find(key, root->right);
        else
            return root;
    }

    void add(int key)
    {
        TreapNode* findNode = this->find(key, this->root);
        if (findNode != nullptr)
        {
            findNode->count++;
            return;
        }
        Treap* another = this->split(key);
        Treap* aloneNode = new Treap((new TreapNode(key)));
        this->merge(aloneNode);
        this->merge(another);
        return;
    }

    void remove(int key)
    {
        TreapNode* findNode = this->find(key, this->root);
        if (findNode == nullptr)
            return;
        Treap* left = this->split(key-1);
        Treap* middle = this->split(key+1);
        delete middle;
        merge(left);
        return;
    }

private:
    void destruct(TreapNode* node)
    {
        if (node == nullptr)
            return;
        if (node->left != nullptr)
            destruct(node->left);
        if (node->right != nullptr)
            destruct(node->right);
        delete node;
        return;
    }

    void merge(Treap* another)
    {
        this->root = mergeTreapNodes(this->root, another->root);
        another->root = nullptr;
        delete another;
        return;
    }

    Treap* split(int delimiter)
    {
        Pair splitResult = splitTreapNode((this->root), delimiter);
        this->root = splitResult.first;
        Treap* out = new Treap(splitResult.second);
        return out;
    }

    Pair splitTreapNode(TreapNode* node, int delimiter)
    {
        if (node == nullptr)
            return {nullptr, nullptr};

        if (node->key <= delimiter)
        {
            Pair temp = splitTreapNode(node->right, delimiter);
            node->right = temp.first;               // Первый, слева
            return {node, temp.second};
        }   
        else // Тогда node->key > delimiter
        {
            Pair temp = splitTreapNode(node->left, delimiter);
            node->left = temp.second;               // Второй, справа
            return {temp.first, node};
        }
    }

    TreapNode* mergeTreapNodes(TreapNode* L, TreapNode* R)
    {
        if (L == nullptr)
            return R;
        if (R == nullptr)
            return L;
        if (L->priority > R->priority)
        {
            L->right = mergeTreapNodes(L->right, R);
            return L;
        }
        else    // Тогда L->priority <= R->priority
        {
            R->left = mergeTreapNodes(L, R->left);
            return R;
        }
    }

    void printNode(TreapNode* node, int flag = 1)
    {
        if (node == nullptr)
            return;
        if(flag)
            cout << "\t\t";
        cout << node->key << "\t" << node->priority << "\t\t" << node->count << "\n";
        if (node->left != nullptr)
        {
            cout << node->key << ":\tleft\t";
            printNode(node->left, 0);
        }
        if (node->right != nullptr)
        {
            cout << node->key << ":\tright\t";
            printNode(node->right, 0);
        }
    }
};

vector<int> readVector()
{
    ifstream infile("input.txt");
    if (!infile.is_open())
    {
        cout << "Can't load \"input.txt\" data file. Stopping...\n";
        exit(1);
    }
    vector<int> inputVector;
    int input;
    while(infile >> input)
        inputVector.push_back(input);
    infile.close();
    return inputVector;
}

bool isNumber(char c) { return ((c>=48)&&(c<=57)); }

int main()
{
    srand(time(NULL));
    Treap treap(readVector());
    string tempValueString;
    string inputString;
    while(true)
    {
        cout << "\nInput data loaded successfully.\n";
        cout << "Please, write new treap element or empty string for print:\t";
        getline(cin, inputString);
        if(inputString.length() == 0)
            break;
        if(!isNumber(inputString[0]))
            break;
        treap.add(stoi(inputString));
    }
    cout << "\nroot\tdir\tkey\tpriority\tcount\n";
    cout << "=============================================\n";
    treap.print();
    cout << endl;
    system("pause");
    return 0;
}
