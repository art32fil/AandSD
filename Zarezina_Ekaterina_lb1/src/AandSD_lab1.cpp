#include <iostream>
#include <string>
#include <vector>
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

string spacesFree(string expression){
	int startExp = 0;
	int endExp = 0;
	string spacesFree = "";
	while(startExp<expression.length() && expression[startExp] == ' '){
		startExp++;
	}
	while(endExp>expression.length()-1 && expression[endExp] == ' '){
		endExp++;
	}
	for(int i = startExp; i<endExp+1; i++){
		spacesFree += expression[i];
	}
}
 

Recursion simplExpr(string expression, int recLevel){
	recLevel++;
	createTabs(recLevel);
	cout<<"Entered string: "<<expression<<endl;
	int resize = recLevel+1;
	expression = spacesFree(expression);
	if((expression == "TRUE")||(expression == "FALSE")){
		return NEXT_LEVEL;
	} else if(expression == "NOT"){
		cin >> expression;
		createTabs(recLevel);
		cout<<"Checking for simple expression"<<endl;
		Recursion callRec = simplExpr(expression, recLevel);
		if(callRec == Recursion::NEXT_LEVEL){
			//expression.resize(resize);
			if(expression == "TRUE"){
				cout<<"It was !TRUE\n\tnow it's FALSE"<<endl;
				expression = "FALSE";
			} else {
				cout<<"It was !FALSE\n\tnow it's TRUE"<<endl;
				expression = "TRUE";
			}
			createTabs(recLevel);
			cout<<"Found a simple expression"<<endl;
		}
		return NEXT_LEVEL;
	} else {
		cout<<"Wrong expression!"<<endl;
		return STOP_REC;
	}
}

/*Recursion simplExprFile(string expression, FILE* file, int recLevel){
	recLevel++;
	createTabs(recLevel);
	cout<<"Entered string: "<<sym<<endl;
	int resize = recLevel+1;
	expression = spacesFree(expression);

	if((expression == "TRUE")||(expression == "FALSE")){
		return NEXT_LEVEL;
	} else if(expression == "NOT"){
		cin >> expression;
		createTabs(recLevel);
		cout<<"Checking for simple expression"<<endl;
		Recursion callRec = simplExpr(expression, recLevel);
		if(callRec == Recursion::NEXT_LEVEL){
			//expression.resize(resize);
			if(expression == "TRUE"){
				cout<<"It was !TRUE\n\tnow it's FALSE"<<endl;
				expression = "FALSE";
			} else {
				cout<<"It was !FALSE\n\tnow it's TRUE"<<endl;
				expression = "TRUE";
			}
			createTabs(recLevel);
			cout<<"Found a simple expression"<<endl;
		}
		return NEXT_LEVEL;
	} else {
		cout<<"Wrong expression!"<<endl;
		return STOP_REC;
	}
}*/

int main(){
	int recLevel = -1;
	cout<<"Select the text input method:\n\tc - console\n\tt - text from file\nYour choice: ";
	char way;
	way = getchar();
	cout<<"You choose: "<<way<<endl;
	if(way == 'c'){
		string expression;
		cout<<"Enter an expression: ";
		cin >> expression;
		Recursion callRec;
		callRec = simplExpr(expression, recLevel);
		if((callRec == Recursion::NEXT_LEVEL)&&((expression) == "\n")){
			cout<<"Successfull"<<endl;
		} else if (callRec == Recursion::NEXT_LEVEL){
			cout<<"ERROR: extra chars"<<endl;
		}
	} else if(way == 't') {
		string fileName;
		cout<<"Enter a file name: "<<endl;
		getline(cin, fileName);
		cout<<"Your fileName - "<<fileName<<endl;
		ifstream file(fileName);

		if(!file){
			cout<<"NO file"<<endl;
			return 0;
		} else {
			cout<<"File!"<<endl;
			
		}
	}
}
