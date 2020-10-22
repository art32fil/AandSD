#include <iostream> 
#include <fstream>
#include <cstring>

#define PATERN "0123456789+-* ()slqrtabcdefghijkmnopyuvxzw"

using namespace std;

class BTree
{
public:
    string date;
    BTree *lSub; 
    BTree *rSub;
    bool isleft(){
        if( lSub )
            return true;
        return false;
    }
    bool isRight(){
        if( rSub )
            return true;
        return false;
    }
};


int checkSymbol( char c ){

    int n;
    for( n = 0; c != PATERN[n]; n++);
    return n;
}

string getLeft( string &str, int to)
{
    string out = "";
    int ccc = true;
    for (int i = 0; i < to; i++) 
    {
        if(str[i] == '(' && ccc )
        {
            ccc = false;
            continue;
        }
        out += str[i];
    }
    return out; 
}

string getRight( string &str, int from)
{
    string out = "";
    for (int i = from+1; i < str.length()-1; i++) 
    {
        out += str[i];
    }
    return out; 
}

void toPrefix(string str, BTree &head ){

    int c = -1, i = 0;
    int countC = 0;
    while (i < str.length())
    {
        if(str[i] == '(') countC++;
        if(str[i] == ')') countC--;
        
        if ( 10 <= checkSymbol(str[i]) && checkSymbol(str[i]) < 13 && countC == 1) {
            c  = checkSymbol(str[i]);
            break;
        }
        i++;
    }
    if(c >= 10 && c < 13 ) {

         switch (c)
        {
            case 10:
                head.date = "+";  
                break;        
            case 11:
                head.date = "-";  
                break;
            default:
                head.date = "*";      
                break;
        }
        head.lSub = new BTree;
        string L = getLeft(str, i);
        cout << "tmp L: " + L +"\n";
        toPrefix(L, *(head.lSub)) ;
        
        head.rSub = new BTree;
        string R = getRight(str, i);
        cout << "tmp R: " + R +"\n";
        toPrefix(R, *(head.rSub));
    }
    else
    {
        head.date = str;
    }
}


string ShowTree(BTree &head, ofstream &fout, int n){

    cout << head.date;

    for (int i = 0; i < n; i++) {
        
        fout << "   ";
        cout << "   ";
    }

    if(head.date == "+" || head.date == "-" || head.date == "*" || head.date == "/") 
    {
        string oL ="";
        string oR ="";

        cout << head.date << "\n";   
        fout << head.date << "\n"; 
        
        return head.date 
                + " " 
                + ShowTree( *(head.lSub), fout, n+1 ) 
                + " " 
                + ShowTree( *(head.rSub), fout, n+1 );
    }

    cout << head.date << "\n";
    fout << head.date << "\n";
    return head.date;
    
}

int getResult( BTree &head, bool &ch )
{
    if( head.isRight() || head.isleft()) 
    {
        int left = getResult( *(head.lSub ) , ch), 
            right = getResult( *(head.rSub ), ch);
        
        return head.date == "+"
                ? left + right
                : head.date == "-" 
                    ? left - right 
                    : left * right;
  
    }
    int out = 0, i = 0;
    while ( i < head.date.length())
    {
        int tmp = checkSymbol(head.date[i]);
        if(tmp > 9) ch = false;
        out = out*10 + tmp;
        i++;
    }
    return out;
}

void cleanSpace( string& str ){
    string tmp = "";
    for (int i = 0; i < str.length(); i++)
    {
        if(str[i] == ' ') continue;
        tmp += str[i];
    }
    str = tmp;
}


int main(int argc, char const *argv[]){

    string str;
    ifstream fin;
    ofstream fout;
    
    char c[240];
    if( argc > 1 ){

        fin.open(argv[1]);
        if( argc > 2 ) {            
            fout.open(argv[2], ios_base::app);
        }
        else {
            fout.open("infixToPrefix.txt", ios_base::app);
        }

        while (!fin.eof())
        {   
            fin.getline(c, 240); 
            str = c;
            BTree head;
            cleanSpace(str);
            fout << "\n[::new::]\n" << str << "\n";
            toPrefix( str, head);
            fout << "\n" << ShowTree( head, fout, 1) << "\n";
            
            bool isOnlyNum = true; 
            int result = getResult( head, isOnlyNum );           
            if( isOnlyNum )
                fout <<  result << "\n";
        }
        fin.close();
        fout.close();
    }
    else {

        fin.getline(c, 240);    
        str = c;
        BTree head;
        toPrefix( str, head);

        fout.open("infixToPrefix.txt", ios_base::app);
        cout << str << "\n";
        fout << "\n\n[ IN ]: \n" << str;
        fout <<"\n[ Infix out ]: \n" + ShowTree(head, fout, 1); 
        fout.close();
    }   
    return 0;
}