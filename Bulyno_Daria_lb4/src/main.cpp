#include <iostream>
using namespace std;

int pow( int a, int b ){
    int c = 1;
    for (int i = 0; i < b; i++){
        c*=a;
    }
    return c;
}


class  stack{
private:
    int count;
    int **Arr;
    void getSize(){
        count++;
        int **tmp = new int*[count];

        for (int i = 0; i < count; i++){
            tmp[i] = new int[10];
            for (int j = 0; j < 10; j++){
                tmp[i][j] = -1;
            }
        }
        for (int i = 0; i < count-1; i++){
            tmp[i] = Arr[i];
        }
        Arr = tmp;
    }
public:
    stack(){
        count = 0;
        getSize();
    }
    void push(int val, int index){        
        if(!count) getSize();
        bool flag = true;
        for (int i = 0; i < count; i++){
            if(!Arr[i][index]){
                Arr[i][index] = val;
                false;
            }
        }
        if(flag){
            getSize();
            Arr[count-1][index] = val;
        }
    };
    int pop(){
        int flag = true;
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < count; j++){
                if(Arr[j][i] != -1){                    
                    int tmp = Arr[j][i];
                    Arr[j][i] = -1;
                    false;
                    return tmp;
                }
            }            
        }
        if (flag){
            for (int i = 0; i < count; i++){
                delete [] Arr[i];
            }
            count = 0;
        }
        return -1;
    }

    void print(){
        for (int i = 0; i < 10; i++){
            cout << "[" << i <<"]: ";
            for (int j = 0; j < count; j++){
                if(Arr[j][i] != -1){                    
                    cout << "[ "<< Arr[j][i] << " ] | ";
                }
            }          
            cout << endl;  
        }
    }
    ~stack(){
         if(count){
            for (int i = 0; i < count; i++){
                delete [] Arr[i];
            }
            count = 0;
        }        
    }
};



int* foo(int *Arr, int count){
    int max = Arr[0];
    for (int i = 0; i < count; i++){
        if( Arr[i] > max) max = Arr[i];
    }

    stack st;
    int Radix = 1, c;

    while (max >= pow(10, Radix-1)){
        c = pow(10, Radix);
        
        for (int i = 0; i < count; i++){
            cout << "Разряд: " << Radix <<"\n"; 
            st.push(Arr[i], (Arr[i]%c-Arr[i]%(c/10) )/pow(10, Radix-1));  
            st.print();
            cout << endl;      
        }
        
        for (int i = 0; i < count; i++){
            cout << "Разряд: " << Radix <<"\n";
            Arr[i] = st.pop();      
            st.print();
            cout << endl;        
        }

        Radix++;
    }
    return Arr;
}

int main(){
	int n;
	cout << "Введите количество элементов массива: n = ";
	cin >> n;
	if (!n){
		cout << "Размер массива не задан" << endl;
		return 0;
	}
    int mass[n];
    cout << "Введите массив: a[n] = ";
    for (int i = 0; i < n; i++){
    	cin >> mass[i];
    }
    int *arr = new int[n];
    for (int i = 0; i < n; i++){
        arr[i] = mass[i];
    }

    arr = foo(arr, n);
	
	cout << "Результат поразрядной сортировки:" << endl;
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;  
    return 0;
}
