#include <iostream>
#include <fstream>
#include <variant>

class Node {
    using NodePtr = std::shared_ptr<Node>;

public:
    NodePtr next{ nullptr };
    std::variant<char, NodePtr> value;
    Node() = default;
    ~Node() = default;
};

std::shared_ptr<Node> foundPostfix(std::string& string, int& iter){
    using NodePtr = std::shared_ptr<Node>;
    int counter = 0;
    short int arg = 3;
    NodePtr headLocal = std::make_shared<Node>();
    NodePtr curLocal = headLocal;
    headLocal->value = string[iter];
    while ((iter != string.length()) && (counter < arg)) {
        iter++;
            if (!string.compare(iter, 1, "(")) {
                curLocal->next = std::make_shared<Node>();
                curLocal = curLocal->next;
                curLocal->value = foundPostfix(string, iter);
                counter++;
            } else {
                if(((string[iter]>='a' && string[iter]<= 'z') || (string[iter]>='0' && string[iter]<='9')) && counter != 2){
                    if(counter == 1 && string[iter] == '0' && string[iter+1] == '/'){
                        return headLocal;
                    } else {
                        curLocal->next = std::make_shared<Node>();
                        curLocal = curLocal->next;
                        curLocal->value = string[iter];
                        counter++;
                    }
                }else if(counter == 2 && (string[iter] == '+' || string[iter] == '-' || string[iter] == '*' || string[iter] == '/')){
                    curLocal->next = std::make_shared<Node>();
                    curLocal = curLocal->next;
                    curLocal->value = string[iter];
                    counter++;
                }else {
                    return headLocal;
                }
            }

    }
    if (string[iter] != ')' && (string[iter-1] != '+' && string[iter-1] != '-' && string[iter-1] != '*' && string[iter-1] != '/'))
        iter++;
    return headLocal;
}
int main(){
    std::shared_ptr<Node> head;
    int iter = 0;
    std::ifstream fin("./Tests/input.txt");
    std::string str;
    fin>>std::noskipws;
    if(!fin){
        std::cout<<"Can't open this file!"<<'\n';
        return 1;
    }
    fin>>str;
    //std::cout<<str.length()-1<<'\n';
    head = foundPostfix(str, iter);
    //std::cout<<iter<<'\n';
    if (iter == str.length() - 1)
        std::cout << "Success: Correct syntax!\n";
    else
        std::cout << "Error: Incorrect syntax!\n";
    return 0;
}

