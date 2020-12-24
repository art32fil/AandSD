#include <iostream>
#include <fstream>
#include <string>
#include <list>
#define ESCAPE 257
using namespace std;

class Tree {
public:
	Tree* left;
	Tree* right;
	Tree* parent;
	int code;
    bool symbol_code;
	int weight;
    Tree(Tree* left, Tree* right, Tree* parent, bool symbol_code) {
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->symbol_code = symbol_code;
        this->weight = 0;
        this->code = 255;
    }
};





void PrintTree(Tree* tree, int r, ofstream& fout){
    r++;
    if(tree->right!=nullptr)
        PrintTree(tree->right,r+1, fout);
    for (int i=0;i<(4*r);i++)
        fout << " ";
    if(tree->symbol_code){
        if(tree->code == ESCAPE){
            fout<<tree->weight<<"("<<"0*"<<")"<<endl;
        }
        else{
            fout<<tree->weight<<"("<<(char)tree->code<<")"<<endl;
        }
    }
    else{
        fout<<tree->weight<<endl;
    }
    if(tree->left!=nullptr)
    PrintTree(tree->left,++r, fout);
    --r;
}









///////////////////////////////////////////// Декодирование строки
int InputBits(string& str, int& n,  ofstream& fout) {
    int result = 0;
    char symbol;
    int bit;
    fout << str[n];
    for (int i = n; i < n + 8; i++) {
        fout << str[i];
        symbol = str[i];
        bit = atoi(&symbol);
        result = (result << 1) + bit;
    }
    n += 8;
    return result;
}

void addweight(Tree* tree) {
    tree->weight++;
    if (tree->parent) addweight(tree->parent);
}

void remweight(Tree* tree) {
    tree->weight--;
    if (tree->parent) remweight(tree->parent);
}

void restore(list<Tree*>& sort) {
    Tree* prev = *(--sort.end());
    Tree* current = nullptr;
    for (std::list<Tree*>::iterator i = --sort.end(); true; i--) {
        if (prev->weight > (*i)->weight) current = prev;
        if (current && (current->weight <= (*i)->weight)) {
            Tree test = *current;
            current->left = prev->left;
            if (current->left) current->left->parent = current;
            current->right = prev->right;
            if (current->right) current->right->parent = current;
            current->code = prev->code;
            current->symbol_code = prev->symbol_code;
            prev->left = test.left;
            if (prev->left) prev->left->parent = prev;
            prev->right = test.right;
            if (prev->right) prev->right->parent = prev;
            prev->code = test.code;
            prev->symbol_code = test.symbol_code;
            int diff = current->weight - prev->weight;
            for (int i = 0; i < diff; i++) {
                remweight(current);
                addweight(prev);
            }
            restore(sort);
            break;
        }
        prev = *i;
        if (i == sort.begin()){
            break;
        } 
    }
}

int DecodeSymbol(Tree* tree, string& str, int& n, int& flag_parent, list<Tree*>& sort, ofstream& fout) {

    if (flag_parent) {

        if (n + 8 > str.length()) return 258;
        fout << "symbol = ";
        tree->right = new Tree(nullptr, nullptr, tree, true);
        tree->right->code = InputBits(str, n, fout);
        addweight(tree->right);  
        tree->left = new Tree(nullptr, nullptr, tree, true);
        tree->left->code = ESCAPE;
        flag_parent = 0;
        sort.push_back(tree->right);
        sort.push_back(tree->left);
        fout<<" ("<<char(tree->right->code) << ")"<< endl;
        return tree->right->code;
    }
    Tree* tree_test = tree;
    if (n >= str.length() )
        return 258;
    fout << "symbol = ";
    while (1) {
        if (n >= str.length()) return 258;
        if (str[n] == '1') {
            fout << "1";
            tree_test = tree_test->right;
            if (!tree_test) return 256;
            if (tree_test->symbol_code) {
                n += 1;
                addweight(tree_test);
                //fout << endl;
                fout<<" ("<<char(tree_test->code) << ")"<< endl;
                return tree_test->code;
            }
        }
        else if (str[n] == '0') {
            fout << "0";
            tree_test = tree_test->left;
            if (!tree_test) return 256;
            if (tree_test->symbol_code) {
                if (tree_test->code == ESCAPE) {
                    n += 1;
                    tree_test->right = new Tree(nullptr, nullptr, tree_test, true);
                    tree_test->right->code = InputBits(str, n, fout);
                    addweight(tree_test->right);
                    tree_test->left = new Tree(nullptr, nullptr, tree_test, true);
                    tree_test->left->code = ESCAPE;
                    tree_test->symbol_code = false;
                    sort.push_back(tree_test->right);
                    sort.push_back(tree_test->left);
                    fout<<" ("<<char(tree_test->right->code) << ")"<< endl;
                    return tree_test->right->code;
                }
                else {
                    n += 1;
                    addweight(tree_test);
                    fout<<" ("<<char(tree_test->code) << ")"<< endl;
                    return tree_test->code;
                }
            }
        }
        n += 1;
    }
}

