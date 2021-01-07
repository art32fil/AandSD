#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ios>
#include <streambuf>

using namespace std;

typedef char base;	// базовый тип элементов (атомов)

struct node {
	base *hd;
	node *tl;
	// constructor
	node (){
		hd = NULL;
		tl = NULL;
	}
};

typedef node *list;
struct s_expr;
struct  two_ptr{
	s_expr *hd;
	s_expr *tl;
} ;	//end two_ptr;

struct s_expr {
	bool tag; // true: atom, false: pair
	union{
		base atom;
		two_ptr pair;
	} node;		//end union node
};			//end s_expr

typedef s_expr *lisp;

// функции
void create_tabs(int level);
void print_s_expr( lisp s );
lisp head (const lisp s);
lisp tail (const lisp s);
lisp cons (const lisp h, const lisp t);
lisp make_atom (const base x);
bool isAtom (const lisp s);
bool isNull (const lisp s);
void destroy (lisp s);
base getAtom (const lisp s);
list cons (base x, list t);
int count_seq(const lisp x, int count, int level);
int count_lisp(const lisp x, int count, int level);
list make_list_lisp(const lisp x, int level, list p);
list make_list_seq(const lisp x, int level, list p);


	// функции ввода:
void read_lisp ( lisp& y);
void read_s_expr (base prev, lisp& y);
void read_seq ( lisp& y);
void read_lisp_file (ifstream &file, lisp& y);
void read_s_expr_file (ifstream &file, base prev, lisp& y);
void read_seq_file (ifstream &file, lisp& y);




	// функции вывода:
void write_lisp (const lisp x);
void write_seq (const lisp x);



void create_tabs(int level){
	for(int i= 0; i<level; i++){
		cout<<"\t";
	}
}

