#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

//счётчик для количества итераций
int iterations = 0;

//структура дерева
struct Node {
	int key;
	int size;
	Node* left;
	Node* right;
	Node(int k) {
		key = k;
		left = right = nullptr;
		size = 1;
	}
};

int getsize(Node* btree) {
	if (!btree) return 0;
	return btree->size;
}

int fixsize(Node* btree) {
	return btree->size = getsize(btree->left) + getsize(btree->right) + 1;
}

//функция для подсчёта максимальной высоты дерева
int height(Node* btree){
	Node *temp = btree;
	int h1 = 0, h2 = 0;
	if (btree == NULL)return(0);
	if (btree->left) { h1 = height(btree->left); }
	if (btree->right) { h2 = height(btree->right); }
	return (max(h1, h2) + 1);
}

//функция для нахождения элемента дерева
Node* find(Node* btree, int key){
	if (!btree) {
		iterations++;
		return 0;
	}
	if (key == btree->key) {
		iterations++;
		return btree;
	}
	if (key < btree->key) {
		iterations++;
		return find(btree->left, key);
	}
	else {
		iterations++;
		return find(btree->right, key);
	}
}

//функция для классической вставки элемента в БДП
Node* usual_insert(Node* btree, int k){
	if (!btree) {
		iterations++;
		return new Node(k);
	}
	if (btree->key > k) {
		iterations++;
		btree->left = usual_insert(btree->left, k);
	}
	else {
		iterations++;
		btree->right = usual_insert(btree->right, k);
	}
	fixsize(btree);
	return btree;
}

//функция для поворота вправо поддерева
Node* rotateright(Node* btree) {
	iterations++;
	//cout << "rotate R " << iterations << endl;
	Node* newbtree = btree->left;
	if (!newbtree) return btree;
	btree->left = newbtree->right;
	newbtree->right = btree;
	newbtree->size = btree->size;
	fixsize(btree);
	return newbtree;
}

//функция для поворота влево поддерева
Node* rotateleft(Node* btree) {
	iterations++;
	//cout << "rotate L " << iterations << endl;
	Node* newbtree = btree->right;
	if (!newbtree) return btree;
	btree->right = newbtree->left;
	newbtree->left = btree;
	newbtree->size = btree->size;
	fixsize(btree);
	return newbtree;
}

//функция для вставки в корень элемента дерева
Node* insertroot(Node* btree, int k) {
	if (!btree) {
		iterations++;
		//cout << "root new" << iterations << endl;
		return new Node(k);
	}
	if (k < btree->key) {
		iterations++;
		//cout << "root left " << iterations << endl;
		btree->left = insertroot(btree->left, k);
		return rotateright(btree);
	}
	else {
		iterations++;
		//cout << "root right " << iterations << endl;
		btree->right = insertroot(btree->right, k);
		return rotateleft(btree);
	}
}

//функция для вывода дерева, повёрнутого на 90 градусов против часовой стрелки
void Print(Node* btree, int level) {
	if (btree->right != nullptr) {
		Print(btree->right, level + 1);
	}
	for (int i = 0; i < level; i++) {
		cout << "    ";
	}
	cout << btree->key << "\n";
	if (btree->left != nullptr) {
		Print(btree->left, level + 1);
	}
}

//функция вставки элемента в рандомизированное дерево
Node* insert(Node* btree, int k) {
	if (!btree) {
		iterations++;
		//cout << "new " << iterations << endl;
		return new Node(k);
	}
	if (rand() % (btree->size + 1) == 0) {
		//cout << "Вставка в корень значения " << k << endl;
		btree = insertroot(btree, k);
		//Print(btree, 0);
		//cout << endl;
		return btree;
	}
	if (btree->key > k){
		iterations++;
		//cout << "left " << iterations << endl;
		btree->left = insert(btree->left, k);
	}		
	else{
		iterations++;
		//cout << "right " << iterations << endl;
		btree->right = insert(btree->right, k);
	}
	fixsize(btree);
	return btree;
}

