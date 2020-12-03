#include <iostream>
#include <memory>
#include <algorithm>

class CodesTree;
using namespace std;
typedef shared_ptr<CodesTree> pTree;

class CodesTree  {
    string data;
    int sum;
    pTree left={nullptr};
    pTree right= {nullptr};
    string code;
public:
    string& Get_Code(){
        return this->code;
    }
    void Set_Code(string& str){
        this->code=str;
    }
    string& Get_Data(){
        return this->data;
    }
    CodesTree(string& str){
        this->data=str;
    }
    void SetSum(int s){
        this->sum=s;
    }
    int GetSum(){
        return this->sum;
    }
    void Create_left(string& str) {
        this->left = make_shared<CodesTree>(str);
    }
    void Create_right(string& str){
        this->right = make_shared<CodesTree>(str);
    }
    void Set_Str(string& str){
        this->data=str;
    }
    pTree Get_left(){
        return this->left;
    }
    pTree Get_right(){
        return this->right;
    }
};

struct simbol{
    int n;
    char c;
    string code;
};

static int index=0;

void DecodingProcess(pTree head,pTree fict,string& coded,string& decoded) {
    if (index <= coded.length()) {
        if (fict->Get_Data().length() == 1) {
            decoded += fict->Get_Data();
            DecodingProcess(head,head,coded,decoded);
        }
        if(coded[index]=='0'){
            index++;
            DecodingProcess(head,fict->Get_left(),coded,decoded);
        }else if(coded[index]=='1'){
            index++;
            DecodingProcess(head,fict->Get_right(),coded,decoded);
        }
    }
}

string CodingProcess(simbol* array, string& str){
    string res;
    for(int i=0;i<str.length();i++){
        for(int j=31;j>0;j--){
            if(array[j].c==str[i]){
                res+=array[j].code;
                continue;
            }
        }
    }
    return res;
}

void Sort(simbol* array, int& size){
    int left_index;
    int right_index;
    int left_bord;
    int mid_bord;
    int right_bord;
    for (int i = 1; i < size; i *= 2){
        for (int j = 0; j < size - i; j = j+2*i){
            left_index = 0;
            right_index = 0;
            left_bord = j;
            mid_bord = j + i;
            right_bord = j+2*i;
            if(right_bord >= size){
                right_bord = size;
            }
            simbol* sorted_array = new simbol[right_bord - left_bord];
            while (left_bord + left_index < mid_bord && mid_bord + right_index < right_bord){
                if (array[left_bord + left_index].n < array[mid_bord + right_index].n){
                    sorted_array[left_index + right_index].n = array[left_bord + left_index].n;
                    sorted_array[left_index + right_index].c = array[left_bord + left_index].c;
                    left_index += 1;
                }
                else{
                    sorted_array[left_index+right_index].n=array[mid_bord+right_index].n;
                    sorted_array[left_index+right_index].c=array[mid_bord+right_index].c;
                    right_index += 1;
                }
            }
            while (left_bord + left_index < mid_bord){
                sorted_array[left_index + right_index].n = array[left_bord + left_index].n;
                sorted_array[left_index + right_index].c = array[left_bord + left_index].c;
                left_index += 1;
            }
            while (mid_bord + right_index < right_bord){
                sorted_array[left_index + right_index].n = array[mid_bord + right_index].n;
                sorted_array[left_index + right_index].c = array[mid_bord + right_index].c;
                right_index += 1;
            }
            for (int k = 0; k < left_index + right_index; k++){
                array[left_bord + k].n = sorted_array[k].n;
                array[left_bord + k].c = sorted_array[k].c;
            }
            delete [] sorted_array;
        }
    }
}

void CountFrequency(string& str, simbol* arr){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    for(int i=0;i<str.length();i++){
        int ind=(char)(str[i])-97;
        if(isalpha(str[i])){
            if(arr[ind].n==0){
                arr[ind].c=str[i];
                arr[ind].n++;
            }else{
                arr[ind].n++;
            }
        }
            if(str[i]=='.'){
                arr[26].c=str[i];
                arr[26].n++;
            }
            if(str[i]==','){
                arr[27].c=str[i];
                arr[27].n++;
            }
            if(str[i]=='?'){
                arr[28].c=str[i];
                arr[28].n++;
            }
            if(str[i]=='!'){
                arr[29].c=str[i];
                arr[29].n++;
            }
            if(str[i]==' '){
                arr[30].c=str[i];
                arr[30].n++;
            }
    }
}

