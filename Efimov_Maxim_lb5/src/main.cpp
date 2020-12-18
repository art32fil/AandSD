#include "tree.h"
#include "tree.cpp"
#include <iostream>
#include <fstream>
template <typename T>
int getsize(Tree<T>*  tree) 
{
	if( !tree ) return 0; 
	return tree->size; 
}
template <typename T>
void fixsize(Tree<T>*  tree)
{
	tree->size = getsize(tree->left)+getsize(tree->right)+1; 
}

template <typename T>
void  rotateright(Tree<T>*  &tree) 
{
    if(tree==nullptr) return;
    
	Tree<T>* tmp = tree->left; 
	tree->left = tmp->right; 
	tmp->right =  tree; 
    tmp->size = tree->size; 
    tree = tmp;
	fixsize(tree);
}

template <typename T>
void  rotateleft(Tree<T>*  &tree) 
{


    if(tree==nullptr) return;

	Tree <T>* tmp = tree->right;
	tree->right = tmp->left;
	tmp->left = tree;
	tmp->size = tree->size;
    tree = tmp;
	fixsize(tree);
}



template <typename T>
void PritTree(Tree<T>* tree, int n, std::ofstream &fout)
{

    if (tree->left != nullptr)
    {
        PritTree(tree->left, n + 1, fout);
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << "\t";
        fout << "    ";
    }

    std::cout << tree->key<<'('<<tree->size<<')'<<"\n";
    fout << tree->key<<'('<<tree->size<<')'<<"\n";
    if (tree->right != nullptr)
    {
        PritTree(tree->right, n + 1, fout);
    }
}










template <typename T>
void PrintTree(Tree<T>* tree, int r){
    r++;
    if(tree->right!=nullptr)
        PrintTree(tree->right,r+1);
    for (int i=0;i<(4*r);i++)
        std::cout << " ";
    std::cout<<tree->key<<'('<<tree->size<<')'<<std::endl;
    if(tree->left!=nullptr)
    PrintTree(tree->left,++r);
    --r;
}


template <typename T>
Tree <T>*  Create(const T& key,Tree<T>* left, Tree<T>* right)
{
    Tree<T>* result = new Tree <T>();
    result->key=key;
    result->left = left;
    result->right = right;
    return result;
    
}

template <typename T>
void insertroot(Tree<T>* &tree, T& value){
    if(tree==nullptr)
    {
        tree = Create<T>(value,nullptr,nullptr);
        return;
    }
    if(tree->key>value){
        insertroot(tree->left,value);
        rotateright(tree); 
    }
    else{
        insertroot(tree->right,value);
        rotateleft(tree);
    }
    
}




template <typename T>
void   insert(Tree<T>* &tree, T& value,std::ofstream &fout){
    if(tree==nullptr)
    {
        tree = Create<T>(value,nullptr,nullptr);
        return;
    }
    srand( time(0) );
    if( rand()%(tree->size+1)==0 ){
    std::cout<<"Вставка в корень на уровне "<<tree->size<< " значения "<< value<<std::endl;
    fout<<"Вставка в корень на уровне "<<tree->size<< " значения "<< value<<std::endl;
    insertroot(tree,value); 
    return;
    }
    if(tree->key>value){
        insert(tree->left,value,fout);

    }
    else{
        insert(tree->right,value,fout);
    }
    fixsize(tree);
}

template <typename T>
void   simple_insert(Tree<T>* &tree, T& value){
    if(tree==nullptr)
    {
        tree = Create<T>(value,nullptr,nullptr);
        return;
    }
    if(tree->key>value){
        simple_insert(tree->left,value);

    }
    else{
        simple_insert(tree->right,value);
    }
    fixsize(tree);
}



template <typename T>
int contain(Tree<T>* &tree, T& value){
    if(!tree) return 0;
    int count= 0;
    if(tree->key == value) count++;
     if( value < tree->key )
        count+=contain(tree->left,value); 
    else
        count+=contain(tree->right,value); 
    return count;
    
}
void start(int* arr,int n,std::ofstream &fout){
    Tree<int >* New = Create<int >(arr[0],nullptr,nullptr);
int count = 0;
for(int i = 1;i<n;i++){
        count = contain<int>(New,arr[i]);
        if(!count){
        insert<int >(New,arr[i],fout);

        std::cout<<"Вставтка значения "<<arr[i]<<std::endl;
        fout<<"Вставтка значения "<<arr[i]<<std::endl;


        PritTree(New,0,fout);


        std::cout<<std::endl<<"\n\n\n\n\n";
        fout<<std::endl<<"\n\n\n\n\n";
    }
    else{
        std::cout<<"Элемен:"<<arr[i]<<"уже в дереве"<<std::endl;
        fout<<"Элемен:"<<arr[i]<<"уже в дереве"<<std::endl;
    } 
}
    while(1){
    std::cout<<"Хотители ли вы вставить еще вставить значения[y/n]"<<std::endl;
    char c;
    std::cin>>c;
    if(c != 'y')break;
    int x;
    std::cin>>x;


    insert<int >(New,x,fout);

    std::cout<<"Вставтка значения "<<x<<std::endl;
    fout<<"Вставтка значения "<<x<<std::endl;


    PritTree(New,0,fout);


    std::cout<<std::endl<<"\n\n\n\n\n";
    fout<<std::endl<<"\n\n\n\n\n";
    }
      
PritTree(New,0,fout);
std::cout<<std::endl<<"\n\n";
fout<<std::endl<<"\n\n";
Tree<int>* New1 = Create<int>(arr[0],nullptr,nullptr);
    for(int i = 1;i<n;i++){
    count = contain<int>(New1,arr[i]);
    if(!count)
        simple_insert<int>(New1,arr[i]);
    else{
        std::cout<<"Элемен:"<<arr[i]<<"уже в дереве"<<std::endl;
        fout<<"Элемен:"<<arr[i]<<"уже в дереве"<<std::endl;
    }
}

PritTree(New1,0,fout);
}
int main(int argc, char const *argv[]){

    std::ifstream fin;
    std::ofstream fout;
    if( argc > 1 ){

        fin.open(argv[1]);
        if( argc > 2 ) {            
            fout.open(argv[2], std::ios_base::app);
        }
        else {
            fout.open("result.txt");
        }
        int m;
        fin >> m;
        int *arr = new int[m];
        for (int j = 0; j < m; j++)
        {
            fin >> arr[j];
        }
        start(arr,m,fout);
        
        delete[] arr;
        fin.close();
        fout.close();
    }
    else{
        fout.open("result.txt");
        int m;
        std::cin >> m;
        int *arr = new int[m];
        for (int j = 0; j < m; j++)
        {
            std::cin >> arr[j];
        }
        start(arr,m,fout);
        delete[] arr;
        
    }
    return 0;

}