//функция для объеденения двух поддеревьев
Node* join(Node* btree1, Node* btree2) {
	if (!btree1) {
		iterations++;
		//cout << "no left " << iterations << endl;
		return btree2;
	}
	if (!btree2) {
		iterations++;
		//cout << "no right " << iterations << endl;
		return btree1;
	}
	if (rand() % (btree1->size + btree2->size) < btree1->size) {
		iterations++;
		//cout << "right join " << iterations << endl;
		btree1->right = join(btree1->right, btree2);
		fixsize(btree1);
		return btree1;
	}
	else {
		iterations++;
		//cout << "left join " << iterations << endl;
		btree2->left = join(btree1, btree2->left);
		fixsize(btree2);
		return btree2;
	}
}

//функция для удаления элемента из дерева
Node* remove(Node* btree, int k) {
	if (!btree) {
		iterations++;
		//cout << "this " << iterations << endl;
		return btree;
	}
	if (btree->key == k) {
		Node* newbtree = join(btree->left, btree->right);
		delete btree;
		return newbtree;
	}
	else if (k < btree->key) {
		iterations++;
		//cout << "left " << iterations << endl;
		btree->left = remove(btree->left, k);
	}
	else {
		iterations++;
		//cout << "right " << iterations << endl;
		btree->right = remove(btree->right, k);
	}
	return btree;
}

//функция генерации элементов для среднего случая
vector<int> generate_average(int n) {
	vector<int> values;
	for (int i = 0; i < n; i++) {
		int value = rand () %10000;
		values.push_back(value);
	}
	if(n > 2){
		int count1 = 0;
		int count2 = 0;
		for (int i = 0; i < n; i++) {
			if (values[i] < values[i + 1] || values[i] == values[i + 1]) count1++;
			if (values[i] > values[i + 1] || values[i] == values[i + 1]) count2++;
		}
		if (count2 == n  || count1 == n) generate_average(n); //ликвидация создания худшего случая
		else return values;
	}
	return values;
}

//функция генерации элементов для худшего случая
vector<int> generate_worst(int n) {
	vector<int> values;
	for (int i = 0; i < n; i++) {
		int value = rand() % 10000;
		values.push_back(value);
	}
	int chance = rand() % 2; //устанавливается вероятность генерации по возрастанию и убыванию
	if (chance == 0) sort(values.begin(), values.end());
	if (chance == 1) sort(values.begin(), values.end(), greater<int>());
	return values;
}

