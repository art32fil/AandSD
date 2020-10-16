#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

using namespace std;

typedef char base;

class List;

class Pair{
public:
    List* head;
    List* tail;
};


class List{
public:
    bool isAtomic;
    union{
        base atom;
        Pair pair;
    } Node;
    
    
    List* head();
    List* tail();
    bool isAtom();
    bool isEmpty();
    List* reverse();
    
};

List* setElem(List* headNew, List* tailNew);
List* setData(const base data);
void readList(List* &y);
void readElem(base prev, List* &y);
void readSeq(List* &y);
void writeList(List* y);
void writeSeq(List* y);
List* reverseRec(List* head, List* tail);

void readListFromFile(List* &y, string& line, int& cur, int& len);
void readElemFromFile(List* &y, string& line, int& cur, int& len);
void readSeqFromFile(List* &y, string& line, int& cur, int& len);

void destroy(List* elem);
#endif //LIST_H