lisp tail (const lisp s){
	if (s != nullptr){
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

lisp head (const lisp s){
	if (s != nullptr){
		if (!isAtom(s)){
			return s->node.pair.hd;
		} else {
			cerr << "Error: Head(atom) \n";
			exit(1);
		}
	} else {
		cerr << "Error: Head(nullptr) \n";
		exit(1);
	}
}

bool isAtom (const lisp s){
	if(s == nullptr) {
		return false;
	} else {
		return (s -> tag);
	}
}

bool isNull (const lisp s){
	return s==nullptr;
}

lisp cons (const lisp h, const lisp t){
	lisp p;
	if (isAtom(t)){
		cerr << "Error: Tail(nil) \n";
		exit(1);
	} else {
		p = new s_expr;
		if (p == nullptr){
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

lisp make_atom (const base x){
	lisp s;
	s = new s_expr;
	s -> tag = true;
	s->node.atom = x;
	return s;
}

void destroy (lisp s) {
	if (s != nullptr) {
		if (!isAtom(s)) {
			destroy ( head (s));
			destroy ( tail(s));
		}
		delete s;
	}
}

base getAtom (const lisp s){
	if (!isAtom(s)){
		cerr << "Error: getAtom(s) for !isAtom(s) \n";
		exit(1);
	}else{
		return (s->node.atom);
	}
}

// ввод списка с консоли
void read_lisp ( lisp& y){
	base x;
	do{
		cin >> x;
	}while (x==' ');
	read_s_expr ( x, y);
}

void read_s_expr (base prev, lisp& y){ //prev - ранее прочитанный символ
	if ( prev == ')' ) {
		cerr << " ! List.Error 1 " << endl;
		exit(1);
	} else if ( prev != '(' ) {
		y = make_atom (prev);
	} else {
		read_seq (y);
	}
}

void read_seq ( lisp& y) {
	base x;
	lisp p1, p2;
	cin>>noskipws;
	cin >> x;
	if (x == '\n') {
		cerr << " ! List.Error 2 " << endl;
		exit(1);
	} else {
		while  ( x==' ' ) {
			cin >> x;
		}
		if ( x == ')' ){
			y = nullptr;
		} else {
			read_s_expr ( x, p1);
			read_seq ( p2);
			y = cons (p1, p2);
		}
	}
}

void read_lisp_file (ifstream &file, lisp& y){
	base x;
	do{
		file >> x;
	}while (x==' ');
	read_s_expr_file (file,x,y);
}

void read_s_expr_file (ifstream &file, base prev, lisp& y){ //prev - ранее прочитанный символ
	if ( prev == ')' ) {
		cerr << " ! List.Error 1 " << endl;
		exit(1);
	} else if ( prev != '(' ) {
		y = make_atom (prev);
	} else {
		read_seq_file(file,y);
	}
}

void read_seq_file (ifstream &file, lisp& y) {
	base x;
	lisp p1, p2;
	if (!(file >> x)) {
		cerr << " ! List.Error 2 " << endl;
		exit(1);
	} else {
		while  ( x==' ' ) {
			file >> x;
		}
		if ( x == ')' ){
			y = nullptr;
		} else {
			read_s_expr_file (file, x, p1);
			read_seq_file (file, p2);
			y = cons (p1, p2);
		}
	}
}

void write_lisp (const lisp x){// ѕроцедура вывода списка с обрамл€ющими его скобками,
							   // пустой список выводитс€ как ()
	if (isNull(x)){
		cout << " ()";
	} else if (isAtom(x)){
		cout << ' ' << x->node.atom;
	} else  { 				   // непустой список}
		cout << " (" ;
		write_seq(x);
		cout << " )";
	}
}

void write_seq (const lisp x)  {//ѕроцедура вывода списка без обрамл€ющих его скобок
	if (!isNull(x)) {
		write_lisp(head (x));
		write_seq(tail (x));
	}
}


void conc2 (list &y, const list z){	// процедура conc2 (y := y*z)
	if (y==nullptr) {
		y = z;
	} else {
		conc2(y->tl, z);
	}
}

void write_list ( list s ){
	list p = s;
	short i = 0;
	while (p != nullptr) {
		i++;
		cout << i << " : " << *p->hd << "(" << int (*p->hd) << ") "<< endl;
		p = p->tl;
	}
}

list cons (base x, list t){
	list p = new node;
	if (p == nullptr){
		cerr << "Memory not enough\n";
		exit(1);
	} else {
		p->hd = new char;
		*p->hd = x;
		p->tl = t;
		return p;
	}
}

//ѕодсчЄт элементов последовательности списка с обрамл€ющими скобками
int count_lisp(const lisp x, int count, int level){
	level++;
	if(isNull(x)){
		return count;
	} else if (isAtom(x)){
		create_tabs(level);
		cout<< x->node.atom << " - it's Atom" << endl;
		count++;
		create_tabs(level);
		cout <<"count_1 = "<<count<<endl;
	} else {
		create_tabs(level);
		cout<< "( - It's not Atom" << endl;
		count+=count_seq(x,count,level);
		create_tabs(level);
		cout <<"count_2 = "<<count<<endl;
	}
	create_tabs(level);
	cout<< "Head sum = "<<count<<endl;
	return count;
}

//ѕодсчЄт элементов последовательности списка без обрамл€ющих скобок
int count_seq(const lisp x, int count, int level){
	level++;
	if(!isNull(x)){
		int head1 = count_lisp(head(x), count, level);//—умма элементов в голове списка
		int tail1 = count_seq(tail(x), count, level);//—умма элементов в хвосте списка
		count = head1+tail1;
		create_tabs(level);
		cout<< "Equal to head and tail's sum " << endl;
		create_tabs(level);
		cout<< "Head = "<<head<<endl;
		create_tabs(level);
		cout<< "Tail = "<<tail<<endl;
		create_tabs(level);
		cout<< "Result sum = "<<count<<endl;
	} else {
		create_tabs(level);
		cout<< "Tail = 0 !!!" << endl;
		count = 0;
	}
	return count;
}

//—оздание линейного списка из элементов списка с обрамл€ющими скобками
list make_list_lisp(const lisp x, int level, list p){
	level++;
	if(isNull(x)){
		return p;
	} else if (isAtom(x)){
		p = cons(x->node.atom, p);
		create_tabs(level);
		write_list(p);
	} else {
		create_tabs(level);
		cout<< "( - It's not Atom" << endl;
		conc2(p, make_list_seq(x, level, p));
	}
	return p;
}

// —оздание линейного списка из элементов списка без обрамл€ющих скобок
list make_list_seq(const lisp x, int level, list p){
	level++;
	if(!isNull(x)){
		create_tabs(level);
		cout<<"List consist of head and tail elements"<<endl;
		list head1 = make_list_lisp(head(x), level, p);
		list tail1 = make_list_seq(tail(x), level, p);
		conc2(head1, tail1);
		create_tabs(level);
		write_list(head1);
		return head1;
	}
	create_tabs(level);
	cout<<"No elements in tail!"<<endl;
	return nullptr;
}

int main(){
	int way;
	cout<<"1 - console\n2 - file\nYour choice: "<<endl;
	cin>>way;
	lisp lisp;
	if(way == 1){
		cout<<"Enter your list :"<<endl;
		read_lisp(lisp);
	} else if (way == 2){
		string filename;
		cout<<"Enter filename:"<<endl;
		cin>>filename;
		ifstream file (filename);
		if(!file){
			cerr<<"File can't be opened!"<<endl;
			exit(0);
		}
		char letter;
		file>>letter;
		file.seekg(0,ios::beg);
		string line;
		getline(file, line);
		cout<<"File content : "<< line<<endl;
		file.seekg(0,ios::beg);
		read_lisp_file(file, lisp);
		file.close();
		cout<<"Entered list :"<<endl;
		write_lisp(lisp);
		cout<<endl;
	} else {
		cerr<<"Wrong way! Try again!"<<endl;
		exit(0);
	}
	cout<<endl;
	int countElem = 0;
	int recLevel = 0;
	list listPtr = nullptr;
	countElem = count_lisp(lisp,countElem,recLevel);
	listPtr = make_list_lisp(lisp, recLevel, listPtr);
	cout<<"Number of elements in list = "<<countElem<<endl;
	cout<<"Linear list: ";
	write_list(listPtr);
	cout<<endl;
	return 0;
}