//функция для работы со сгенерированными деревьями
void function_for_bst(string generation, Node* tree, Node* newtree) {
	srand(time(0));
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3; //используются для подсчёта времени выполнения операций
	int value; //используется для ввода нового значения
	string operation; //используется для выбора операции
	string menu_for_value;
	while (generation == "y" || generation == "yes") {
		iterations = 0;
		cout << "Выберите действие, которое хотите осуществить:\n0. Создание нового дерева.\n1. Поиск элемента.\n2. Вставка элемента.\n3. Удаление элемента.\n";
		cout << "Действие: ";
		cin >> operation;
		if (operation == "0") break;
		else if (operation == "1") { //поиск элемента и анализ
			cout << "Выберите действие, которое хотите осуществить:\n1. Выбрать значение.\n2.Сгенерировать значение.\n";
			cout << "Действие: ";
			cin >> menu_for_value;
			if (menu_for_value == "1") {
				cout << "Введите значение, которое хотите найти: ";
				cin >> value;
			}
			else value = rand() % 10000;
			start1 = chrono::system_clock::now(); //начало подсчёта времени
			newtree = find(tree, value);
			end1 = chrono::system_clock::now(); //конец подсчёта времени
			chrono::duration<double> duration1 = end1 - start1; //промежуток времени работы функции
			if (!newtree) cout << "Данного элемента нет в дереве.\n";
			else {
				if(fixsize(newtree) <= 20) Print(newtree, 0);
				cout << endl << "Количество итераций для поиска одного элемента: " << iterations << endl;
				cout << "Время, затраченное на поиск одного элемента: " << duration1.count() << "s\n";
			}
		}
		else if (operation == "2") { //добавление элемента и анализ
			cout << "Выберите действие, которое хотите осуществить:\n1. Выбрать значение.\n2.Сгенерировать значение.\n";
			cout << "Действие: ";
			cin >> menu_for_value;
			if (menu_for_value == "1") {
				cout << "Введите значение, которое хотите добавить: ";
				cin >> value;
			}
			else value = rand() % 10000;
			start2 = chrono::system_clock::now(); //начало подсчёта времени
			tree = insert(tree, value);
			end2 = chrono::system_clock::now(); //конец подсчёта времени
			chrono::duration<double> duration2 = end2 - start2; //промежуток времени работы функции
			cout << "***************************************\n";
			if (1 + fixsize(tree) <= 20) {
				cout << "Новое случайное БДП с рандомизацией:" << endl;
				Print(tree, 0);
			}
			cout << endl << "Количество итераций для добавления одного элемента: " << iterations << endl;
			cout << "Время, затраченное на добавление одного элемента: " << duration2.count() << "s\n";
		}
		else if (operation == "3") { //удаление элемента и анализ
			cout << "Выберите действие, которое хотите осуществить:\n1. Выбрать значение.\n2.Сгенерировать значение.\n";
			cout << "Действие: ";
			cin >> menu_for_value;
			if (menu_for_value == "1") {
				cout << "Введите значение, которое хотите удалить: ";
				cin >> value;
			}
			else value = rand() % 10000;
			if (find(tree, value)) { //проверка на наличие элемента в дереве
				if (fixsize(tree) > 1) { //проверка на возможность удаления
					iterations = 0;
					start3 = chrono::system_clock::now(); //начало подсчёта времени
					tree = remove(tree, value);
					end3 = chrono::system_clock::now(); //конец подсчёта времени
					chrono::duration<double> elapsed_seconds3 = end3 - start3; //промежуток времени работы функции
					cout << "***************************************\n";
					if (1 + fixsize(tree) <= 20) {
						cout << "Новое случайное БДП с рандомизацией:" << endl;
						Print(tree, 0);
					}
					cout << endl << "Количество итераций для удаления одного элемента: " << iterations << endl;
					cout << "Время, затраченное на удаление одного элемента: " << elapsed_seconds3.count() << "s\n";
				}
				else cout << endl << "Дерево состоит из одного элемента." << endl;
			}
			else cout << "Данного элемента нет в дереве." << endl;
		}
		else {
			cout << "Действие выбрано неверно.";
		}
		cout << endl;
		cout << "Введите 'yes/y', если хотите продолжить работать с данным БДП: ";
		cin >> generation;
		if (generation == "y" || generation == "yes") continue;
		else {
			tree = nullptr;
			iterations = 0;
		}
	}
}

//функция создания дерева для среднего случая
void func_for_researhing_average(int size, int new_iterations, string generation, Node* tree, Node* btree, Node* newtree, vector<int> average_case) {
	srand(time(0));
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2; //используются для подсчёта времени генерации деревьев
	cout << "Введите количество элементов: ";
	cin >> size;
	while (size <= 0) {
		cout << "Неправильно указано количество элементов.\nВведите количество элементов: ";
		cin >> size;
	}
	tree = nullptr;
	average_case = generate_average(size); //формируется вектор из случайных чисел для среднего случая
	if (size <= 100) {
		for (int i = 0; i < size; i++) {
			cout << average_case[i] << " ";
		}
	}
	cout << endl;
	start1 = chrono::system_clock::now(); //начало подсчёта времени для сл. БДП с рандомизацией
	for (int i = 0; i < size; i++) {
		tree = insert(tree, average_case[i]);
	}
	end1 = chrono::system_clock::now(); //конец подсчёта времени для сл. БДП с рандомизацией
	chrono::duration<double> duration1 = end1 - start1; //промежуток времени работы функции для сл. БДП с рандомизацией
	cout << "Случайное БДП с рандомизацией в среднем случае:" << endl;
	if (size <= 20) Print(tree, 0);
	new_iterations = iterations;
	cout << endl << "Высота случайного БДП с рандомизацией: " << height(tree) << endl;
	cout << "Количество итераций для случайного БДП с рандомизацией: " << iterations << endl;
	cout << "Время, затраченное на добавление одного элемента: " << duration1.count() / size << "s";
	cout << endl;
	start2 = chrono::system_clock::now(); //начало подсчёта времени для сл. БДП
	for (int i = 0; i < size; i++) {
		btree = usual_insert(btree, average_case[i]);
	}
	end2 = chrono::system_clock::now(); //конец подсчёта времени для сл. БДП, которое приводится для сравнения
	chrono::duration<double> duration2 = end2 - start2; //промежуток времени работы функции для сл. БДП, которое приводится для сравнения
	cout << "Случайное БДП для сравнения:" << endl;
	if (size <= 10) Print(btree, 0);
	cout << endl << "Высота случайного БДП: " << height(btree) << endl;
	cout << "Количество итераций для случайного БДП: " << iterations - new_iterations << endl;
	cout << "Время, затраченное на добавление одного элемента: " << duration2.count() / size << "s\n";
	generation = "y";
	function_for_bst(generation, tree, newtree);
}