void CreateTree(pTree tree,simbol* arr){
    int curr_sum=0;
    int lsum=0;
    string ldata;
    string rdata;
    for(int i=0;i<tree->Get_Data().length();i++){
        for(int j=30;j>=0;j--){
            if(tree->Get_Data()[i]==arr[j].c){
                curr_sum+=arr[j].n;
            }
        }
    }
    tree->SetSum(curr_sum);
    for(int i=0;i<tree->Get_Data().length();i++){
        for(int j=0;j<31;j++){
            if(tree->Get_Data()[i]==arr[j].c){
                if(lsum+arr[j].n<=curr_sum/2){
                    lsum+=arr[j].n;
                    ldata+=arr[j].c;
                }else{
                    rdata+=arr[j].c;
                }
            }
        }
    }
    string lcode=tree->Get_Code()+'0';
    string rcode=tree->Get_Code()+'1';
    if(ldata.length()>1){
        tree->Create_left(ldata);
        tree->Get_left()->Set_Code(lcode);
        CreateTree(tree->Get_left(),arr);
    }else if(ldata.length()==1){
        tree->Create_left(ldata);
        tree->Get_left()->Set_Code(lcode);
        tree->Get_left()->SetSum(lsum);
        for(int j=30;j>=0;j--){
            if(arr[j].c==ldata[0]){
                arr[j].code=lcode;
            }
        }
    }
    if(rdata.length()>1){
        tree->Create_right(rdata);
        tree->Get_right()->Set_Code(rcode);
        CreateTree(tree->Get_right(),arr);
    }else if(rdata.length()==1){
        tree->Create_right(rdata);
        tree->Get_right()->Set_Code(rcode);
        tree->Get_right()->SetSum(curr_sum-lsum);
        for(int j=30;j>=0;j--){
            if(arr[j].c==rdata[0]){
                arr[j].code=rcode;
            }
        }
    }
}

void PrintTree(pTree tree){
    cout<<tree->Get_Data()<<" "<<tree->GetSum()<<" code: "<<tree->Get_Code()<<"\n";
    if(tree->Get_left()){
        PrintTree(tree->Get_left());
    } else{
        cout<<"#\n";
    }
    if(tree->Get_right()){
        PrintTree(tree->Get_right());
    }else{
        cout<<"#\n";
    }
}

string Make_String(simbol* arr){
    string res;
    int ind=30;
    while(ind>=0){
        if(arr[ind].n>0){
            res+=arr[ind].c;
        }else{
            break;
        }
        ind--;
    }
    return res;
}

int main() {
    string path;
    int size=31;
    cout<<"Enter decoded string:\n";
    getline(cin, path,'\n');
    for(int i=0;i<path.length();i++){
        if(isdigit(path[i])){
            cerr<<"Coded string can't have numbers!\n";
            exit(1);
        }
    }
    simbol* arr = new simbol[size];
    CountFrequency(path,arr);
    Sort(arr,size);
    string simbols = Make_String(arr);
    pTree Bin_Tree = make_shared<CodesTree>(simbols);
    CreateTree(Bin_Tree,arr);
    cout<<"All elements of our tree:\n";
    PrintTree(Bin_Tree);
    cout<<"Simbol It's code Frequency\n";
    for(int j=0;j<size;j++){
        if(arr[j].n>0){
            cout<<arr[j].c<<" "<<arr[j].code<<" "<<arr[j].n;
            cout<<"\n";
        }
    }
    string coded_str = CodingProcess(arr,path);
    string decoded_str;
    DecodingProcess(Bin_Tree,Bin_Tree,coded_str,decoded_str);
    cout<<"Coded message:\n"<<coded_str;
    cout<<"\nDecooded message:\n"<<decoded_str;
    delete[] arr;
    //system("pause");
    return 0;
}
