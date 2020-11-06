#include <iostream>
#include <string>
#include <fstream>
void inputText(std::string text)
{
    std::string path = "result.txt";
    std::string test;
    std::ofstream fin;
    fin.open(path, std::ios_base::app);
    int depth;
    if( !fin.is_open() )
    {
        std::cout<<"Ошибка открытия файла";
    } 
    else
    {
        fin << text<<std::endl;
    }
    fin.close();
} 
class Tree
{
private:
    Tree* right;
    Tree* left;
    char data;
public:
    Tree() {
        data = '#';
        right = left = nullptr;   
    }
    char getData()
    {
        return data;
    }
    void satData(char x)
    {
        data = x;
    }
    void makeRight()
    {
        right = new Tree;
    }
    void makeLeft()
    {
        left  = new Tree;
    }
    Tree* getRight()
    {
        return right;
    }
    Tree* getLeft()
    {
        return left;
    }
    bool isLeftFree()
    {
        return left == nullptr;
    }
    bool isRightFree()
    {
        return right == nullptr;
    }  
};

void createForest(Tree* a, std::string info, int& n) {

    if( n >= (int)info.length() || info[n]== '\0')
    {
        n++;
        return;
    }

    if(info[n]=='/')
    {
        a = new Tree;
        n++;
    }else {

        a->satData(info[n]);

        n++;
        a->makeLeft();
        createForest(a->getLeft(), info, n );

        a->makeRight();
        createForest(a->getRight(), info, n );  
    } 

}
void printTree(Tree* treePtr, int p)
{
    int i;
        if(treePtr != nullptr)
    {
        printTree(treePtr->getLeft(),p+3);
        for(i=0;i<p;i++)
        {
            printf(" ");
        }
        printf("%3c\n", treePtr->getData());
        printTree(treePtr->getRight(), p+3);
    }
}
void printSheet(Tree* head)
{
    if(!head->isRightFree() && !head->isLeftFree())
        if ( head->getLeft()->getData()=='#' && head->getRight()->getData()=='#')
        {
            std::string sheet = "Листья:";
            std::cout<< sheet << head->getData() << std::endl;
            sheet =+ head->getData();
            inputText(sheet);
            return; 
        }  
    if(!head->isRightFree())
        printSheet(head->getLeft());
    if(!head->isLeftFree())
        printSheet(head->getRight());  
}
void numberNodes(Tree* head,int number,int current,int& sum)
{
    if( head->getData()=='#' ) return;

    if(current == number)
    {

        sum++;
        std::cout<<"Атом "<< head->getData() <<" Сумма ="<<sum<<std::endl;
        std::string  atom = "Атом ";
        atom+=head->getData();
        atom+=" Сумма =" + std::to_string(sum);
        inputText(atom);
    }
    if(!head->isRightFree())
        numberNodes(head->getLeft(),number,current+1,sum);
    if(!head->isLeftFree())
        numberNodes(head->getRight(),number,current+1,sum);
}
int main()
{
    std::string path = "test.txt";
    std::string test;
    std::ifstream fin;
    fin.open(path);
    int depth;
    if( !fin.is_open() )
    {
        std::cout<<"Ошибка открытия файла";
    } 
    else
    {
        fin >> test;
        fin >> depth;
    }
    Tree* head = new Tree;
    int n = 0;
    createForest(head, test, n);
    printTree(head, 1);
    printSheet(head);
    int sum = 0;
    numberNodes(head, depth, 1, sum);
    inputText("Сумма узлов: " + std::to_string(sum));
    return 0;
}



