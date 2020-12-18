#include "treap.h"

/*
 * Split function is used to split string objects by delimiter.
 * It is custom, because there're no split function in C++ standard library.
 * A type of return value is void, because the given vector cont stroages the splitted string.
 */
void linesplit(const string& str, vector<string>& cont, char delim){
    stringstream ss(str);
    string token;
    while(getline(ss, token, delim)){
        cont.push_back(token);
    }
}

shared_ptr<Node> Treap::merge(shared_ptr<Node> left, shared_ptr<Node> right){
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

Pair Treap::split(shared_ptr<Node> p, int x){
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

void Treap::insert(int x){
    Pair q = split(data, x);
    shared_ptr<Node> t(new Node(x));
    data = merge(q.first, merge(t, q.second));
    print();
}


void Treap::remove(int key) {
    Pair fst_pair, snd_pair;
    fst_pair = split(data, key-1);
    snd_pair = split(fst_pair.second, key);
    data = merge(fst_pair.first, snd_pair.second);
    dispose(snd_pair.first);
    print();
}


void Treap::dispose(shared_ptr<Node> node) {
    if (node == nullptr)
        return;

    dispose(node->left);
    dispose(node->right);
    node.reset();
}


void Treap::PrintInOrderTraversal(shared_ptr<Node> node, int k){
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


void Treap::print(){
    PrintInOrderTraversal(this->data, 0);
    cout << "\n";
}

void Treap::PrintFileTraversal(shared_ptr<Node> node, int k, std::string& res){
    if (node){
        PrintFileTraversal(node->left, k+1, res);
        for(int i = 0; i < k; i++){
            res += " " ;
        }
        res += "{";
        res += std::to_string(node->key);
        res += ", ";
        res += std::to_string(node->prior);
        res += "}\n";
        PrintFileTraversal(node->right, k+1, res);
    }
    else{
        return;
    }
}


std::string Treap::printFile(){
    //fs.open("conditions.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    std::string res;
    PrintFileTraversal(this->data, 0, res);
    return res;
    //fs << "\n";
    //fs.close();
}


void Treap::visualize(){
    stack<shared_ptr<Node>> st;
    string file_name = "test.txt";

    //cout << "Enter the name of a file-data storager: " << endl;
    //getline(cin, file_name);
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

std::pair<int, int> Treap::read(){
    int count = rand()%16 + 3;
    int ind = rand()%count;
    size = count;
    int key = 0;
    std::pair<int, int> ans = {0 , 0};
    for(int i = 0; i < count; i++){
        key = rand()%(count * (i + 1)) + (i * count);
        this->insert(key);
        if(i == ind){
            ans.first = key;
            ans.second = find(data, key);
        }
    }
    return ans;
}

int Treap::findElem(int x){
    return find(data, x);
}

int Treap::find(shared_ptr<Node> node, int x){
    if(node->key == x){
        return node->prior;
    } else if(node->key >= x){
        return find(node->left, x);
    } else {
        return find(node->right, x);
    }
}

std::string Treap::correctAnswer(){
    std::vector<shared_ptr<Node>> queue;
    std::string ans = "";
    size_t qStart = 0;
    if(data){
        queue.push_back(data);
        ans += std::to_string(data->key);
        shared_ptr<Node> v = nullptr;
        while(qStart < queue.size()){
            v = queue[qStart];
            qStart++;
            if (v->left){
                queue.push_back(v->left);
                ans += std::to_string(v->left->key);
            }
            if (v->right){
                queue.push_back(v->right);
                ans += std::to_string(v->right->key);
            }
        }
    }
    return ans;
}


