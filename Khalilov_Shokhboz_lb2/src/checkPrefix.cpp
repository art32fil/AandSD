#include <iostream> 
#include <fstream>
#include <regex>

using namespace std;

#define PATERN_LOG "log\\s?\\(\\s?\\d+\\s?,\\s?\\d+\\s?\\)"
#define PATERN_SQRT "sqrt\\s?\\(\\s?\\d+\\s?\\)"
#define PATERN "0123456789+-*/ ()slqrtabcdefghijkmnopyuvxzw"
#define PLUS "+";
#define MINUS "-";
#define MULTIPLICATION "*";
#define DIVISION "/";


typedef struct BTree
{
    string date;
    BTree *Left; 
    BTree *Right;

} BTree;


int checkSymbol( char & c ){

    int n;
    for( n = 0; c != PATERN[n]; n++);
    return n;
}

bool Sqrt( string &str, string &out_str, int &Index) {

    string tmp = "";
    int i;
    
    for (i = Index; str[i] != ')'; i++){
        
        tmp += str[i];
    }
    tmp += str[i];

    if( regex_match(tmp, regex(PATERN_SQRT))) {

        out_str = tmp;
        Index = i+1;
        return true;
    }
    return false;
}


bool Log( string &str, string &out_str, int &Index) {

    string tmp = "";
    int i;
    for (i = Index; str[i] != ')'; i++){
        
        tmp += str[i];
    }
    tmp += str[i];
    
    if( regex_match(tmp, regex(PATERN_LOG))) {

        out_str = tmp;
        Index = i+1;
        return true;
    }
    return false;
}


void creatForest(string &str, int &index, BTree &Head) {

    int num = 0, c;
    string tmp_str = "";
    c = checkSymbol(str[index]);
    
    if(c == 14) {

        while(c == 14 ) {

            index++;
            c = checkSymbol(str[index]);
        }
    }

    if( c >= 10 && c <= 13 ) {

        index++;
        
        switch (c)
        {
            case 10:
                Head.date = PLUS;  
                break;        
            case 11:
                Head.date = MINUS;  
                break;
            case 12:
                Head.date = MULTIPLICATION;      
                break;
            default:
                Head.date = DIVISION;      
                break;
        }

        Head.Left = new BTree;        
        creatForest ( str, index, *(Head.Left) );

        Head.Right = new BTree;
        creatForest ( str, index, *(Head.Right));
    } 
    else if( c >= 0 && c <= 9 ) {

        for (;;index++) {

            c = checkSymbol(str[index]);
           
            if( c > 9 || c < 0 ) break; 
            
            tmp_str += str[index];
        }
        Head.date = tmp_str;
    }
    else if( c == 15 ) {

        for (;;index++) {

            tmp_str += str[index];

            if( c == 16 ) break; 

            c = checkSymbol(str[index]);    
        }
        Head.date = tmp_str;        
    }       
    else if( c == 17) {

        if( !Sqrt( str, tmp_str, index)) {
        
            Head.date = "";    
            return;
        }
        Head.date = tmp_str;        
    }
    else if( c == 18) {

        if(!Log( str, tmp_str, index)) {

            Head.date = "";    
            return;
        }
        Head.date = tmp_str;        
    }
    else if( c >= 19 && c < 43) {

        Head.date = str[index++];
    }  
}


bool checkPrefix(BTree &head){

    if( head.date == "+" || head.date == "-" || head.date == "*" || head.date == "/" ) 
    {         
        return checkPrefix( *(head.Left)) && checkPrefix( *(head.Right)); 
    }
    else if( head.date.empty())
        return false;
    return true;
}


string ShowTree(BTree &head, ofstream &fout, int n){
    
    for (int i = 0; i < n; i++) {
        
        fout << "   ";
        cout << "   ";
    }
    string out = "";

    if(head.date == "+" || head.date == "-" || head.date == "*" || head.date == "/") 
    {
        
        cout << head.date << "\n";   
        fout << head.date << "\n"; 
        
        out += "(" + ShowTree( *(head.Left), fout, n+1 );
        
        return out + head.date + ShowTree( *(head.Right), fout, n+1)+")";
    }

    cout << head.date << "\n";
    fout << head.date << "\n";
    return head.date;
    
}


int main(int argc, char const *argv[]){

    string str;
    ifstream fin;
    ofstream fout;
    int index;
    char c[240];
    if( argc > 1 ){

        fin.open(argv[1]);
        if( argc > 2 ) {            
            fout.open(argv[2], ios_base::app);
        }
        else {
            fout.open("res.txt", ios_base::app);
        }

        while (!fin.eof())
        {   
            fin.getline(c, 240); 
            str = c;
            index = 0;
            BTree head;

            creatForest( str, index, head);
            
            cout << str << "\n";
            fout << "\n\n[ IN ]: \n" << str;
            if( checkPrefix(head) ){
                cout <<"[ Prefix ] \n";
                fout <<"\t[ Prefix ] \n ";
            }
            else {
                cout <<"[ Not Prefix ] \n";   
                fout <<"\t[ Not Prefix ] \n";   
            }
            fout <<"\n[ Infix out ]: \n" + ShowTree(head, fout, 1);   
            
        }
        fin.close();
        fout.close();
    }
    else {

        fin.getline(c, 240);    
        str = c;
        BTree head;
        index = 0;
        creatForest( str, index, head);
        //  ofstream fout;
        fout.open("result.txt", ios_base::app);

        cout << str << "\n";
        fout << "\n\n[ IN ]: \n" << str;
        if( checkPrefix(head) ){

            cout <<"[ Prefix ] \n";
            fout <<"\t[ Prefix ] \n ";
        }
        else {

            cout <<"[ Not Prefix ] \n";   
            fout <<"\t[ Not Prefix ] \n";   
        }
        fout <<"\n[ Infix out ]: \n" + ShowTree(head, fout, 1); 
        fout.close();
    }   
    return 0;
}