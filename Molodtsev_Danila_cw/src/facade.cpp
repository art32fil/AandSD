#include "facade.h"

Facade::Facade(std::string message){
    this->task_string=message;
}

Facade::~Facade(){
    if(code_tree_!=nullptr){
        delete code_tree_;
    }
    if(arr!=nullptr){
        delete [] arr;
    }
}

void Facade::CountFrequency(std::string message){
    transform(message.begin(), message.end(), message.begin(), ::tolower);
    arr = new simbol[size];
        for(int i=0;i<message.length();i++){
            int ind=(char)(message[i])-97;
            if(isalpha(message[i])){
                if(arr[ind].n==0){
                    arr[ind].c=message[i];
                    arr[ind].n++;
                }else{
                    arr[ind].n++;
                }
            }
                if(message[i]=='.'){
                    arr[26].c=message[i];
                    arr[26].n++;
                }
                if(message[i]==','){
                    arr[27].c=message[i];
                    arr[27].n++;
                }
                if(message[i]=='?'){
                    arr[28].c=message[i];
                    arr[28].n++;
                }
                if(message[i]=='!'){
                    arr[29].c=message[i];
                    arr[29].n++;
                }
                if(message[i]==' '){
                    arr[30].c=message[i];
                    arr[30].n++;
                }
        }
}

void Facade::CreateTreeByFano(BinTree* tree){
    int curr_sum=0;
        int lsum=0;
        std::string ldata="";
        std::string rdata="";
        for(int i=0;i<(int)(tree->Get_Data().length());i++){
            for(int j=30;j>=0;j--){
                if(tree->Get_Data()[i]==arr[j].c[0]){
                    curr_sum+=arr[j].n;
                }
            }
        }
        tree->SetSum(curr_sum);
        for(int i=0;i<tree->Get_Data().length();i++){
            for(int j=0;j<31;j++){
                if(tree->Get_Data()[i]==(arr[j].c[0])){
                    if(lsum+arr[j].n<=curr_sum/2){
                        lsum+=arr[j].n;
                        ldata+=arr[j].c;
                    }else{
                        rdata+=arr[j].c;
                    }
                }
            }
        }
        std::string lcode=tree->Get_Code()+'0';
        std::string rcode=tree->Get_Code()+'1';
        if(ldata.length()>1){
            tree->Create_left(ldata);
            tree->Get_left()->Set_Code(lcode);
            CreateTreeByFano(tree->Get_left());
        }else if(ldata.length()==1){
            tree->Create_left(ldata);
            tree->Get_left()->Set_Code(lcode);
            tree->Get_left()->SetSum(lsum);
            for(int j=30;j>=0;j--){
                if(arr[j].c[0]==ldata[0]){
                    arr[j].code=lcode;
                }
            }
        }
        if(rdata.length()>1){
            tree->Create_right(rdata);
            tree->Get_right()->Set_Code(rcode);
            CreateTreeByFano(tree->Get_right());
        }else if(rdata.length()==1){
            tree->Create_right(rdata);
            tree->Get_right()->Set_Code(rcode);
            tree->Get_right()->SetSum(curr_sum-lsum);
            for(int j=30;j>=0;j--){
                if(arr[j].c[0]==rdata[0]){
                    arr[j].code=rcode;
                }
            }
        }
}

void Facade::PrintTree(BinTree* tree){
    std::cout<<tree->Get_Data()<<" "<<tree->GetSum()<<" code: "<<tree->Get_Code()<<"\n";
    if(tree->Get_left()){
        PrintTree(tree->Get_left());
    } else{
        std::cout<<"#\n";
    }
    if(tree->Get_right()){
        PrintTree(tree->Get_right());
    }else{
        std::cout<<"#\n";
    }
}

void Facade::Sort(){
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
                    if (arr[left_bord + left_index].n < arr[mid_bord + right_index].n){
                        sorted_array[left_index + right_index].n = arr[left_bord + left_index].n;
                        sorted_array[left_index + right_index].c = arr[left_bord + left_index].c;
                        left_index += 1;
                    }
                    else{
                        sorted_array[left_index+right_index].n=arr[mid_bord+right_index].n;
                        sorted_array[left_index+right_index].c=arr[mid_bord+right_index].c;
                        right_index += 1;
                    }
                }
                while (left_bord + left_index < mid_bord){
                    sorted_array[left_index + right_index].n = arr[left_bord + left_index].n;
                    sorted_array[left_index + right_index].c = arr[left_bord + left_index].c;
                    left_index += 1;
                }
                while (mid_bord + right_index < right_bord){
                    sorted_array[left_index + right_index].n = arr[mid_bord + right_index].n;
                    sorted_array[left_index + right_index].c = arr[mid_bord + right_index].c;
                    right_index += 1;
                }
                for (int k = 0; k < left_index + right_index; k++){
                    arr[left_bord + k].n = sorted_array[k].n;
                    arr[left_bord + k].c = sorted_array[k].c;
                }
                delete [] sorted_array;
            }
        }
}

void Facade::MakeHead(){
    simbols="";
    int ind=30;
    while(ind>=0){
        if(arr[ind].n>0){
              simbols+=arr[ind].c[0];
            }else{
                break;
            }
            ind--;
        }
    code_tree_= new BinTree(simbols);
}

void Facade::CodingByFano(){
        for(int i=0;i<task_string.length();i++){
            for(int j=30;j>=0;j--){
                if(arr[j].c[0]==task_string[i]){
                    coded_str+=arr[j].code;
                    continue;
                }
            }
        }
        SetAnwserInt(arr[30].code.length());
}