//функция создания дерева для худшего случая
void func_for_researching_worst(int size, int new_iterations, string generation, Node* tree, Node* btree, Node* newtree, vector<int> worst_case) {
	srand(time(0));
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2; //используются для подсчёта времени генерации деревьев
	cout << "Введите количество элементов: ";
	cin >> size;
	while (size <= 0) {
		cout << "Неправильно указано количество элементов.\nВведите количество элементов: ";
		cin >> size;
	}
	tree = nullptr;
	worst_case = generate_worst(size); //формируется вектор из случайных чисел для худшего случая
	if (size <= 100) {
		for (int i = 0; i < size; i++) {
			cout << worst_case[i] << " ";
		}
	}
	cout << endl;
	start1 = chrono::system_clock::now(); //начало подсчёта времени для сл. БДП с рандомизацией
	for (int i = 0; i < size; i++) {
		tree = insert(tree, worst_case[i]); 
	}
	end1 = chrono::system_clock::now(); //конец подсчёта времени для сл. БДП с рандомизацией
	chrono::duration<double> duration1 = end1 - start1; //промежуток времени работы функции для сл. БДП с рандомизацией
	cout << endl << "Случайное БДП с рандомизацией в худшем случае:" << endl;
	if (size <= 20) Print(tree, 0);
	new_iterations = iterations;
	cout << endl << "Высота случайного БДП с рандомизацией: " << height(tree) << endl;
	cout << "Количество итераций для случайного БДП с рандомизацией: " << iterations << endl;
	cout << "Время, затраченное на добавление одного элемента: " << duration1.count() / size << "s";
	cout << endl;
	start2 = chrono::system_clock::now(); //начало подсчёта времени для сл. БДП, которое приводится для сравнения
	for (int i = 0; i < size; i++) {
		btree = usual_insert(btree, worst_case[i]);
	}
	end2 = chrono::system_clock::now();  //конец подсчёта времени для сл. БДП, которое приводится для сравнения
	chrono::duration<double> duration2 = end2 - start2; //промежуток времени работы функции для сл. БДП, которое приводится для сравнения
	cout << "Случайное БДП для сравнения:" << endl;
	if (size <= 10) Print(btree, 0);
	cout << endl << "Высота случайного БДП: " << height(btree) << endl;
	cout << "Количество итераций для случайного БДП: " << iterations - new_iterations << endl;
	cout << "Время, затраченное на добавление одного элемента: " << duration2.count() / size << "s\n";
	cout << endl;
	generation = "y";
	function_for_bst(generation, tree, newtree);
}

