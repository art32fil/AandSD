#include "tree.h"
#include "tree.cpp"
#include <iostream>
#include <fstream>
int COUNT(0);
int COUTN_NULL(0);
template <typename T>
Tree<T>*  START(nullptr);





template <typename T>
unsigned int Tree_Height(Tree<T>* tr){
    unsigned int l, r;
    if(tr != NULL){
        l = (tr->left  != NULL) ? Tree_Height(tr->left)  : 0;
        r = (tr->right != NULL) ? Tree_Height(tr->right) : 0;
        return ((l > r) ? l : r) + 1;
    }
    return 0;
}

template <typename T>
void write(Tree<T>*  head,std::ofstream& myGraph){
    if(head!=nullptr){
         if(head->left!=nullptr){
            myGraph<<'"'<<std::to_string(head->key)<<'"'<<"->"<<'"'<<std::to_string(head->left->key)<<'"'<<std::endl;
            write(head->left,myGraph);
        }
        else{
            myGraph<<'"'<<std::to_string(head->key)<<'"'<<"->"<<'"'<<"N"<<std::to_string(COUTN_NULL++)<<'"'<<std::endl;
        }
        if(head->right!=nullptr){
            myGraph<<'"'<<std::to_string(head->key)<<'"'<<"->"<<'"'<<std::to_string(head->right->key)<<'"'<<std::endl;
            write(head->right,myGraph);
        }
        else{
            myGraph<<'"'<<std::to_string(head->key)<<'"'<<"->"<<'"'<<"N"<<std::to_string(COUTN_NULL++)<<'"'<<std::endl;
        }
    }

}
template <typename T>
void Plot(Tree<T>*  head,std::string* massage){
    ::COUNT++;
    std::string count = std::string(3 - std::to_string(COUNT).length(), '0') + std::to_string(COUNT);
    std::string name = count +std::string(".gv");
    std::ofstream myGraph(name);
    myGraph<<"digraph G"<<"{\n";
    myGraph<<"graph [ordering=\"out\"]\n";
    write(head,myGraph);
    if(massage!=nullptr)
    myGraph<<"label="<<'"'<<*massage<<'"'<<std::endl;
    myGraph<<"}\n";
    myGraph.close();
    COUTN_NULL = 0; 
    std::string command = std::string("dot -Tpng ");
    command+=name;
    command+=std::string(" -o");
    command+=count;
    command+=std::string(".jpg");
    std::cout<<command;
    system(command.c_str());

}






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
    std::string massage = "Поворот вправо: значение "+std::to_string(tree->left->key);
    massage+=std::string(" поднимается вверх\n");
    massage+=std::string("Значение ");
    massage+=std::to_string(tree->key);
    massage+=std::string(" опускается вправо\n");

	Tree<T>* tmp = tree->left; 
	tree->left = tmp->right;

    if(tmp->right!=nullptr){
    massage+=std::string("значение ");
    massage+=std::to_string(tmp->right->key);
    massage+=std::string( " становится левым <<ребенком>> значения ");
    massage+=std::to_string(tree->key);
    }


	tmp->right =  tree; 
    tmp->size = tree->size; 
    if(START<int> == tree){START<int> = tmp;}
    tree = tmp;
	fixsize(tree);
    Plot(START<int>,&massage);
}

template <typename T>
void  rotateleft(Tree<T>*  &tree) 
{


    if(tree==nullptr) return;
    std::string massage = "Поворот влево: значение "+std::to_string(tree->right->key);
    massage+=std::string(" поднимается вверх\n");
    massage+=std::string("Значение ");
    massage+=std::to_string(tree->key);
    massage+=std::string(" опускается влево\n"); 


	Tree <T>* tmp = tree->right;
	tree->right = tmp->left;


      if(tmp->left!=nullptr){
    massage+=std::string("значение ");
    massage+=std::to_string(tmp->left->key);
    massage+=std::string( " становится правым <<ребенком>> значения ");
    massage+=std::to_string(tree->key);
    }




	tmp->left = tree;
	tmp->size = tree->size;
    if(START<int> == tree){START<int> = tmp;}
    tree = tmp;
	fixsize(tree);

    Plot(START<int>,&massage);
}



template <typename T>
void PritTree(Tree<T>* tree, int n, std::ofstream &fout)
{

    if (tree->right != nullptr)
    {
        PritTree(tree->right, n + 1, fout);
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << "\t";
        fout << "    ";
    }

    std::cout << tree->key<<'('<<tree->size<<')'<<"\n";
    fout << tree->key<<'('<<tree->size<<')'<<"\n";
    if (tree->left != nullptr)
    {
        PritTree(tree->left, n + 1, fout);
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
void insertroot(Tree<T>* &tree, T& value,std::string* massage){
    if(tree==nullptr)
    {
        tree = Create<T>(value,nullptr,nullptr);
        *massage+="\nCейчас значение на ходится на своем базовом месте,но так как призошло выпадения вставки в корень, будут "
                  "\nсовершаться повороты обратные спуску,пока новое значение не поднимется до места выпадения вставки в корень";
        Plot(START<int>,massage);
        return;
    }
    if(tree->key>value){
        insertroot(tree->left,value, massage);
        rotateright(tree); 
    }
    else{
        insertroot(tree->right,value,massage);
        rotateleft(tree);
    }
    
}




template <typename T>
void   insert(Tree<T>* &tree, T& value,std::ofstream &fout){
    if(tree==nullptr)
    {
        tree = Create<T>(value,nullptr,nullptr);
        std::string massage = "Шанс выпадения в корень не сработал,произошла базовая вставка значения "+std::to_string(tree->key);
        Plot(START<int>,&massage);
        return;

    }
    srand( time(0) );
    if( rand()%(tree->size+1)==0 ){
    std::string massage ="Проходя вершину  "+ std::to_string(tree->key);
    massage+=std::string(" выпала вставка в корень значения ");
    massage+=std::to_string(value);
    massage+=std::string(". Шанс выпадения был 1:");
     massage+=std::to_string(tree->size+1);
    std::cout<<" Вставка в корень на уровне "<<tree->size<< " значения "<< value<<std::endl;
    fout<<"Вставка в корень на уровне "<<tree->size<< " значения "<< value<<std::endl;
    insertroot(tree,value,&massage);
   // START<int> = tree; 
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
    START<int> = New;
int count = 0;
for(int i = 1;i<n;i++){
        count = contain<int>(New,arr[i]);
        if(!count){
        insert<int >(New,arr[i],fout);

        std::cout<<"Вставтка значения "<<arr[i]<<std::endl;
        fout<<"Вставтка значения "<<arr[i]<<std::endl;

        //Plot(New,nullptr); дублирует
        PritTree(New,0,fout);

        std::cout<<std::endl<<"\n\n\n\n\n";
        fout<<std::endl<<"\n\n\n\n\n";
    }
    else{
        std::cout<<"Элемен:"<<arr[i]<<"уже в дереве"<<std::endl;
        fout<<"Элемен:"<<arr[i]<<"уже в дереве"<<std::endl;
    } 
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
std::string new_massage ="Для сравнения. Максимальная высота "+std::to_string(Tree_Height(New));
Plot(New,&new_massage);

new_massage = std::string("Максимальная высота при базовом построении ");
new_massage+=std::to_string(Tree_Height(New1));
Plot(New1,&new_massage);
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
        system("convert *.jpg  my.pdf");
        system("rm *.gv");
        system("rm *.jpg");
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