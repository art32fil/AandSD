#include "elements.h"

ostream& operator <<(ostream& out, Symbol<char>& symb){
    if(symb.deleted){
        out << "[deleted]";
        return out;
    }

    char key = symb.key;

    out << "'";
    if((signed char)(key) < 0){
        out << "~";
        key = ~key;
    }
    if(isgraph(key)) out << key;
    else{
        switch(key){
        case ' ':
            out << "<SPACE>";
            break;
        case '\t':
            out << "<TAB>";
            break;
        default:
            out << "^" << (char)(key + '@');
        }
    }
    out << "'";
    return out;
}

ostream& operator <<(ostream& out, Symbol<char>* symb){
    while(symb){
        out << *symb << "(x" << symb->count << ") -> ";
        symb = symb->link;
    }
    out << "nil\n";
    return out;
}



