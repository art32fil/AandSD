#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cmath>
#include <iostream>
#include <fstream>

#define SIZE 100 

using namespace std;

namespace BT{

//Node----------------------------------

template<typename T>
struct Node{
public:
	Node<T>* left;
	Node<T>* right;
	Node();
	void print(ofstream* outfile);
	void read(ifstream* infile);
	T getData();
private:
	T data;
};

template<typename T>
Node<T>::Node() : left(nullptr), right(nullptr) {}

template<typename T>
void Node<T>::print(ofstream* outfile){
	std::cout << "[" << this->data << "]";
	(*outfile) << "[" << this->data << "]";
}

template<typename T>
T Node<T>::getData(){
	return this->data;
}

template<typename T>
void Node<T>::read(ifstream* infile){
	T tmp;
	(infile->is_open() ? *infile : std::cin) >> tmp;
	cout << tmp;//
	this->data = tmp;
}

//pair---------------------

template<typename T>
class Pair{
public:
	Node<T>* ptr;
	int level;
	Pair(Node<T>* ptr, int level) : ptr(ptr) , level(level) {}
	Pair() {}
};

//customQueue--------------------

template<typename T>
struct CustomQueue{
public:
	CustomQueue(ofstream* pointer);
	void push(Pair<T>);
	Pair<T> pop();
	bool empty();
	bool full();
	void clear();
	void pushTree(Node<T>*, int);
	void print();
	int size();
private:
	Pair<T> array[SIZE];
	int start; //первый незаполненный
	int end; //последний заполненный
	int length;
	ofstream* outfile;
};

template<typename T>
CustomQueue<T>::CustomQueue(ofstream* pointer) : start(0), end(0), length(0), outfile(pointer) {}

template<typename T>
void CustomQueue<T>::clear(){
	start = 0;
	end = 0;
	length = 0;
}

template<typename T>
bool CustomQueue<T>::full(){
	return (length == SIZE);
}

template<typename T>
bool CustomQueue<T>::empty(){
	return (!length);
}

template<typename T>
int CustomQueue<T>::size(){
	return length;
}

template<typename T>
void CustomQueue<T>::push(Pair<T> element){
	if(this->full()){
		std::cout << "Attempt to push to the full queue rejected. Exiting...\n";
		exit(1);
	}
	array[start] = element;
	start = (start + 1) % SIZE;
	++length;
}

template<typename T>
Pair<T> CustomQueue<T>::pop(){
	if(this->empty()){
		std::cout << "Tried to pop from the empty queue. Exiting...\n";
		exit(1);
	}
	--length;
	int tmp = end;
	end = (end + 1) % SIZE;
	return array[tmp];
}

template<typename T>
void CustomQueue<T>::pushTree(Node<T>* root, int level){
	CustomQueue<T>* tmp = new CustomQueue(nullptr);

	int counter = 0;
	int length;
	Pair<T> pair;
	pair.ptr = root;
	pair.level = counter;
	tmp->push(pair);
	while(!tmp->empty()){
		++counter;
		length = tmp->size();
		for(int i = 0; i < length; ++i){
			pair = tmp->pop();
			this->push(pair);
			if(pair.ptr->left) tmp->push(Pair<T>(pair.ptr->left , counter));
			if(pair.ptr->right) tmp->push(Pair<T>(pair.ptr->right , counter));
		}
	}
	delete tmp;
}

template<typename T>
void CustomQueue<T>::print(){
	if(this->empty()) return;
	Pair<T> elem;
	int width = 4*ceil((this->length)/2) - 1 + 9;
	Pair<T> prev = this->pop();
	std::cout << "Level " << prev.level << ": ";
	(*outfile) << "Level " << prev.level << ": ";
	prev.ptr->print(outfile);
	while(!this->empty()){
		elem = this->pop();
		if(elem.level > prev.level){
			std::cout << "\n";
			(*outfile) << '\n';
			for(int i = 0; i < width; ++i) {std::cout << "-"; (*outfile) << "-";}
			std::cout << '\n';
			(*outfile) << '\n';
			std::cout << "Level " << elem.level << ": ";
			(*outfile) << "Level " << elem.level << ": ";
		}
		elem.ptr->print(outfile);
		prev = elem;
	}
}

//tree-----------------------------

template<typename T>
struct BinTree{
public:
	BinTree(ofstream* ptr);
	void read(ifstream* infile);
	void reset();
	Node<T>* root();
private:
	Node<T> array[SIZE];
	int top;
	ofstream* outfile;
};

template<typename T>
BinTree<T>::BinTree(ofstream* ptr): top(0), outfile(ptr) {}

template<typename T>
void BinTree<T>::reset(){
	top = 0; 
	for(int i = 0; i < SIZE; ++i) array[i] = Node<T>();
}

template<typename T>
Node<T>* BinTree<T>::root(){
	return array;
}

template<typename T>
void BinTree<T>::read(ifstream* infile){
	char chr;
	array[top].read(infile);
	(*outfile) << array[top].getData();
	int tmp = top;
	(infile->is_open() ? *infile : std::cin) >> chr;
	if( (infile->is_open() && infile->eof()) || (!(infile->is_open())) && cin.eof()){
		cout << "\b";
		exit(0);
	}
	switch(chr){
	case '(':
		cout << '('; (*outfile) << '(';
		(infile->is_open() ? *infile : std::cin) >> chr;
		switch(chr){
		case ' ':
			cout << ' '; (*outfile) << ' ';
			break;
		case ')':
			std::cout << chr << " <- ERROR\n";
			(*outfile) << chr << " <- ERROR" << endl;
			exit(1);
		default:
			(infile->is_open() ? *infile : std::cin).unget();
			++top;
			array[tmp].left = array + top;
			this->read(infile);
		}
		(infile->is_open() ? *infile : std::cin) >> chr;
		switch(chr){
		case '(':
			std::cout << chr << " <- ERROR\n";
			(*outfile) << chr << " <- ERROR" << endl;
			exit(1);
		case ')':
			std::cout << ')'; (*outfile) << ')';
			break;
		case ' ':
			std::cout << chr << " <- ERROR\n";
			(*outfile) << chr << " <- ERROR" << endl;
                        exit(1);
		default:
			(infile->is_open() ? *infile : std::cin).unget();
			++top;
			array[tmp].right = array+top;
			read(infile);
			//считать оставшуюся скобку?
			(infile->is_open() ? *infile : std::cin) >> chr;
			if(chr != ')'){
				std::cout << chr;
				std::cout << " <- ERROR\n";
				(*outfile) << chr << " <- ERROR" << endl;
				exit(1);
			}
			cout << ')'; (*outfile) << ")";
		}
	break;
	case'\n':
		(infile->is_open() ? *infile : std::cin).unget();
		//infile->is_open() ? std::cin : std::cin.unget();
	return;
	default:
		(infile->is_open() ? *infile : std::cin).unget();
	}
}

}

#endif