void Facade::CodingByHaffman(BinTree* head){
    std::string lcode=head->Get_Code()+"0";
    std::string rcode=head->Get_Code()+"1";
    int curr_sum=0;
    for(int i=0;i<(int)(head->Get_Data().length());i++){
        for(int j=30;j>=0;j--){
            if(head->Get_Data()[i]==arr[j].c[0]){
                curr_sum+=arr[j].n;
            }
        }
    }
    head->SetSum(curr_sum);
    if(head->Get_left() && head->Get_left()->Get_Code()==""){
        head->Get_left()->Set_Code(lcode);
        CodingByHaffman(head->Get_left());
    }
    if(head->Get_right()){
        head->Get_right()->Set_Code(rcode);
        CodingByHaffman(head->Get_right());
    }
    if(head->Get_Data().length()==1){
        for(int j=30;j>=0;j--){
            if(arr[j].c[0]==head->Get_Data()[0]){
                arr[j].code=head->Get_Code();
            }
        }
    }
    SetAnwserInt(arr[30].code.length());
}

void Facade::Decoding(BinTree *head, BinTree *fict){
    if (index <= coded_str.length()) {
            if (fict->Get_Data().length() == 1) {
                decoded_str += fict->Get_Data();
                if(head->Get_Data().length()==1){
                    index++;
                    if(coded_str.length()-index==1){
                        index++;
                    }
                }
                Decoding(head,head);
            }
            if(coded_str[index]=='0'){
                index++;
                Decoding(head,fict->Get_left());
            }else if(coded_str[index]=='1'){
                index++;
                Decoding(head,fict->Get_right());
            }
        }
}

void Facade::CreateHaffmanNodes(){
    BinTree* fict;
    for (int i=0;i<size;i++) {
        if(arr[i].n>0){
            fict=new BinTree(arr[i].c);
            fict->SetSum(arr[i].n);
            Haffman_tree.push_back(fict);
        }
    }
    std::reverse(Haffman_tree.begin(),Haffman_tree.end());
}

BinTree* Facade::MergeNodes(BinTree *left, BinTree *right){
    std::string str=left->Get_Data()+right->Get_Data();
    BinTree* head= new BinTree(str);

    head->SetLeft(left);
    head->SetRight(right);
    head->SetSum(left->GetSum()+right->GetSum());
    return head;
}

void Facade::CreateTreeByHaffman(){
    BinTree* head;
    while (Haffman_tree.size() >= 2){
         head=MergeNodes(Haffman_tree[Haffman_tree.size()-1], Haffman_tree[Haffman_tree.size()-2]);
         Haffman_tree.pop_back();
         Haffman_tree.pop_back();
         Haffman_tree.push_back(head);
         std::sort(Haffman_tree.begin(), Haffman_tree.end(), this->cmp);
    }
}

QString Facade::BuildFrequencyStr(){
    QString str="";
    for (int i=0;i<size;i++) {
        if(arr[i].n>0){
            str = str + QString::fromStdString(arr[i].c) + "(" + QString::number(arr[i].n) + ")\n";
        }
    }
    return str;
}

void Facade::BuildTreeFile(){
    std::string path="Tree";
    path+=".txt";
    file.open(path, std::fstream::in | std::fstream::out| std::fstream::trunc);
    file<<"digraph Tree{\n";
    if(code_tree_!=nullptr){
        BuildNode(code_tree_);
    }else if(this->GetHaffman_()!=nullptr){
        BuildNode(Haffman_tree[0]);
    }
    file << "}";
    file.close();
    std::string command = "dot -Tpng " + path;
    command+=" -o res.png";
    system(command.c_str());
    file_num++;
    file_index=0;
}

void Facade::BuildNode(BinTree *head){
    if(head->Get_left()){
        file<<"\""<<head->Get_Data()<< ", ("<<head->GetSum()<<")\"";
        file<<" -> \""<< head->Get_left()->Get_Data()<< ", ("<<head->Get_left()->GetSum()<<")\";\n";
        BuildNode(head->Get_left());
    }else{
        file << file_index << " [shape=point];\n";
        file<<"\""<<head->Get_Data()<< ", ("<<head->GetSum()<<")\"";
        file<<" -> "<< file_index <<";\n";
        file_index++;
    }
    if(head->Get_right()){
        file<<"\""<<head->Get_Data()<< ", ("<<head->GetSum()<<")\"";
        file<<" -> \""<< head->Get_right()->Get_Data()<< ", ("<<head->Get_right()->GetSum()<<")\";\n";
        BuildNode(head->Get_right());
    }else{
        file << file_index << " [shape=point];\n";
        file<<"\""<<head->Get_Data()<< ", ("<<head->GetSum()<<")\"";
        file<<" -> "<< file_index <<";\n";
        file_index++;
    }
}

void Facade::SetAnwserInt(int a){
    this->int_answer=a;
}

int Facade::GetAnswerInt(){
    return this->int_answer;
}

BinTree* Facade::GetHaffman_(){
    return this->Haffman_tree[0];
}

bool Facade::cmp(BinTree *t1, BinTree *t2){
    return t1->GetSum() > t2->GetSum();
}

simbol* Facade::GetArr(){
    return this->arr;
}

std::string Facade::GetSimbols(){
    return this->simbols;
}

BinTree* Facade::GetTree(){
    return this->code_tree_;
}

std::string Facade::GetTaskStr(){
    return this->task_string;
}

int Facade::GetSize(){
    return this->size;
}
