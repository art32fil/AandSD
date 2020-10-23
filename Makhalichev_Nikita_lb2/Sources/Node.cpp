#include "../Headers/Node.h"

lisp head(const lisp s){
    if (s != NULL){
        if (!isAtom(s)){
            return s->node.pair.hd;
        } else {
            cerr << "Error: Head(atom) \n";
            exit(1);
        }
    } else {
        cerr << "Error: Head(nil) \n";
        exit(1);
    }
}

bool isAtom(const lisp s){
    if(s == NULL){
        return false;
    } else {
        return (s->tag);
    }
}

bool isNull(const lisp s){
    return s == NULL;
}

lisp tail(const lisp s){
    if (s != NULL){
        if (!isAtom(s)){
            return s->node.pair.tl;
        } else {
            cerr << "Error: Tail(atom) \n";
            exit(1);
        }
    } else {
        cerr << "Error: Tail(nil) \n";
        exit(1);
    }
}

lisp cons(const lisp h, const lisp t){
    lisp p;
    if (isAtom(t)){
        cerr << "Error: Tail(nil) \n";
        exit(1);
    } else {
        p = new s_expr;
        if (p == NULL){
            cerr << "Memory not enough\n";
            exit(1);
        } else {
            p->tag = false;
            p->node.pair.hd = h;
            p->node.pair.tl = t;
            return p;
        }
    }
}

lisp make_atom(const Base x){
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.atom = x;
    return s;
}

void destroy(lisp s){
    if (s != NULL){
        if (!isAtom(s)){
            destroy(head (s));
            destroy(tail(s));
        }
        delete s;
    }
}

Base getAtom(const lisp s){
    if (!isAtom(s)){
        cerr << "Error: getAtom(s) for !isAtom(s) \n";
        exit(1);
    } else {
        return (s->node.atom);
    }
}

void read_lisp(lisp& y, string *line){
    Base x;
    if (line){
        x = (*line)[line->length()-1];
        line->pop_back();
    }
    read_s_expr(x, y, line);
}

void read_s_expr(Base prev, lisp& y, string *line){
    if (prev == ')'){
        cerr << " ! List.Error 1 " << endl;
        exit(1);
    } else {
        if (prev != '('){
            y = make_atom(prev);
        } else {
            read_seq(y, line);
        }
    }
}

void read_seq(lisp& y, string *line){
    Base x;
    lisp p1, p2;
    if (!line){
        cerr << " ! List.Error 2 " << endl;
        exit(1);
    } else {
        x = (*line)[line->length()-1];
        line->pop_back();
    }
    if (x == ')'){
        y = NULL;
    } else {
        read_s_expr ( x, p1, line);
        read_seq ( p2, line);
        y = cons (p1, p2);
    }
}

void write_lisp(const lisp x, string &out){
    if (isNull(x)){
        out += " ()";
    } else {
        if (isAtom(x)){
            out += ' ';
            out += x->node.atom;
        } else{
            out += " (";
            write_seq(x, out);
            out += " )";
        }
    }
}

void write_seq(const lisp x, string &out){
    if (!isNull(x)){
        write_lisp(head(x), out);
        write_seq(tail(x), out);
    }
}

int depth(lisp x, int d, bool &isNotEmpty){
    if (!isNull(x)){
        if (isAtom(x)){
            isNotEmpty = true;
            return d;
        } else {
            depth(head(x), d+1, isNotEmpty);
        }
    }
    return 0;
}

int depth_search(lisp x, int deep){
    string current;
    write_lisp(x, current);
    cout << "Checking - " << current << endl;
    bool isNotEmpty = false;
    int res = deep;
    if (!isNull(x)){
        if (isAtom(x)){
            return res;
        } else {
            int current = depth(head(x), 0, isNotEmpty);
            int current1 = depth_search(head(x), deep+1);
            int current2 = depth_search(tail(x), deep);
            if (isNotEmpty){
                res += current;
                if (current1 > res){
                    res = current1;
                }
                if (current2 > res){
                    res = current2;
                }
            }
        }
    }
    return res;
}
