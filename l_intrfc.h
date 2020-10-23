#include <string>
#include <cmath>
#include <fstream>

using namespace std;

#define NORMAL "\033[0m"
#define RED "\033[0;31m"
// интерфейс АТД "Иерархический Список"
namespace h_list
{
	typedef std::string base;	// базовый тип элементов (атомов)

	struct s_expr;
	struct  two_ptr
		{
		s_expr *hd;
		s_expr *tl;
	} ;	//end two_ptr;

	struct s_expr {
		bool tag; // true: atom, false: pair
		struct  
		{
			base atom;
			two_ptr pair;	
		} node;		//end struct node
	};			//end s_expr 
	
	typedef s_expr *lisp;

// функции 
	void print_s_expr( lisp s );
	// базовые функции:
	lisp head (const lisp s);
	lisp tail (const lisp s);
	lisp cons (const lisp h, const lisp t);
	lisp make_atom (const base x);
	bool isAtom (const lisp s);
	bool isNull (const lisp s);
	void destroy (lisp s);
	
	base getAtom (const lisp s);

	double calculate(const lisp s, ofstream* outfile);

	// функции ввода:
	void read_lisp ( lisp& y, /*ifstream* infile*/ string& str); // основная
	void read_s_expr (base prev, lisp& y , /*ifstream* infile*/ string& str); 
	void read_seq ( lisp& y, /*ifstream* infile*/ string& str); 
	
	// функции вывода:
	void write_lisp (const lisp x, ofstream* outfile);		// основная
	void write_seq (const lisp x, ofstream* outfile);  
	
	lisp copy_lisp (const lisp x);
	lisp flatten1(const lisp s);
	lisp concat (const lisp y, const lisp z);

} // end of namespace h_list
