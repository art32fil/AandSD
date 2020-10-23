#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

typedef char base;
struct s_expr;

struct two_ptr{
    s_expr *head;
    s_expr *tail;
};

struct s_expr{
    bool tag;
    union{
        base atom;
        two_ptr pair;
    } node;
};

typedef s_expr *lisp;

lisp head(const lisp s);
lisp tail(const lisp s);
bool isAtom(const lisp s);
bool isNull(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(const base x);
void destroy(lisp s);
void write_lisp(const lisp s);
void write_seq(const lisp s);
void read_lisp(lisp& s, ifstream& fin, int& flag);
void read_s_expr(base prev, lisp& s, ifstream& fin);
void read_seq(lisp& s, ifstream& fin);

lisp head(const lisp s){
    if (s != nullptr){
        if (!isAtom(s))
            return s->node.pair.head;
        else{
           cout << "Error: s is atom\n";
           destroy(s);
           exit(1);
        }
    }
    else{
        cout << "Error: s is nullptr\n";
        exit(1);
    }
}

lisp tail(const lisp s){
    if (s != nullptr){
        if (!isAtom(s))
            return s->node.pair.tail;
        else{
            cout << "Error: s is atom\n";
            destroy(s);
            exit(1);
        }
    }
    else{
        cout << "Error: s is nullptr\n";
        exit(1);
    }
}

bool isAtom(const lisp s){
    if (s == nullptr)
        return false;
    else
        return s->tag;
}

bool isNull(const lisp s){
    return s == nullptr;
}

lisp cons(const lisp h, const lisp t){
    lisp p;
    if (isAtom(t)){
        cout << "Error\n";
        destroy(h);
        destroy(t);
        exit(1);
    }
    else{
        p = new s_expr;
        if (p == NULL){
            cout << "Error. Memory is not enough\n";
            exit(1);
        }
        else{
            p->tag = false;
            p->node.pair.head = h;
            p->node.pair.tail = t;
            return p;
        }
    }
}

lisp make_atom(const base x){
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.atom = x;
    return s;
}

void destroy(lisp s){
    if (s != nullptr){
        if (!isAtom(s)){
            destroy(head(s));
            destroy(tail(s));
        }
        delete s;
    }
}

void write_lisp(const lisp s){
    if (isNull(s))
        cout << "()";
    else if (isAtom(s))
        cout << ' ' << s->node.atom << ' ';
    else{
        cout << "(";
        write_seq(s);
        cout << ")";
    }
}

void write_seq(const lisp s){
    if (!isNull(s)){
        write_lisp(head(s));
        write_seq(tail(s));
    }
}

void read_lisp(lisp& s, ifstream& fin, int& flag){
    base x;
    do
        fin >> x;
    while (x == ' ');
    if (fin.eof()){
        flag = 1;
        return;
    }
    read_s_expr(x, s, fin);
}

void read_s_expr(base prev, lisp& s, ifstream& fin){
    if (prev == ')'){
        cout << "! List.Error 1\n";
        destroy(s);
        exit(1);
    }
    else if (prev != '(')
        s = make_atom(prev);
    else
        read_seq(s, fin);
}

void read_seq(lisp& s, ifstream& fin){
    base x;
    lisp p1, p2;
    if (!(fin >> x)){
        cout << "! List.Error 2\n";
        destroy(s);
        exit(1);
    }
    else{
        while (x == ' ')
            fin >> x;
        if (x == ')')
            s = nullptr;
        else{
            read_s_expr(x, p1, fin);
            read_seq(p2, fin);
            s = cons(p1, p2);
        }
    }
}

struct list{
    base data;
    list* next;
};

list* createListEl(base el){
    list* t = new list;
    t->data = el;
    t->next = nullptr;
    return t;
}

void push(list* &head, base el){
    if (!head){
        head = createListEl(el);
        return;
    }
    list* cur = head;
    list* t = createListEl(el);
    while (cur->next)
        cur = cur->next;
    cur->next = t;
}

int countEl(list* head){
    if (!head)
        return 0;
    list* cur = head;
    int n = 0;
    while (cur){
        n++;
        cur = cur->next;
    }
    return n;
}

void removeEl(list* head){
    list* cur = head;
    list* prev = head;
    while (cur->next){
        prev = cur;
        cur = cur->next;
    }
    prev->next = nullptr;
    delete cur;
}

void printList(list* head){
    cout <<"(";
    list* cur = head;
    while(cur){
        cout << " " << cur->data << " ";
        cur = cur->next;
    }
    cout << ")\n";
}

void lispElements(const lisp s, list* &hd){
    if (isNull(s))
        return;
    if (isAtom(s)){
        push(hd, s->node.atom);
    }
    else{
        lispElements(head(s), hd);
        lispElements(tail(s), hd);
    }
}

int main(){
    string filename;
    cout << "Enter a file name\n";
    cin >> filename;
    ifstream fin(filename);
    int flag = 0;
    while(fin){
        lisp s;
        list* head = nullptr;
        read_lisp(s, fin, flag);
        if (flag)
            break;
        cout << "Иерархический список: ";
        write_lisp(s);
        cout << '\n';
        lispElements(s, head);
        cout << "Линейный список: ";
        printList(head);
        cout << '\n';
        destroy(s);
        for (int i = 0; i<countEl(head)-1; i++){
            removeEl(head);
        }
        delete head;
    }
    fin.close();
    return 0;
}