#include "../Headers/BinTree.h"

BinTree::BinTree(): left(nullptr), right(nullptr){};

bool BinTree::IsNull(BinTree *tree){
    return tree == nullptr;
}

BinTree *BinTree::Left(BinTree *tree){
    if (tree == nullptr){
        cerr << "Error: Left(nullptr)\n";
        exit(1);
    }
    return tree->left;
}

BinTree *BinTree::Right(BinTree *tree){
    if (tree == nullptr){
        cerr << "Error: Right(nullptr)\n";
        exit(1);
    }
    return tree->right;
}

char BinTree::RootElement(BinTree *tree){
    if (tree == nullptr){
        cerr << "Error: Root(nullptr)\n";
        exit(1);
    }
    return tree->element;
}

void BinTree::MakeElement(BinTree *tree, char element, BinTree *left, BinTree *right){
    tree->element = element;
    tree->left = left;
    tree->right = right;
}

void BinTree::FunctionRead(BinTree *tree, string &line, int from, int to){
    int deep = 0;
    if (from == to){
        if ((operands.find(line[from]) != -1)){
            MakeElement(tree, line[from], nullptr, nullptr);
        } else {
            cerr << "Error: Wrong element - " << line[from] << endl;
            exit(1);
        }
        return;
    }
    for (int i = from; i<=to; i++){
        if (line[i] == '(')
            deep++;
        if (line[i] == ')')
            deep--;
        if ((operators.find(line[i]) != -1) && (deep == 1)){
            if ((line[i-1] == '(') || (line[i+1] == ')')){
                cerr << "Error: Wrong function" << endl;
                exit(1);
            }
            BinTree *p = new BinTree;
            BinTree *q = new BinTree;
            FunctionRead(p, line, from+1, i-1);
            FunctionRead(q, line, i+1, to-1);
            MakeElement(tree, line[i], p, q);
        }
    }
}

void BinTree::ReadTree(BinTree *tree, string &line){
    if (line.length()){
        char element;
        element = line[line.length()-1];
        line.pop_back();
        if (operators.find(element) != -1){
            BinTree *p = new BinTree;
            BinTree *q = new BinTree;
            ReadTree(p, line);
            ReadTree(q, line);
            MakeElement(tree, element, p, q);
        } else {
            if (operands.find(element) != -1){
                tree->element = element;
            } else {
                cerr << "Error: Wrong element - " << element << endl;
                exit(1);
            }
        }
    } else {
        cerr << "Error: Wrong size" << endl;
        exit(1);
    }
}

void BinTree::Destroy(BinTree *tree){
    if (!IsNull(Left(tree))){
        Destroy(tree->left);
    }
    if (!IsNull(Right(tree))){
        Destroy(tree->right);
    }
    delete tree;
}

void BinTree::Display(BinTree *tree, int n){
    if (tree != nullptr){
        for (int i = 0; i < n; i++){
            cout << "  ";
        }
        cout << RootElement(tree) << endl;
        if (!IsNull(Right(tree))){
            Display(Right(tree), n+1);
        }
        if (!IsNull(Left(tree))){
            Display(Left(tree), n+1);
        }
    }
}

void BinTree::PostfixPrint(BinTree *tree){
    if (!IsNull(tree)){
        PostfixPrint(Left(tree));
        PostfixPrint(Right(tree));
        cout << RootElement(tree);
    }
}

void BinTree::FunctionPrint(BinTree *tree, string &res){
    if (Left(tree) && Right(tree)){
        res.push_back('(');
        FunctionPrint(Left(tree), res);
        res.push_back(tree->element);
        FunctionPrint(Right(tree), res);
        res.push_back(')');
    } else {
        res.push_back(tree->element);
    }
}

void BinTree::Diff(BinTree *tree){
    if (!IsNull(tree)){
        Diff(Left(tree));
        Diff(Right(tree));
        if (RootElement(tree) == '-') {
            if ((numbers.find(RootElement(Right(tree))) != -1) && (numbers.find(RootElement(Left(tree))) != -1)){
                int diff, op1, op2;
                op1 = (int)RootElement(Left(tree)) - '0';
                op2 = (int)RootElement(Right(tree)) - '0';
                cout << "Calculating: " << RootElement(Left(tree)) << '-' << RootElement(Right(tree)) << endl;
                if (op1 >= op2){
                    diff = op1-op2;
                    tree->element = diff + '0';
                    delete Left(tree);
                    delete Right(tree);
                    tree->left = nullptr;
                    tree->right = nullptr;
                } else {
                    Left(tree)->element = '0';
                    Right(tree)->element = (op2-op1) + '0';
                }

            }
        }
    }
}
