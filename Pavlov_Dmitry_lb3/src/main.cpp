#include <iostream>
#include <fstream>
class Node{
private:
    char data;
    Node* right;
    Node* left;
public:
    Node() {
        data = '#';
        right = nullptr;
        left = nullptr;
    }
    char getData(){
        return data;
    }
    void setData(char x){
        data = x;
    }
    void makeRight(){
        right = new Node;
    }
    void makeLeft(){
        left  = new Node;
    }
    Node* getRight(){
        return right;
    }
    Node* getLeft(){
        return left;
    }
    bool isLeftFree(){
        return left == nullptr;
    }
    bool isRightFree(){
        return right == nullptr;
    }
};

void createForest(Node* a, const std::string info, int& n) {

    if(n >= info.length() || info[n]== '\0'){
        n++;
        return;
    }

    if(info[n]=='/')
    {
        a = new Node;
        n++;
    }else {

        a->setData(info[n]);

        n++;
        a->makeLeft();
        createForest(a->getLeft(), info, n );

        a->makeRight();
        createForest(a->getRight(), info, n );
    }

}

void getLen(const Node* head, const int s, int& result){
    if(head->getData() == '#'){
        return;
    }
    result += s;
    if(!head->isLeftFree()) {
        getLen(head->getLeft(), s+1, result);
    }
    if(!head->isRightFree()){
        getLen(head->getRight(), s+1, result);
    }
}

int getDeep(const Node* head, const int s) {
    int x = 1;
    int r;

    if(head->getData() == '#') {
        return x;
    }

    if(!head->isLeftFree()){
        x = getDeep(head->getLeft(), s+1);
    }


    if(!head->isRightFree()){

       r = getDeep(head->getRight(), s+1);
       if (x < r)
           x = r;
    }
    if (s > x) return s;
    else return x;
}


int main(){
    int n = 0;
    int result = 0;
    std::ifstream fin("./IO/input.txt");
    std::ofstream out("./IO/output.txt");
    Node* head = new Node;
    std::string str;
    fin>>std::noskipws;
    if(!fin){
        std::cout<<"Can't open this file!";
    }
    fin>>str;
    createForest(head, str, n);
    result = getDeep(head, 1);
    out << "Result deep = " << result << '\n';
    int a = 0;
    getLen(head, 0, a);
    out << "Len = "<<a<<'\n';
    return 0;
}
