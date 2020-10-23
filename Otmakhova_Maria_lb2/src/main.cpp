#include <iostream>
#include "l_intrfc.h"
#include <string>

using namespace std;
using namespace h_list;

lisp concat (const lisp y, const lisp z);
bool counter(lisp, string);
lisp reverse(const lisp s);
lisp rev(const lisp s,const lisp z);

lisp flatten1(const lisp s);

int main ( )
{
    lisp s1;
    string values;
    cout << "enter values:" << endl;
    getline(cin,values);
    cout << "enter list:" << endl;
    read_lisp (s1);
    cout << "result: " << endl;
    cout << counter(reverse(flatten1(s1)), values) << endl;
    destroy (s1);
    return 0;
}

lisp concat (const lisp y, const lisp z)
{
    if (isNull(y)) return copy_lisp(z);
    else return cons (copy_lisp(head (y)), concat (tail (y), z));
}

lisp reverse(const lisp s)
{
    return(rev(s,NULL));
}


lisp rev(const lisp s,const lisp z)
{
    if(isNull(s)) return(z);
    else if(isAtom(head(s))) return(rev(tail(s), cons(head(s),z)));
    else return(rev(tail(s), cons(rev(head(s), NULL),z)));
}


lisp flatten1(const lisp s)
{
    if (isNull(s)) return NULL;
    else if(isAtom(s)) return cons(make_atom(getAtom(s)),NULL);
    else //s - непустой список
    if (isAtom(head(s))) return cons( make_atom(getAtom(head(s))),flatten1(tail(s)));
    else //Not Atom(Head(s))
        return concat(flatten1(head(s)),flatten1(tail(s)));
}


bool analyze(lisp &list, string values, bool answer){
    int pos = values.find(head(list)->node.atom);
    list = tail(list);
    bool answer1;
    if(values[pos+2] == '1')
        answer1 = true;
    else
        answer1 = false;
    switch (head(list)->node.atom) {
        case 'R':
            answer = answer || answer1;
            list = tail(list);
            list = tail(list);
            return answer;
            break;
        case 'D':
            answer = answer && answer1;
            list = tail(list);
            list = tail(list);
            list = tail(list);
            return answer;
            break;
        case 'T':
            answer = !answer1;
            list = tail(list);
            list = tail(list);
            list = tail(list);
            return answer;
            break;
        case 'N':
            answer = !(answer || answer1);
            list = tail(list);
            list = tail(list);
            list = tail(list);
            return answer;
            break;
    }
}

bool counter(lisp list, string values) {
    bool answer;
    while (!isNull(list)) {
        answer = analyze(list, values, answer);
    }
    return answer;
}