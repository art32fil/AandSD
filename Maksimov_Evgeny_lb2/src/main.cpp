#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Elem{
	Elem* tail = NULL;
	Elem* child = NULL;
	char data = 0;
	bool dataTag = 0;
} Elem;

void lineToLists(string& line, vector<Elem*>& pointerCollector);
bool splitString(string &line, string &line1, string &line2);
Elem* getHList(string line, int& i, Elem* hListHead, vector<Elem*>& pointerCollector, int depth = 0);
bool isUniqueData(Elem* hList, vector<char>& dataCollector);
bool equalLists(Elem* hList1, Elem* hList2);
bool isData(char c);
void recursionDepth(char s, int n, bool sublist = false);
void push(Elem*& hListHead, Elem* hListTail);
void setData(Elem* hListElem, char data);
Elem* error(int n);

int main(int argc, char *argv[]){
	string line;
	vector<Elem*> pointerCollector;
	if(argc==1){
		cout << "Write input lists:\t";
		getline(cin, line);
		lineToLists(line, pointerCollector);
	}else if(argc==2){
		line = argv[1];
		ifstream in(line);
		if(!in){
			error(10);
			return 0;
		}
		ofstream out("HLists.txt");
    	streambuf *coutbuf = cout.rdbuf();
    	cout.rdbuf(out.rdbuf());
		int lineNum;
		for(lineNum = 1; getline(in, line); lineNum++){
			cout << "\n\tString #" << lineNum << endl;
			lineToLists(line, pointerCollector);
		}
		cout.rdbuf(coutbuf);
		if(lineNum == 1) error(7); else cout << "Results are saved in HLists.txt file." << endl;
	}else error(6);
	for(int i=0; i<pointerCollector.size(); i++) delete pointerCollector[i];
	return 0;
}

void lineToLists(string& line, vector<Elem*>& pointerCollector){
	string line1, line2;
	int i;
	if(splitString(line, line1, line2) == 0) error(1);
	else {
		Elem* hList1 = new Elem;
		pointerCollector.push_back(hList1);
		Elem* hList2 = new Elem;
		pointerCollector.push_back(hList2);
		cout << "=======\nList #1:" << endl;
		hList1 = getHList(line1, i=0, hList1, pointerCollector);
		if(hList1 == NULL) error(8);
		cout << "=======\nList #2:" << endl;
		hList2 = getHList(line2, i=0, hList2, pointerCollector);
		if(hList2 == NULL) error(9);
		cout << "=======" << endl;
		if((hList1 == NULL)||(hList2 == NULL)) cout << "Lists are not comparable." << endl;
		else if(equalLists(hList1, hList2)) cout << "Lists are equal." << endl; else cout << "Lists are NOT equal." << endl;
	}
}

bool splitString(string &line, string &line1, string &line2){
    string delimiter = " ";
    int delimiterIndex = line.find(delimiter);
    if(delimiterIndex <= 0) return false;
    line1 = line.substr(0, delimiterIndex);
    line2 = line.substr(delimiterIndex+1, line.length());
    return true;
}

Elem* getHList(string line, int& i, Elem* hListHead, vector<Elem*>& pointerCollector, int depth){
	if(line[i] == '('){
		Elem* hListLocalTail = new Elem;
		pointerCollector.push_back(hListLocalTail);
		hListHead->child = hListLocalTail;
		if(depth != 0) recursionDepth(0, depth, true);
		for(++i; ((i < line.length())&&(line[i] != ')')); i++){
		    Elem* hListBlank = new Elem;
			pointerCollector.push_back(hListBlank);
			if(isData(line[i])){
				setData(hListLocalTail, line[i]);
				recursionDepth(line[i], depth);
			}
			else if(line[i] == '('){
			    if(getHList(line, i, hListLocalTail, pointerCollector, depth+1) == NULL) return NULL;
			}
			else return error(3);    
			push(hListLocalTail, hListBlank);
		}
		if(i == line.length()) return error(4);
		if((depth == 0)&&(i+1 < line.length())) return error(5);
		vector<char> dataCollector;
		if(isUniqueData(hListHead, dataCollector) == 0) return error(11);
		return hListHead;	
	} 
	return error(2);
}

bool equalLists(Elem* hList1, Elem* hList2){
	if(hList1->data != hList2->data) return false;
	if((hList1->child != NULL)^(hList2->child != NULL)) return false;
	if((hList1->tail != NULL)^(hList2->tail != NULL)) return false;
	if((hList1->child != NULL)&&(hList2->child != NULL)) if (equalLists(hList1->child, hList2->child) == 0) return false;
	if((hList1->tail != NULL)&&(hList2->tail != NULL)) if (equalLists(hList1->tail, hList2->tail) == 0) return false;
	return true;
}

void recursionDepth(char s, int n, bool sublist){
	for(int i=0; i<n; i++) cout << "\t";
	if(sublist) cout << "Sublist:" << endl; else cout << "Symbol: " << s << "\tdepth: " << n << endl;
	return;
}

bool isData(char c){
	return ((c>=48)&&(c<=57))||((c>=65)&&(c<=90))||((c>=97)&&(c<=122));
}

void push(Elem*& hListHead, Elem* hListTail){
    hListHead->tail = hListTail;
    hListHead = hListTail;
    return;
}

void setData(Elem* hListElem, char data){
    hListElem->dataTag = 1;
    hListElem->data = data;
    return;
}

bool isUniqueData(Elem* hList, vector<char>& dataCollector){
	if(hList->dataTag){
		for(int i=0; i<dataCollector.size(); i++) if(dataCollector[i] == hList->data) return false;
		dataCollector.push_back(hList->data);
	}
	if(hList->child != NULL) if(isUniqueData(hList->child, dataCollector) == false) return false;
	if(hList->tail != NULL) if(isUniqueData(hList->tail, dataCollector) == false) return false;
	return true;
}

Elem* error(int n){
	cout << "Error!\t";
 	switch (n){
  		case 0: cout << "Empty string." << endl; break;
		case 1: cout << "Incorrect list string. Need 2 lists separated by space." << endl; break;
		case 2: cout << "Expected \'(\' symbol." << endl; break;
		case 3: cout << "Non-permitted symbol is string. Permitted symbols for list are: [A-Za-z0-9()]." << endl; break;
		case 4: cout << "Expected \')\' symbol." << endl; break;
		case 5: cout << "Unexpected sequence after brackets." << endl; break;
		case 6: cout << "Incorrect input arguments. Write file path or two hierarchical lists." << endl; break;
		case 7: cout << "Empty file." << endl; break;
		case 8: cout << "List #1 has incorrect syntax." << endl; break;
		case 9: cout << "List #2 has incorrect syntax." << endl; break;
		case 10: cout << "File not found." << endl; break;
		case 11: cout << "List must have unique data." << endl; break;
 	};
	return NULL;
}
