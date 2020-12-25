#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>

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
        {
            add(keys[i]);
            getImage(string("treap_") + to_string(i) + string(".png"), keys[i], 0);
        }
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
        Treap* right = this->split(key);
        Treap* middle = this->split(key-1);
        delete middle;
        merge(right);
        return;
    }

    void getImage(string imageName, int key, int flagAddRem)
    {
        ofstream output("dotCode.txt");
        if (!output.is_open())
        {
            cout << "Can't open \"dotCode.txt\" data file. Stopping...\n";
            exit(0);
        }
        int i = 0;
        output << "digraph Tree{\n";
        toDotTreapNode(this->root, output, i);

        if(flagAddRem == 0)
            output << "label=\"Added key: " << key << "\";\n";
        else
            output << "label=\"Removed key: " << key << "\";\n";
        output << "labelloc=top;\n";

        output << "}";
        output.close();
        string sysCommand = ".\\graphviz\\dot.exe -Tpng dotCode.txt -o .\\images\\" + imageName;
        system(sysCommand.c_str());
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

    void toDotTreapNode(TreapNode* node, ofstream& output, int& i)
    {
        if(node->left != nullptr)
        {
            output << "\"" << node->key << " (" << node->priority << ")\" -> \"" << node->left->key << " (" << node->left->priority << ")\";\n";
            toDotTreapNode(node->left, output, i);
        }
        else
        {
            output << i << " [shape=point];\n";
            output << "\"" << node->key << " (" << node->priority << ")\" -> " << i << ";\n";
            i++;
        }
        if(node->right != nullptr)
        {
            output << "\"" << node->key << " (" << node->priority << ")\" -> \"" << node->right->key << " (" << node->right->priority << ")\";\n";
            toDotTreapNode(node->right, output, i);
        }
        else
        {
            output << i << " [shape=point];\n";
            output << "\"" << node->key << " (" << node->priority << ")\" -> " << i << ";\n";
            i++;
        }
    }
};

vector<int> readVector()
{
    ifstream infile("data/input.txt");
    vector<int> inputVector;
    if (!infile.is_open())
    {
        cout << "\nCan't open \"input.txt\" file. Continue...\n";
        return inputVector;
    }
    else
        cout << "\n\"input.txt\" file opened successfully.\n";
    
    int input;
    while(infile >> input)
        inputVector.push_back(input);
    infile.close();
    return inputVector;
}

bool isNumber(char c) { return ((c>=48)&&(c<=57)); }

void clearImagesFolder(int i = 0)
{
    string removeImage = string(".\\images\\treap_") + to_string(i) + string(".png");
    if(remove(removeImage.c_str()) == 0)
        clearImagesFolder(++i);
}

int main()
{
    srand(time(NULL));
    system("color 0B");
    cout << "\tWelcome to the Treap Visualizer\n";
    cout << "\tMade by Maximov E. (AandSD coursework)\n\n";
    cout << "Before continue, make sure that application's folder contains graphviz folder, otherwise there will be no output images.\n";
    cout << "You can create data/input.txt file and write numbers for treap into it before start.\n";
    cout << "All images will be saved in \"images\" folder. You can open images before program ends.\n\n";
    cout << "Info: Treap - special data structure. Each node of treap has 2 values: key and priority.\n";
    cout << "Keys organized like binary search tree. Priority organized like heap data structure.\n\n";
    cout << "Repeating numbers will be drawn on image only once.\n";
    cout << "Program chooses priority at random for optimized treap creating. Prority value will be written in brackets.\n\n";
    clearImagesFolder();
    system("pause");

    vector<int> inputVector = readVector();
    Treap treap(inputVector);
    string tempValueString, inputString;
    int imageIndex = inputVector.size();
    while(true)
    {
        cout << "\nPlease, write treap element for add or empty string to continue:\t";
        getline(cin, inputString);
        if(inputString.length() == 0)
            break;
        if(!isNumber(inputString[0]))
            break;
        treap.add(stoi(inputString));
        
        treap.getImage(string("treap_") + to_string(imageIndex) + string(".png"), stoi(inputString), 0);
        imageIndex++;
    }
    while(true)
    {
        cout << "\nPlease, write treap element for delete or empty string to continue:\t";
        getline(cin, inputString);
        if(inputString.length() == 0)
            break;
        if(!isNumber(inputString[0]))
            break;
        treap.remove(stoi(inputString));
        
        treap.getImage(string("treap_") + to_string(imageIndex) + string(".png"), stoi(inputString), 1);
        imageIndex++;
    }
    cout << "\nStep-by-step treap images were saved in \"images\" folder.\n\n";
    remove("dotCode.txt");
    system("pause");
    return 0;
}
