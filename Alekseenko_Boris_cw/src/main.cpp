#include "AVL_tree.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

vector<int> avl_insert_generator(int size, char c){
	vector<int> avl_tree;
	if (c == 'w') {
		int m = rand();
		for (int i = m; i < m + size; i++) {
			avl_tree.push_back(i);
		}
	}
	else if (c == 'a') {
		for (int i = 0; i < size; i++) {
			avl_tree.push_back(rand());
		}
	}
	return avl_tree;
}

void avl_tree_generator_average(Head_AVL_Tree<int>* head, vector<int>& the_ones, vector<int>& avl_tree, int size) {
	for (int i = 0; i < size; i++)
	{
		int elem = rand();
		head->insert(elem);
		avl_tree.push_back(elem);
	}

	std::cout << avl_tree.size() << endl;
	for (int i = 0; i < size / 2; i++)
	{
		int itr = rand() % avl_tree.size();
		std::cout << "Iter - " << itr << endl;
		the_ones.push_back(avl_tree[itr]);
	}

}

void avl_tree_generator_worst(Head_AVL_Tree<int>* head, vector<int>& the_ones, vector<int>& avl_tree, int size) {
	int m = rand() % size;
	for (int i = m; i < size + m; i++) {
		head->insert(i);
		avl_tree.push_back(i);
	}

	std::cout << avl_tree.size() << endl;
	for (int i = 0; i < size / 2; i++)
	{
		int itr = rand() % avl_tree.size();
		if (itr > avl_tree.size()) {
			i--;
			continue;
		}

		std::cout << "Iter - " << itr << endl;
		the_ones.push_back(avl_tree[itr]);
	}

}

int main(int argc, char* argv[]) {


	srand(static_cast<unsigned int>(time(0)));

	std::cout << "Which operation you want to research? [Delete - d / Insert - i]" << endl;

	char operation = 'd';
	if(argc > 1)
		operation = *argv[1];
	//cin >> operation;

	if (operation == 'd')
	{

		std::cout << "What case do you want to consider?[w - worst / a - average]" << endl;
		char choice = 'w';

		if(argc > 2)
			choice = *argv[2];
		//cin >> choice;

		if (choice == 'w') {

			int size = 1;							// ���������� ���������.
			int iter = 0;

			while (size <= 10000)
			{
				ofstream fout;
				std::string file = "result_d_w/result_w_";
				std::string num = to_string(iter);
				file.append(num);
				file.append(".txt");
				fout.open(file, std::fstream::trunc | std::fstream::out);

				Head_AVL_Tree<int>* head = new Head_AVL_Tree<int>;
				vector<int> the_ones;
				vector<int> avl_tree;
				avl_tree_generator_worst(head, the_ones, avl_tree, size);

				fout << size << " ";

				for (int i = 0; i < the_ones.size(); i++)
				{
					if (head->is_contain(the_ones[i])) {
						if (i != 0) {
							fout << " ";
						}
						head->reset_o();
						head->remove(the_ones[i]);
						fout << head->get_o() - 2;
						head->insert(rand() % size);
					}
				}

				fout << endl;
				fout << endl;

				if (size == 1) {
					size += 49;
				}
				else
				{
					size += 50;
				}
				iter++;
				delete head;
				fout.close();
			}
		}

		else if (choice == 'a') {
			int size = 1;
			int iter = 0;


			while (size <= 10000)
			{
				ofstream fout;
				std::string file = "result_d_a/result_a_";
				std::string num = to_string(iter);
				file.append(num);
				file.append(".txt");
				fout.open(file, std::fstream::trunc | std::fstream::out);

				Head_AVL_Tree<int>* head = new Head_AVL_Tree<int>;

				vector<int> the_ones;
				vector<int> avl_tree;

				avl_tree_generator_average(head, the_ones, avl_tree, size);

				fout << size << " ";

				for (int i = 0; i < the_ones.size(); i++)
				{
					if (head->is_contain(the_ones[i])) {
						if (i != 0) {
							fout << " ";
						}
						head->reset_o();
						head->remove(the_ones[i]);
						fout << head->get_o() - 2;
						head->insert(rand());
					}
				}
				fout << endl;
				fout << endl;

				if (size == 1) {
					size += 49;
				}
				else
				{
					size += 50;
				}

				iter++;
				delete head;
				fout.close();
			}
		}
	}
	else if(operation == 'i'){
		std::cout << "What case do you want to consider?[w - worst / a - average]" << endl;
		//cin >> choice;
		char choice = 'w';
		if(argc > 2)
			choice = *argv[2];

		if (choice == 'w') {

			int size = 1;							// ���������� ���������.
			int iter = 0;

			while (size <= 10000)
			{
				ofstream fout;
				std::string file = "result_i_w/result_w_";
				std::string num = to_string(iter);
				file.append(num);
				file.append(".txt");
				fout.open(file, std::fstream::trunc | std::fstream::out);

				Head_AVL_Tree<int>* head = new Head_AVL_Tree<int>;
				vector<int> avl_tree;
				vector<int> the_ones;
				avl_tree_generator_worst(head, the_ones, avl_tree, size);
				avl_tree = avl_insert_generator(size, 'w');

				fout << size << " ";

				for (int i = 0; i < avl_tree.size(); i++)
				{
					 	if (i != 0) {
						 	fout << " ";
					  }
						head->reset_o();
						head->insert(avl_tree[i]);
						fout << head->get_o() - 2;
						head->remove(head->get_head()->get_d());
				}

				fout << endl;
				fout << endl;

				if (size == 1) {
					size += 49;
				}
				else
				{
					size += 50;
				}
				iter++;
				delete head;
				fout.close();
			}
		}

		else if (choice == 'a') {
			int size = 1;
			int iter = 0;

			while (size <= 10000)
			{
				ofstream fout;
				std::string file = "result_i_a/result_a_";
				std::string num = to_string(iter);
				file.append(num);
				file.append(".txt");
				fout.open(file, std::fstream::trunc | std::fstream::out);

				Head_AVL_Tree<int>* head = new Head_AVL_Tree<int>;

				vector<int> the_ones;
				vector<int> avl_tree;

				avl_tree_generator_average(head, the_ones, avl_tree, size);
				avl_tree = avl_insert_generator(size, 'w');

				fout << size << " ";

				for (int i = 0; i < avl_tree.size(); i++)
				{
					if (i != 0) {
						fout << " ";
					}
					head->reset_o();
					head->insert(avl_tree[i]);
					fout << head->get_o() - 2;
					head->remove(head->get_head()->get_d());
				}

				if (size == 1) {
					size += 49;
				}
				else
				{
					size += 50;
				}

				iter++;
				delete head;
				fout.close();
			}
		}
	}

	std::cout << "Finished right" << endl;
	return 0;
}
