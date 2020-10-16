#include "list.h"

List* setElem(List* headNew, List* tailNew){
    List* newElem;
    if(tailNew -> isAtom()){
        cout << "Error, tail is atomic" << endl;
        exit(1);
    }
    else{
        newElem = new List;
        newElem->isAtomic = false;
        newElem->Node.pair.head = headNew;
        newElem->Node.pair.tail = tailNew;
        return newElem;
    }
    
}


List* setData(const base data){
    List* newElem = new List;
    newElem->isAtomic = true;
    newElem->Node.atom = data;
    return newElem;
}

List* List::reverse(){
    return reverseRec(this, nullptr);
}

List* reverseRec(List* head, List* tail){
    if(head->isEmpty()){
        return tail;
    }else if(head->head()->isAtom()){
        return (reverseRec(head->tail(), setElem(head->head(), tail)));
    }else{
        return (reverseRec(head->tail(), setElem(reverseRec(head->head(), nullptr), tail)));
    }
}



List* List::head(){
    if(this != nullptr){
        if (this->isAtom() == false){
            return this->Node.pair.head;
        }
        else{
            cout << "Your element is atom!" << endl;
            exit(1);
        }
    }
    else{
        cout << "Head is empty!" << endl;
        exit(1);
    }
}

List* List::tail(){
    if (this != nullptr){
        if(this->isAtom() == false){
            return this->Node.pair.tail;
        }
        else{
            cout << "Your element is atom!" << endl;
            exit(1);
        }
    }
    else{
        cout << "Tail is empty!" << endl;
        exit(1);
    }
}

bool List::isAtom(){
    if (this->isEmpty())
        return false;
    return this->isAtomic;
}

bool List::isEmpty(){
    return this == nullptr;
}



void readListFromFile(List* &y, string& line, int& cur, int& len){
    while(line[cur] == ' '){
        cur++;
    }
    readElemFromFile(y, line, cur, len);
}

void readElemFromFile(List* &y, string& line, int& cur, int& len){
    base prev = line[cur];
    if ( prev == ')'){
        cout << "Error" << endl;
        exit(1);
    }else if(prev != '('){
        y = setData(prev);
    }else{
        readSeqFromFile(y, line, cur, len);
    }
}

void readSeqFromFile(List* &y, string& line, int& cur, int& len){
    //base x;
    List* firstElem;
    List* secondElem;

    if(cur >= len){
        cout << "Error" << endl;
        exit(1);
    }
    else{
        cur++;
        while( line[cur] == ' ') cur++;
        if ( line[cur] == ')'){
            y = nullptr;
        }
        else{
            readElemFromFile(firstElem, line, cur, len);
            readSeqFromFile(secondElem, line, cur, len);
            y = setElem(firstElem, secondElem);
        }
    }
}

void readList(List* &y){
    base x;
    do cin >> x; while(x == ' ');
    readElem(x, y);
}

void readElem(base prev, List* &y){
    if ( prev == ')'){
        cout << "Error" << endl;
        exit(1);
    }else if(prev != '('){
        y = setData(prev);
    }else{
        readSeq(y);
    }
}

void readSeq(List* &y){
    base x;
    List* firstElem;
    List* secondElem;

    if(!(cin >> x)){
        cout << "Error" << endl;
        exit(1);
    }
    else{
        while( x == ' ') cin >> x;
        if ( x == ')'){
            y = nullptr;
        }
        else{
            readElem(x, firstElem);
            readSeq(secondElem);
            y = setElem(firstElem, secondElem);
        }
    }
}

void writeList(List* y){
    if(y->isEmpty()){
        cout << "()" << endl;
    }
    else if(y->isAtom()){
        cout << y->Node.atom;
    }
    else{
        cout << "(";
        writeSeq(y);
        cout << ")";
    }
}

void writeSeq(List* y){
    if(!y->isEmpty()){
        writeList(y->head());
        writeSeq(y->tail());
    }
}


void destroy(List* elem){
    if (elem != nullptr){
        if (!elem->isAtom()){
            destroy(elem->head());
            destroy(elem->tail());
        }
        delete elem;
    }
}