int main() {
	setlocale(LC_ALL, "Russian");
	int new_iterations = 0;
	string start_end; //используется для работы программы в качестве входа/выхода
	string menu_for_generation; //используется в качестве меню по генерации деревьев
	string menu_for_creation; //используется в качестве меню по обработки созданного дерева
	string generation; //используется для работы со сгенерированным деревом
	cout << "Введите 'yes/y', если хотите начать работать с БДП: ";
	cin >> start_end;
	while (start_end == "y" || start_end =="yes"){
		int size;
		cout << "Выберите действие, которое хотите осуществить:\n";
		cout << "0. Завершить работу.\n1. Сгенерировать случайное БДП с рандомизацией и провести его анализ.\n2. Построить случайное БДП с рандомизацией.\n";
		string menu; //используется в качестве меню программы
		cout << "Действие: ";
		cin >> menu;
		vector<int> average_case;
		vector<int> worst_case;
		Node* tree = nullptr;
		Node* btree = nullptr;
		Node* newtree = nullptr;
		if(menu == "0") break;
		else if (menu == "1") { //генерация случайного БДП с рандомизацией и анализ
			menu_for_generation = "y";
			while (menu_for_generation == "y" || menu_for_generation == "yes") { //меню выбора генерации дерева
				cout << "Выберите действие, которое хотите осуществить:\n1. Генерация элементов в среднем случае.\n2. Генерация элементов в худшем случае.\n";
				cout << "Действие: ";
				string type_generation; //используется для определения типа генерации
				cin >> type_generation;
				if (type_generation == "1") func_for_researhing_average(size, new_iterations, generation, tree, btree, newtree, average_case);
				else if (type_generation == "2") func_for_researching_worst(size, new_iterations, generation, tree, btree, newtree, average_case);
				else cout << "Действие выбрано неверно.";
				cout << endl;
				cout << "Введите 'yes/y', если хотите продолжить работать с генерацией БДП: ";
				cin >> menu_for_generation;
				if (menu_for_generation == "y" || menu_for_generation == "yes") {
					btree = nullptr;
					iterations = 0;
				}
			}
		}
		else if (menu == "2") { //создание случайного БДП с рандомизацией
			srand(time(0));
			cout << "Введите количество элементов: ";
			cin >> size;
			while (size <= 0) {
				cout << "Неправильно указано количество элементов.\nВведите количество элементов: ";
				cin >> size;
			}
			cout << "Введите массив элементов: ";
			for (int i = 0; i < size; i++) {
				int in;
				cin >> in;
				tree = insert(tree, in);
			}
			cout << "***************************************\n";
			cout << "Случайное БДП с рандомизацией:" << endl;
			Print(tree, 0);
			cout << endl;
			menu_for_creation = "y";
			while (menu_for_creation == "y" || menu_for_creation == "yes") { //меню выбора метода работы с деревом
				cout << "Выберите действие, которое хотите осуществить:\n0. Создание нового дерева.\n1. Поиск элемента.\n2. Вставка элемента.\n3. Удаление элемента.\n";
				cout << "Действие: ";
				string method;
				int value;
				cin >> method;
				if (method == "0") break;
				else if (method == "1") { //поиск элемента
					srand(time(0));
					cout << "Введите значение, которое хотите найти: ";
					cin >> value;
					cout << endl;
					newtree = find(tree, value);
					if (!newtree) cout << "Данного элемента нет в дереве.\n";
					else Print(newtree, 0);
				}
				else if (method == "2") { //добавление элемента
					srand(time(0));
					cout << "Введите значение, которое хотите добавить: ";
					cin >> value;
					cout << endl;
					tree = insert(tree, value);
					cout << "***************************************\n";
					cout << "Новое случайное БДП с рандомизацией:" << endl;
					Print(tree, 0);
				}
				else if (method == "3") { //удаление элемента
					srand(time(0));
					cout << "Введите значение, которое хотите удалить: ";
					cin >> value;
					if (find(tree, value)) {
						if (fixsize(tree) >= 1) {
							tree = remove(tree, value);
							cout << "***************************************\n";
							cout << "Новое случайное БДП с рандомизацией:" << endl;
							Print(tree, 0);
						}
					}
					else cout << "Данного элемента нет в дереве.\n";
				}
				else{
					cout << "Действие выбрано неверно.";
				}
				cout << endl;
				cout << "Введите 'yes/y', если хотите продолжить работать с данным БДП: ";
				cin >> menu_for_creation;
				if (menu_for_creation == "y" || menu_for_creation == "yes") continue;
				else iterations = 0;
			}
		}
		else{
			cout << "Действие выбрано неверно.";
		}
		cout << endl;
		cout << "Введите 'yes/y', если хотите продолжить работать с БДП: ";
		cin >> start_end;
		if (start_end == "y" || start_end == "yes") iterations = 0;
	}
	cout << "Работа завершена.";
	return 0;
}