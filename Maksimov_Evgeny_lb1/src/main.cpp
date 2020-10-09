#include <iostream>
#include <fstream>
using namespace std;

bool bracket(string line);
bool round(string line, int* i, int depth);
bool square(string line, int* i, int depth);
bool figure(string line, int* i, int depth);
bool error(int n);
void recursionDepth(char s, int n);

int main(int argc, char *argv[]){
	if(argc==1){
		cout << "Write input bracket: " << endl;
		string line;
		cin >> line;
		if(bracket(line)) cout << line << " is a bracket." << endl; else cout << line << " is NOT a bracket." << endl;
	}else if(argc==2){
		string line(argv[1]);
		ifstream in(line);
		if(!in){
			cout << "File not found!" << endl;
			return 0;
		}

		ofstream out("BracketsOut.txt");
    	streambuf *coutbuf = cout.rdbuf();
    	cout.rdbuf(out.rdbuf());
		int lineNum = 1;
		for(lineNum; getline(in, line); lineNum++){
			cout << "String #" << lineNum << endl;
			if(bracket(line)) cout << line << " is a bracket.\n" << endl; else cout << line << " is NOT a bracket.\n" << endl;
		}

		cout.rdbuf(coutbuf);
		if(lineNum == 1) cout << "Empty file!" << endl; else cout << "Results saved in BracketsOut.txt file." << endl;

	}else cout << "Incorrect input arguments." << endl;
	return 0;
}

bool bracket(string line){
	int i = 0;
	bool b = false;
	int depth = 0;
	
	if(line[0] == '\n' || line[0] == '\0') return error(0);
	if ((line[i] == '+') || (line[i] == '[')) b = square(line, &i, depth);
	else if ((line[i] == '-') || (line[i] == '(')) b = round(line, &i, depth);
	else if ((line[i] == '0') || (line[i] == '{')) b = figure(line, &i, depth);
	else return error(1);

	if(b && (i+1 < line.length())) return error(2);
	return (b && (i+1 == line.length()));
}

bool round(string line, int* i, int depth){
	bool k;
	recursionDepth(line[*i], depth);
	if(line[*i] == '-') return true;
	else if(line[*i] == '('){
		if(++(*i) < line.length()){
			k = figure(line, i, depth+1);
			if(k){
				if(++(*i) < line.length()){
					k = square(line, i, depth+1);
				}else return error(6);
			}else return false;

			if(k){
				if(++(*i) < line.length()){
					recursionDepth(line[*i], depth);
					return (line[*i] == ')');
				}else return error(5);
			}else return false;
		}else return error(7);
	}else return error(8);
}

bool square(string line, int* i, int depth){
	bool k;
	recursionDepth(line[*i], depth);
	if(line[*i] == '+') return true; 
	else if(line[*i] == '['){
		if(++(*i) < line.length()){
			k = round(line, i, depth+1); 
			if(k){
				if(++(*i) < line.length()){
					k = figure(line, i, depth+1);
				}else return error(7);
			}else return false;
			
			if(k){
				if(++(*i) < line.length()){
					recursionDepth(line[*i], depth);
					return (line[*i] == ']');
				}else return error(3);
			}else return false;
		}else return error(8);
	}else return error(6);
}

bool figure(string line, int* i, int depth){
	bool k;
	recursionDepth(line[*i], depth);
	if (line[*i] == '0') return true;
	else if(line[*i] == '{'){
		if(++(*i) < line.length()){
			k = square(line, i, depth+1); 
			if(k){
				if(++(*i) < line.length()){
					k = round(line, i, depth+1);
				}else return error(8);
			}else return false;

			if(k){
				if(++(*i) < line.length()){
					recursionDepth(line[*i], depth);
					return (line[*i] == '}');
				}else return error(4);
			}else return false;
		}else return error(6);
	}else return error(7);
}

bool error(int n){
	cout << "Error!\t";
 	switch (n){
  		case 0: cout << "Empty string." << endl; break;
		case 1: cout << "Non-permitted symbol." << endl; break;
		case 2: cout << "Unexpected sequence." << endl; break;
		case 3: cout << "Expected ']' symbol." << endl; break;
		case 4: cout << "Expected '}' symbol." << endl; break;
		case 5: cout << "Expected ')' symbol." << endl; break;
		case 6: cout << "Expected '+' or '[' symbol." << endl; break;
		case 7: cout << "Expected '0' or '{' symbol." << endl; break;
		case 8: cout << "Expected '-' or '(' symbol." << endl; break;
 	};
	return false;
}

void recursionDepth(char s, int n){
	cout << "Symbol: " << s << "\tRecursion depth is: " << n << endl;
	return;
}