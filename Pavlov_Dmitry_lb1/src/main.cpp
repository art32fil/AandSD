#include <iostream>

struct vector{
    int* arr;
    int size;
};

void transform(vector &v,int start, int len){
    if(len == 1) return; //alpha
    
    if(len == 2 &&(v.arr[start+1] < v.arr[start])){ //swap ba
        int temp = v.arr[start];
        v.arr[start] = v.arr[start+1];
        v.arr[start+1] = temp;
    }

    if(len > 2){                    //Transform(B)Transform(g)
        if(len%2 == 0){             
            transform(v, start, len/2);
            transform(v, start + len/2, len/2);
        }else{
            transform(v, start, len/2+1);
            transform(v, start+len/2, len/2);
        }
    }
}

int main(){
    vector v;
    char str[10];
    std::cout<<"Enter the length of the string: ";
    fgets(str, sizeof(str), stdin);
    while (sscanf(str, "%d", &v.size) != 1) {
        std::cout<<"ERROR!\nTry to input a number:";
        fgets(str, sizeof(str), stdin);
    }
        
        int tempArr[v.size];
        v.arr = tempArr;
        for (int i=0;i<v.size;i++){
            std::cout<<"Number "<<i+1<<": ";
            fgets(str, sizeof(str), stdin);
            while (sscanf(str, "%d", &v.arr[i]) != 1) {
                std::cout<<"ERROR!\nTry to input a number:";
                fgets(str, sizeof(str), stdin);
            }
        }

    transform(v, 0, v.size);
    std::cout<<"Transformed vector: (";
    for (size_t i = 0; i < v.size; i++)
    {
        if(i== v.size -1)
            std::cout<<v.arr[i];
        else
            std::cout<<v.arr[i]<<",";
    }
    std::cout<<")"<<'\n';
    return 0;
}
