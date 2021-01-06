#include <iostream>
#include <list>
#include <iterator>
#include <typeinfo>
#include <string>

using namespace std;
static int step = 0;


template <typename T>
list<T> enterList(){
    T num;
    list<T> list;
    cout<<"Enter your sequence:"<<endl;
    string n;
    do{ 
        cin >> n;
        if (typeid(T) == typeid(int)){
            num = stoi(n);
        } else if (typeid(T) == typeid(float)){
            num = stof(n);
        } else if (typeid(T) == typeid(double)){
            num = stod(n);
        } else if (typeid(T) == typeid(long int)){
            num = stol(n);
        } else {
            cout<<"Wrong type of sequence elements!"<<endl;
            exit(0);
        }
        
        list.push_back(num);
    }while(cin.peek() != '\n');
    return list;
}



template <typename T>
list<T> strandSort(list<T>& list){
    if(list.size()<2){
        return list;
    }
    std::list<T> tempList;
    std::list<T> resultList;
    
    while(!list.empty()){
        cout<<"\x1b[1;31m\t\t\t\t\tStep "<<step<<"\x1b[0m"<<endl;
        cout<<"\x1b[1;32m\t\t\tlist: \x1b[0m";
        for(typename std::list<T>::iterator iter = list.begin(); iter != list.end(); iter++){
            cout<<*iter<<' ';
        }
        cout<<endl;
        cout<<"\x1b[1;33m\t\t\ttempList: \x1b[0m";
        for(typename std::list<T>::iterator iter = tempList.begin(); iter != tempList.end(); iter++){
            cout<<*iter<<' ';
        }
        cout<<endl;
        cout<<"\x1b[1;31m\t\t\tresultList: \x1b[0m";
        for(typename std::list<T>::iterator iter = resultList.begin(); iter != resultList.end(); iter++){
            cout<<*iter<<' ';
        }
        cout<<endl;

        cout<<"\n\tpush the first  element of \"list\" to the end of \"tempList\""<<endl;
        tempList.push_back(list.front()); // first element of "list" to the end of "tempList"
        list.pop_front();                 // delete first element in "list"
        cout<<"\x1b[1;32mlist: \x1b[0m";
        for(typename std::list<T>::iterator iter = list.begin(); iter != list.end(); iter++){
            cout<<*iter<<' ';
        }
        cout<<endl;
        cout<<"\x1b[1;33mtempList: \x1b[0m";
        for(typename std::list<T>::iterator iter = tempList.begin(); iter != tempList.end(); iter++){
            cout<<*iter<<' ';
        }
        cout<<endl;
        
        int i =0;
        typename list<T>::iterator it;
        for(it = list.begin(); it!=list.end();){
            cout<<"\n\titeration "<<i<<" in step "<<step<<":"<<endl;
            if(tempList.back() <= *it){  // if last element in "tempList" less than current in "list"
                tempList.push_back(*it); // current elemnt in "list" to the end of "tempList"
                it = list.erase(it);     // current element is next after deleted one
            } else {
                it++;
            }
            cout<<"\x1b[1;32mlist: \x1b[0m";
            for(typename std::list<T>::iterator iter = list.begin(); iter != list.end(); iter++){
                cout<<*iter<<' ';
            }
            cout<<endl;
            cout<<"\x1b[1;33mtempList: \x1b[0m";
            for(typename std::list<T>::iterator iter = tempList.begin(); iter != tempList.end(); iter++){
                cout<<*iter<<' ';
            }
            cout<<endl;
            
            i++;
        }
        
        resultList.merge(tempList);      // merge two sorted lists
        cout<<"\x1b[1;31mresultList: \x1b[0m";
        for(typename std::list<T>::iterator iter = resultList.begin(); iter != resultList.end(); iter++){
            cout<<*iter<<' ';
        }
        cout<<endl;
        cout<<"\n\n";
        step++;

    }
    
    return resultList;
}




int main()
{
    std::list<long int> list = enterList<long int>();
    
    std::list<long int> listCopy;
    for(typename std::list<long int>::iterator iter = list.begin(); iter != list.end(); iter++){
        listCopy.push_back(*iter);
    }

    std::list<long int> sortedList = strandSort<long int>(list);
    listCopy.sort();
    
    cout<<"\n\t\tRESULT:"<<endl;
    cout<<"\x1b[1mStrand sort: \x1b[0m";
    for(typename std::list<long int>::iterator iter = sortedList.begin(); iter != sortedList.end(); iter++){
        cout<<*iter<<' ';
    }
    cout<<endl;
    cout<<"\x1b[1m\nstd::list::sort: \x1b[0m";
    for(typename std::list<long int>::iterator iter = listCopy.begin(); iter != listCopy.end(); iter++){
        cout<<*iter<<' ';
    }
    cout<<endl;
    

    return 0;
}


/*
template <typename T>
list<T> printList(list<T> list){
    for(typename std::list<T>::iterator iter = list.begin(); iter != list.end(); iter++){
        cout<<*iter<<' ';
    }
    cout<<endl;
}

template <typename T>
list<T> copyList(list<T> list){
    std::list<T> listCopy;
    typename list<T>::iterator it;
    for(it = list.begin(); it!=list.end();it++){
        listCopy.push_back(*it);
    }
    return listCopy;
}*/


