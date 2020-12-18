#include <iostream>
#include <string>

using namespace std;

template <typename T> 
class Node{
private:
    Node* left;
    Node* right;
    T value;
public:
    Node(){
        right = left = nullptr;   
    }
  
    T getValue(){
        return value;
    }
    
    void setValue(T x){
        value = x;
    }
    
    Node*& Left(){
        return left;
    }
    
    Node*& Right(){
        return right;
    }
    ~Node(){
    	if (left) delete left;
    	if (right) delete right;
    }  
};

template <typename T> 
void LeftRightRoot(Node<T>* elem){    
    if(elem == nullptr) return;
    
    LeftRightRoot(elem->Left());   
    LeftRightRoot(elem->Right());
      
    cout<< elem->getValue()<< "";    
}

template <typename T> 
void Print(Node<T>* elem, int count){
    if(elem == nullptr) return;
    
    Print(elem->Right(), count+1);
    
    for(int i=0; i < count; i++){
        cout<<"    ";
    }
    cout<< elem->getValue()<< "\n";
    
    Print(elem->Left(), count+1);
}

string toLeft(string &str, int to){
    string out = "";
    for (size_t i = 0; i < to; i++){
        out += str[i];
    }
    return out;    
}

string toRight(string &str, int from){
    string out = "";
    for (size_t i = from+1; i < str.length(); i++){
        out += str[i];
    }
    return out;    
}


template <typename T> 
void Creater_LTR(Node<T>* elem, string str){

    if (str == "") return;
    int rootPos = (str.length()/2);

    if (str == "#"){

        elem->setValue(str[rootPos]);        
        return;
    }
    else{
        elem->setValue(str[rootPos]);
        
        elem->Left() = new Node<T>();
        Creater_LTR(elem->Left(), toLeft(str, rootPos));        

        elem->Right() = new Node<T>();
        Creater_LTR(elem->Right(), toRight(str, rootPos));
    }
}

template <typename T> 
void Creater_TLR(Node<T>* elem, string str, int& n){
    if (str[n] == '#' || n >= str.length()){
        elem->setValue(str[n]);
        
        n++;
        return;
    }
    else{
        elem->setValue(str[n]);
        n++;
        
        elem->Left() = new Node<T>();
        Creater_TLR(elem->Left(), str, n);
        
        elem->Right() = new Node<T>();
        Creater_TLR(elem->Right(), str, n);
    }
}

int main(){
	cout << "Выберите порядок перечисления узлов (TLR или LTR): ";
	string type = "";
	cin >> type;
	if (type == "TLR"){
		cout << "Введите перечисление узлов, обозначив за # листья: ";
    	string str = "";
    	cin >> str;
    	int count = 0;
    	Node<char> * head = new Node<char>();
    	Creater_TLR(head, str, count);
    	cout << endl;
    	cout << "Узлы дерева b в порядке КЛП:\n" << str <<"\n\n";
    	cout << "Изображение дерева b:\n";
    	Print(head, 0); 
    	cout << endl;   
    	cout << "Узлы дерева b в порядке ЛПК:\n";
    	LeftRightRoot(head);
    	delete head;
    	cout << endl;
    }else if (type == "LTR"){
    	cout << "Введите перечисление узлов, обозначив за # листья: ";
    	string str = "";
    	cin >> str;
    	int count = 0;
    	Node<char> * head = new Node<char>();
    	Creater_LTR(head, str);
    	cout << endl;
    	cout << "Узлы дерева b в порядке ЛКП:\n" << str <<"\n\n";
    	cout << "Изображение дерева b:\n";
    	Print(head, 0);
    	cout << endl;    
    	cout << "Узлы дерева b в порядке ЛПК:\n";
    	LeftRightRoot(head);
    	delete head;
    	cout << endl;
    }
    else{
    	cout << "Порядок не определён" << endl;
    	return 0;
    }
    return 0;
} 
