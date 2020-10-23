// continue of namespace h_list
#include "l_intrfc.h"
#include <iostream>
#include <cstdlib>

using namespace std;
namespace h_list
{

//....................................
	lisp head (const lisp s)
	{// PreCondition: not null (s)
		if (s != NULL) if (!isAtom(s))	return s->node.pair.hd;
			else { cerr << "Error: Head(atom) \n"; exit(1); }
		else { cerr << "Error: Head(nil) \n";
			exit(1);
		}
	}
//.......................................
	bool isAtom (const lisp s)
	{	if(s == NULL) return false;
	else return (s -> tag);
	}
//.......................................
	bool isNull (const lisp s)
	{ return s==NULL;
	}
//.......................................
	lisp tail (const lisp s)
	{// PreCondition: not null (s)
		if (s != NULL) if (!isAtom(s))	return s->node.pair.tl;
			else { cerr << "Error: Tail(atom) \n"; exit(1); }
		else { cerr << "Error: Tail(nil) \n";
			exit(1);
		}
	}
//.......................................
	lisp cons (const lisp h, const lisp t)
	// PreCondition: not isAtom (t)
	{lisp p;
	if (isAtom(t)) { cerr << "Error: Tail(nil) \n"; exit(1);}
	else {	
		p = new s_expr; 
		if ( p == NULL)	{cerr << "Memory not enough\n"; exit(1); } 	
		else {
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;	
		}
	}
	}
//...........................
	lisp make_atom (const base x)
	{	lisp s;
		s = new s_expr;
		s -> tag = true;
		s->node.atom = x;
		return s;
	}

//...........................
	void destroy (lisp s) 
	{
	if ( s != NULL) {
		if (!isAtom(s)) {
			destroy ( head (s));
			destroy ( tail(s));
		}
		delete s;
		// s = NULL;
	};
	}
//...........................
	base getAtom (const lisp s)
	{
		if (!isAtom(s)) { cerr << "Error: getAtom(s) for !isAtom(s) \n"; exit(1);}
		else return (s->node.atom);
	}

	
//...........................
// ввод списка с консоли
	void read_lisp ( lisp& y , string& str)
	{	base x;
		//infile->is_open() ? *infile >> x : cin >> x;
		cout << "read_lisp() got: " << str << "\n";
		x = str.substr(0, str.find_first_of(" "));
		cout << "read_lisp() has read: " << x << "\n";
		str.erase(0, str.find_first_not_of(" ",str.find_first_of(" ")));
		cout << "read_lisp(): Cut str: " << str << "\n";
		read_s_expr (x, y, str);
	} //end read_lisp
//...........................
	void read_s_expr (base prev, lisp& y, string& str)
	{ //prev - ранее прочитанный символ}
		if ( prev == ")" ) {cerr << " ! List.Error 1 " << endl; exit(1); } 
		else if ( prev != "(" ) y = make_atom (prev);
			 else read_seq (y, str);
	} //end read_s_expr
//...........................
	void read_seq (lisp& y , string& str) 
	{	base x; 
		lisp p1, p2;

			//infile->is_open() ? *infile >> x : cin >> x;
			cout << "read_seq() got: " << str << "\n";
			x = str.substr(0, str.find_first_of(" "));
			cout << "read_seq(): x: " << x << "\n";
			str.erase(0, str.find_first_not_of(" ",str.find_first_of(" ")));
			cout << "read_seq(): cut str: " << str <<  "\n";
			if ( x == ")" ) y = NULL;
			else {
				read_s_expr ( x, p1, str);
				read_seq (p2, str) ;
				y = cons (p1, p2);
			} 
	} //end read_seq
//...........................
// ѕроцедура вывода списка с обрамл€ющими его скобками - write_lisp,
//  а без обрамл€ющих скобок - write_seq
	void write_lisp (const lisp x, ofstream* outfile)
	{//пустой список выводитс€ как () 
	if (isNull(x)){ 
		cout << RED << " ()" << NORMAL;
		*outfile << " ()";
	}
	else if (isAtom(x)) {cout << ' ' << x->node.atom; *outfile << " " << x->node.atom;}
		else  { //непустой список} 
			cout << RED << " (" << NORMAL;
			*outfile << " (";
			write_seq(x, outfile);
			cout << RED << " )" << NORMAL;
			*outfile << " )";
		}
	} // end write_lisp
//...........................
void write_seq (const lisp x, ofstream* outfile)  
{//выводит последовательность элементов списка без обрамл€ющих его скобок
	if (!isNull(x)) {
		write_lisp(head (x), outfile); 
		write_seq(tail (x), outfile);
	}
}
//...........................
lisp copy_lisp (const lisp x)
{	if  (isNull(x)) return NULL;
	else if (isAtom(x)) return make_atom (x->node.atom);
	else return cons (copy_lisp (head (x)), copy_lisp (tail(x)));
} //end copy-lisp


lisp concat (const lisp y, const lisp z)
        {
        if (isNull(y)) return copy_lisp(z);
        else return cons (copy_lisp(head (y)), concat (tail (y), z));
} // end concat

lisp flatten1(const lisp s)
        {
                if (isNull(s)) return NULL;
                else if(isAtom(s)) return cons(make_atom(getAtom(s)),NULL);
                else //s - непустой список 
                if (isAtom(head(s))) return cons( make_atom(getAtom(head(s))),flatten1(tail(s)));
                else //Not Atom(Head(s))
                        return concat(flatten1(head(s)),flatten1(tail(s)));
        }

double calculate(const lisp list, ofstream* outfile){
	write_lisp(list, outfile);
	cout << "\n";
	*outfile << "\n";
	//cout << "Tail -- null? " << (!isNull(list) && isNull(tail(list))) << "\n";
	if(isNull(list)) return NAN;
	if(isAtom(list)) return stod(list->node.atom);
	if(isNull(tail(list))) return calculate(head(list),outfile);
	if(isAtom(head(list))){
		if(head(list)->node.atom == "+"){
			return calculate(head(tail(list)),outfile) + calculate(tail(tail(list)),outfile);
		}
		if(head(list)->node.atom == "-"){
                        return calculate(head(tail(list)),outfile) - calculate(tail(tail(list)),outfile);
                }
		if(head(list)->node.atom == "*"){
                        return calculate(head(tail(list)),outfile) * calculate(tail(tail(list)),outfile);
                }
		if(head(list)->node.atom == "power"){
                        return pow(calculate(head(tail(list)),outfile),calculate(tail(tail(list)),outfile));
                }

	}
	return NAN; 
}

} // end of namespace h_list
