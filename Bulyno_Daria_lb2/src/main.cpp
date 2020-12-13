#include <iostream>
#include <string>
#define PATERN "0123456789+-*/ "

using namespace std;

class  stack{
private:
    int count;
    int top;
    int *Arr;
    void getSize(){
        count+=50;
        int *tmp = new int[count];
        for (int i = 0; i < top; i++){
            tmp[i] = Arr[i];
        }
        Arr = tmp;
    }
public:
    stack(){
        count = 50;
        top = -1;
        getSize ();
    }
    
    void push( int val ){
        top++;
        if(top >= (count-1)) getSize();    

        Arr[top] = val;
        cout << "PUSH:\t"<< val <<"\n";
    };

    bool isEmpty(){
        return top < 0;
    }
    
    int pop(){
        cout << "POP::\t"<< Arr[top] <<"\n";
        return Arr[top--];
    }
    
    void print(){
        for(int i = 0; i < top; i++){
            cout << "["<<i<<"][  " << Arr[i] << "  ]\n";
        }
    }
    
    ~stack(){
        delete [] Arr;    
    }
};


int chekSymbol(char val){    
    for(int i = 0; i < 14 ; i++){
        if(val == PATERN[i]) return i;
    }
    return -1;
}


void calc(stack* Stack, string str){
    int key, a, b, c;
    for(int i = 0; i < str.length() && str[i] != '\0'; i++){        
        key = chekSymbol(str[i]);
        int tmp = 0;
        if(key > 9 && key < 14){
            b = Stack->pop();
            a = Stack->pop();
            switch(key){
                case 10:
                    c = a+b;
                    cout << a << " + " << b <<" = " << c << endl; 

                   break;
                case 11:
                    c = a-b;
                    cout << a << " - " << b<<" = " << c   << endl; 

                    break;
                case 12:
                    c = a*b;
                    cout << a << " * " << b <<" = " << c  << endl; 
                    break;
                case 13:
                    c = a/b;
                    cout << a << " / " << b <<" = " << c  << endl; 
                    break;           
            }
            Stack->push(c);
        }
        else if(key >= 0 && key <= 9){            
            int tmp = 0;
            while(key >= 0 && key <= 9){
                tmp = tmp*10+key;
                key = chekSymbol(str[++i]);  
            }
            Stack->push(tmp);
            i--;
        }
        else{
            cout << endl;
        }
    }
}

int main(){    
    string str;
    cout << "Введите выражение в постфиксной форме: ";
    getline(cin, str);
    stack *Stack = new stack();
    calc(Stack, str);
    cout << Stack->pop() << endl;
    return 0;
}