string DecodingFile(string& str, ofstream& fout) {
    Tree tree(nullptr, nullptr, nullptr, false);
    list<Tree*> sort;
    ofstream file_graph;
    sort.push_back(&tree);
    string result = "";
    int symbol;
    int n = 0;
    int f = 1;
    file_graph.open("resultGR.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    while ((symbol = DecodeSymbol(&tree, str, n, f, sort, fout)) != 256 && symbol != 258) {
        result += (char)symbol;
        restore(sort);
        PrintTree(&tree, 0, file_graph);
        file_graph<<"\n------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
    fout << "Result: " << result;
    file_graph.close();
    return result;
}

///////////////////////////////////////////////////////////////////////// Кодирвоание строки
string BinSymbol( int dec){
    int mod;
    std::string str = "";
    int k = 128;
    char sym = (char) dec;
    for (int i = 7; i > -1; i--) {

        str += ((char)((sym & k) >> i) + 48);
        k = k >> 1;
    }
    return str;
}



string CodeSymbol(Tree* tree, string& str, int& n, int& flag_parent, list<Tree*>& sort, ofstream& fout, bool flag_str){
    if (flag_parent) {
        if (n + 1 > str.length()) flag_str = false;
        tree->right = new Tree(nullptr, nullptr, tree, true);
        tree->right->code = (int)str[n];
        n+=1;
        addweight(tree->right);
        tree->left = new Tree(nullptr, nullptr, tree, true);
        tree->left->code = ESCAPE;
        flag_parent = 0;
        sort.push_back(tree->right);
        sort.push_back(tree->left);
        fout<< BinSymbol (tree->right->code);
        fout << " =";
        fout<<" ("<<char(tree->right->code) << ")"<< endl;
        return BinSymbol (tree->right->code);
    }
    std::string code = "";
    Tree* end = nullptr;
    for (std::list<Tree*>::iterator i = sort.begin(); i != sort.end(); i++) {
        if ((char)(*i)->code == str[n]) {
            end = (*i);
            break;
        }
    }
    //// здесь проверка в дереве
    if (end) {
			//if (first) end = end->parent;
            int result = end->code;
            addweight(end);
            Tree* current = end;
            end = end->parent;
			for (end; end; current = end, end = end->parent) {
                if (end->right == current ){
                    code += '1';
                }
				if (end->left == current ){
                    code += '0';
                }
			}
			for (int i = 0; i < code.length() / 2; i++) {
				char reserve = code[i];
				code[i] = code[code.length() - i - 1];
				code[code.length() - i - 1] = reserve;
			}
            n+=1;
			fout <<  code << ' ';
            fout << " =";
            fout<<" ("<<(char)result << ")"<< endl;
            return code;
	}
    /// добавление элемента в дерево
    else{
        	Tree* esc = *(--sort.end());
			esc->right = new Tree(nullptr, nullptr, esc, true);
			esc->right->code =(int) str[n];
            addweight(esc->right);
            int result = esc->right->code;
			esc->left = new Tree(nullptr, nullptr, esc, true);
			esc->left->code = ESCAPE;
            esc->code = 258;
            esc->symbol_code = false;
			sort.push_back(esc->right);
			sort.push_back(esc->left);
            Tree* current;
            esc = esc->parent;
            for (esc; esc; current = esc, esc = esc->parent) {
                if (esc->right == current ){
                    code += '1';
                }
				else {
                    code += '0';
                }
			}
			for (int i = 0; i < code.length() / 2; i++) {

				char reserve = code[i];
				code[i] = code[code.length() - i - 1];
				code[code.length() - i - 1] = reserve;
			}
            code+= BinSymbol(result);
            n+=1;
			fout << code << ' ';
            fout << " =";
            fout<<" ("<<char(result) << ")"<< endl;
            //restore (sort);
            return code;
    }

}


string CodingFile(string& str, ofstream& fout){
    Tree tree(nullptr, nullptr, nullptr, false);
    list<Tree*> sort;
    sort.push_back(&tree);
    ofstream file_graph;
    string result = "";
    string symbol = "";
    int n = 0;
    int f = 1;
    bool flag = true;
    int count = 0;
    file_graph.open("resultGR.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    while (flag){
        result += symbol;
        if (n >= str.length()) break;
        symbol = CodeSymbol(&tree, str, n, f, sort, fout,flag);
        restore(sort);
        PrintTree(&tree, 0, file_graph);
        file_graph<<"\n------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
    fout << "Result: " << result;
    file_graph.close();
    return result;
}

void check_answer(int n, string str1, string str2){
    cout<<n<<") ";
    if (str1 == str2){
        cout<<"Solved correctly!\n";
    }
    else{
        cout<<"Wrong decision!\n";
    }
}

void students_task(){
    cout<<"Task: 1) Encode the message with dynamic Huffman encoding. 2) Decode the message with dynamic Huffman decoding. (The Alphabet ASCII)\n ";
}

int main() {
    cout << "[1] - Enter from file test.txt \n[2] - Complete the program\n";
    char flag;
    cout << "--> ";
    cin >> flag;
    ofstream fout;
    ifstream fin;
    string str1;
    string str2;
    string result1;
    string result2;
    string student_answer1;
    string student_answer2;
    string student_name;
    int variant;
    switch (flag) {
    case '1':
        fin.open("test.txt");
        fout.open("Result.txt", std::fstream::in | std::fstream::out | std::fstream::app);
        cout<<"Enter your first name, last name, and group number. ";
        cin >> student_name;
        cout<<"Enter your option 1-3: ";
        cin>>variant;
        if (variant-1<0 || variant-1>2){
            cout<<" There is no such option!";
            return 0;
        }
        while (!fin.eof()) {
            for(int i = 0; i < variant;i++ ){
                getline(fin, str1);
                getline(fin, str2);
            }
            students_task();
            cout<<"1) "<< str1 <<" Answer to task 1: "; cin >> student_answer1;
            fout<<student_name<<"\nTask 1. "<< "Original data: " << str1 << endl;
            result1 = CodingFile(str1, fout);
            fout<<"\nStudent's response: "<< student_answer1<<"\n-------------------------------------------------------------------------------------------------------------\n";
            cout<<"2) "<< str2 <<" Answer to task 2: "; cin >> student_answer2;
            fout<<"Task 2. "<< "Original data: " << str2 << endl;
            result2 = DecodingFile(str2, fout);
            fout<<"\nStudent's response: "<< student_answer2<<"\n-------------------------------------------------------------------------------------------------------------\n";
            check_answer(1,result1, student_answer1);
            check_answer(2,result2, student_answer2);
            break;
        }
        fin.close();
        fout.close();
        break;
    case '2':
        cout << "Thanks for your attention!";
        break;
    default:
        cout << "\nInvalid data entered!";
        break;
    }
    return 0;
}