#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <fstream>
#include <stack>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

void Split(const string& str, vector<string>& cont, char delim){
    stringstream ss(str);
    string token;
    while(getline(ss, token, delim)){
        cont.push_back(token);
    }
}

class Node{
    public:
        int key;
        int prior;
        int size;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node(int key){
            this->key = key;
            left = right = nullptr;
            this->prior = rand()%100;
            size = 1;
        }
        Node(){}
};

typedef pair<shared_ptr<Node>, shared_ptr<Node>> Pair;

class Treap{
protected:
    shared_ptr<Node> data = nullptr;
public:
    shared_ptr<Node> merge(shared_ptr<Node> left, shared_ptr<Node> right){
        if(!left) return right;
        if(!right) return left;
        if (left->prior > right->prior){
            left->right = merge(left->right, right);
            return left;
        }
        else{
            right->left = merge(left, right->left);
            return right;
        }
    }

    Pair split(shared_ptr<Node> p, int x){
        if(!p)
            return {0,0};
        if (p->key <= x){
            Pair q = split(p->right, x);
            p->right = q.first;
            return {p, q.second};
        }
        else {
            Pair q = split(p->left, x);
            p->left = q.second;
            return {q.first, p};
        }
    }

    void insert(int x){
        Pair q = split(data, x);
        shared_ptr<Node> t(new Node(x));
        data = merge(q.first, merge(t, q.second));
        print();
    }
    
    void remove(int key) {
        Pair fst_pair, snd_pair;
        fst_pair = split(data, key-1);
        snd_pair = split(fst_pair.second, key);
        data = merge(fst_pair.first, snd_pair.second);
        dispose(snd_pair.first);
        print();
    }

    void dispose(shared_ptr<Node> node) {
        if (node == nullptr)
            return;
        
        dispose(node->left);
        dispose(node->right);
        node.reset();
    }

    void PrintInOrderTraversal(shared_ptr<Node> node, int k){
        if (node){
            
            PrintInOrderTraversal(node->left, k+1);
            for(int i = 0; i < k; i++){
                cout << " " ;
            }
            cout << "{" << node->key << ", " << node->prior << "}";
            cout << endl;
            PrintInOrderTraversal(node->right, k+1);
           
        }
        else{
            return;
        }
    }

    void print(){
        PrintInOrderTraversal(this->data, 0);
        cout << "\n";
    }

    void vizualize(){
        stack<shared_ptr<Node>> st;
        string file_name;

        cout << "Enter the name of a file-data storager: " << endl;
        getline(cin, file_name);
        std::fstream fs;
        fs.open(file_name, std::fstream::in | std::fstream::out| std::fstream::trunc);
        if(data){
            st.push(data);
        }
        fs << "digraph Tree{\n";
        int k = 0;
        while(!st.empty()){
            auto node = st.top();
            st.pop();
            if(node->left){
                st.push(node->left);
                fs << "\"" << node->key << ", " << node->prior << "\"";
                fs << " -> " << "\"" << node->left->key << ", " << node->left->prior << "\";\n";
            }else{
                fs << k << " [shape=point];\n";
                fs << "\"" << node->key << ", " << node->prior << "\"";
                fs << " -> "  << k << ";\n";
                k++;
            }
            if(node->right){
                st.push(node->right);
                fs << "\"" << node->key << ", " << node->prior << "\"";
                fs << " -> " << "\"" << node->right->key << ", " << node->right->prior << "\";\n";   
            }else{
                fs << k << " [shape=point];\n";
                fs << "\"" << node->key << ", " << node->prior << "\"";
                fs << " -> " << k << ";\n";
                k++;
            }
            
        }
        fs << "}";
        fs.close();
        string command = "dot -Tpng " + file_name + " -o res.png";
        system(command.c_str());
    }
    
    void read(){
        string file_name;
        cout << "Enter the name of an input file: " << endl;
        getline(cin, file_name);
        ifstream input(file_name);
        if (!input){
            cout << "You haven't entered correct input file." << endl;
        }
        else{
            cout << "Parenthesis analyser: " << endl;
            string line;
            getline(input, line);
            vector<string> line_splitted;
            Split(line, line_splitted, ' ');
            for(std::vector<string>::iterator it = line_splitted.begin() ; it != line_splitted.end(); ++it){
                this->insert(atoi((*it).c_str()));
            }
        }
    }
};
int main(){
    srand(time(NULL));
    Treap tree;    
    tree.read();
    tree.print();
    tree.vizualize();
    //tree.remove(4);
    //tree.vizualize();
    return 0;
}