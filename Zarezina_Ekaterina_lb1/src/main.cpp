
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#define BUFF 40

using namespace std;

enum Recursion{
	NEXT_LEVEL,
	STOP_REC,
};

enum BoolExpression{
	BOOL_TRUE,
	BOOL_FALSE,
	BOOL_NOT,
	BOOL_AND,
	BOOL_OR,
	OTHER,
};


void createTabs (int recLevel){
	for(int i = 0; i<recLevel; i++){
		cout<<"\t";
	}
}

BoolExpression resSimplExpr(stringstream& myExpr, string atom){
	if(atom == "TRUE"){
		return BOOL_TRUE;
	} else if(atom == "FALSE"){
		return BOOL_FALSE;
	} else if(atom == "NOT"){
		myExpr>>atom;
		BoolExpression callRec = resSimplExpr(myExpr,atom);
		if(callRec == BoolExpression::BOOL_TRUE){
			return BOOL_FALSE;
		} else if(callRec == BoolExpression::BOOL_FALSE){
			return BOOL_TRUE;
		}
	} else if(atom == "("){
		BoolExpression flag;
		myExpr>>atom;
		BoolExpression bool1 = resSimplExpr(myExpr,atom);
		myExpr>>atom;
		if(atom == "OR"){
			flag = BoolExpression::BOOL_OR;
		} else if (atom == "AND") {
			flag = BoolExpression::BOOL_AND;
		}
		myExpr>>atom;
		BoolExpression bool2 = resSimplExpr(myExpr,atom);
		myExpr>>atom;
		if(flag == BoolExpression::BOOL_OR){
			if((bool1 == BoolExpression::BOOL_FALSE )&&(bool2 == BoolExpression::BOOL_FALSE)){
				return BoolExpression::BOOL_FALSE;
			} else {
				return BoolExpression::BOOL_TRUE;
			}
		} else if (flag == BoolExpression::BOOL_AND){
			if((bool1 == BoolExpression::BOOL_TRUE )&&(bool2 == BoolExpression::BOOL_TRUE)){
				return BoolExpression::BOOL_TRUE;
			} else {
				return BoolExpression::BOOL_FALSE;
			}
		}
	}
  return BoolExpression::OTHER;
}


Recursion simplExpr(stringstream& myExpr, string atom, int recLevel){
	recLevel++;
	createTabs(recLevel);
	if((atom == "TRUE")||(atom == "FALSE")){
		return NEXT_LEVEL;
	} else if(atom == "NOT"){
		myExpr>>atom;
		createTabs(recLevel);
		cout<<"Checking for simple expression"<<endl;
		Recursion callRec = simplExpr(myExpr,atom, recLevel);
		if(callRec == Recursion::STOP_REC){
			cout<<"Something went wrong!"<<endl;
			return STOP_REC;
		} else {
			createTabs(recLevel);
			cout<<"Found a simple expression"<<endl;
			return NEXT_LEVEL;
		}

	} else if(atom == "("){
		cout<<"Checking for first simple expression"<<endl;
		myExpr>>atom;
		Recursion callRec = simplExpr(myExpr,atom,recLevel);
		if(callRec == Recursion::NEXT_LEVEL){
			createTabs(recLevel);
			cout<<"Found first simple expression"<<endl;
			createTabs(recLevel);
			cout<<"Checking for OR or AND"<<endl;
			myExpr>>atom;
			if((atom == "OR")||(atom == "AND")){
				createTabs(recLevel);
				cout<<"Found OR or AND"<<endl;
				createTabs(recLevel);
				cout<<"Checking for second simple expression"<<endl;
				myExpr>>atom;
				Recursion callRec = simplExpr(myExpr,atom,recLevel);
				if(callRec == Recursion::NEXT_LEVEL){
					createTabs(recLevel);
					cout<<"Found second simple expression"<<endl;
					createTabs(recLevel);
					cout<<"Checking for last bracket"<<endl;
					myExpr>>atom;
					if(atom==")"){
						createTabs(recLevel);
						cout<<"Found last bracket"<<endl;
						return NEXT_LEVEL;
					} else {
						createTabs(recLevel);
						cerr<<"NO last bracket!\n";
						exit(1);
					}
				} else {
					createTabs(recLevel);
					cerr<<"NO second simple expression!\n";
					exit(1);
				}
			} else {
				createTabs(recLevel);
				cerr<<"NO OR or AND!\n";
				exit(1);
			}
		} else {
			createTabs(recLevel);
			cerr<<"NO first simple expression!\n";
			exit(1);
		}

	} else {
		cerr<<"Wrong expression!";
		exit(1);
	}
}


int main(){
	int recLevel = -1;
	stringstream myExpr;
	stringstream myExpr2;
	string atom;
	string inputLine;
	string inputLineCopy;
	cout<<"Select the text input method:\n\t1 - console\n\t2 - text from file\nYour choice: "<<endl;
	char way;
	string c;
	cin>>way;
	cout<<"your choice: "<<way<<endl;
	getline(cin,c);
	if(way == '1'){
		cout<<"Enter an expression: "<<endl;
		getline(cin,inputLine);
	} else if(way == '2'){
		string fileName;
		cout<<"Enter a file name: "<<endl;
		getline(cin, fileName);
		ifstream fin (fileName);
		if(fin){
			getline(fin, inputLine);
			cout<<"InputLine from file: "<<inputLine<<endl;
		} else {
			cerr<<"File couldn't be open!\n";
			exit(1);
		}
	}
	inputLineCopy = inputLine.substr();
	cout<<"Input line: "<<inputLine<<endl;
	myExpr<<inputLine;
	myExpr>>atom;
	Recursion callRec = simplExpr(myExpr,atom,recLevel);
	if(callRec == Recursion::NEXT_LEVEL){
		cout<<"It's right expression!"<<endl;
		myExpr2<<inputLineCopy;
		myExpr2>>atom;
		BoolExpression boolRec = resSimplExpr(myExpr2, atom);
		if(boolRec == BoolExpression::BOOL_TRUE){
			cout<<"Result: TRUE"<<endl;
		} else if (boolRec == BoolExpression::BOOL_FALSE){
			cout<<"Result: FALSE"<<endl;
		}
	} else {
		cout<<"It's not an expression!"<<endl;
	}
	
	return 0 ;
}

