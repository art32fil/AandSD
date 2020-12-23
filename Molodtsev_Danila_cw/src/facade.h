#ifndef FACADE_H
#define FACADE_H
#include "libs.h"
#include "bintree.h"


struct simbol{  //struct for saving simbols and their frequencies
    int n=0;
    std::string c="";
    std::string code="";
};

class Facade{
    std::string task_string="";     //message that was generated
    std::string simbols="";     //array of simbols which has frequency equal 1 and more
    int size=31;    //size of simbols array
    int index=0;	//index for checking decoding
    simbol* arr;    //array of simbols and their frequencies
    BinTree* code_tree_=nullptr;    //Binary Tree
    std::vector<BinTree*> Haffman_tree; //all nodes of Haffman tree
    std::string str_answer="";  //right answer if it is message
    int int_answer=-1;  //right answer if it is integer
public:
    int file_num=1;
    int file_index=0;
    std::fstream file;
    BinTree* GetHaffman_();     //method returns head of the Haffman tree
    std::string coded_str="";
    std::string decoded_str="";
    int GetSize();
    simbol* GetArr();   //method for getting array of simbols and
    BinTree* GetTree(); //method for getting Binary Tree
    std::string GetTaskStr();   //method for getting message
    std::string GetSimbols();   //method for getting simbols array
    Facade(std::string message);
    ~Facade();
    QString BuildFrequencyStr();
    void SetAnwserInt(int a);
    int GetAnswerInt();     //method for remembering answer
    void CountFrequency(std::string message);  //method for counting frequency of every single simbol
    void CreateTreeByFano(BinTree* tree);     //Creating Binary Tree with Fano-Shennon method
    void CreateTreeByHaffman();   //Creating Binary Tree with Haffman method
    void CreateHaffmanNodes();      //Creating array of nodes of Haffman tree
    BinTree* MergeNodes(BinTree* left,BinTree* right);  //merging 2 node to one
    void PrintTree(BinTree* tree);  //Printing Binary Tree
    void MakeHead();     //Method for making string which will be paled to head of Binary Tree
    void Sort();    //This method sorts array of simbols by increasing freauence
    void CodingByFano(); //Coding method
    void Decoding(BinTree* head, BinTree* fict); //Decoding method
    void CodingByHaffman(BinTree* head);
    static bool cmp(BinTree* t1, BinTree* t2);     //comparator for vector sorting
    void BuildTreeFile();       //method builds file for Graphviz
    void BuildNode(BinTree* head);
};

#endif // FACADE_H
