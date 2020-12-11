#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

void sort_int(int *a, int *b){
	bool state = false;
	int *c = b - 1;
	for (int *i = a; i < c; i++){
		if (*i > *(i + 1)){ 
			swap(*i, *(i + 1)); 
			state = true; 
		}
	}
	if (state) sort_int(a, b);
}

void print_int(int a[], int n){
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int *Ost(int a[], int n, int &j){
	int *ost = new int[j];
	for(int i = n-1; i >= 0; i--){
		if(a[i] > a[i-1]){
			ost[n-1-i]=a[i];
			j++;
			break;
		}else{
			ost[n-1-i]=a[i];
			j++;
		}
	}
	return ost;
}

int *Res(int ost_1[], int ost_2[], int k, int j){
	int p = 0;
	int t = 0;
	int *res = new int[j];
	for (int i = 0; i < j; i++){
		if (i < k){
			res[i] = ost_1[p];
			p++;
		}else{
			res[i] = ost_2[t];
			t++;
		}
	}
	return res;
}

int *Alm_perm(int a[], int res[], int n, int j){
	int r = 0;
	int *alm_perm = new int[n];
	for (int i = 0; i < n; i++){
		if(i < n-j){
			alm_perm[i] = a[i];
		}else{
			alm_perm[i] = res[r];
			r++;
		}
	}
	return alm_perm;
}

void swap_int(int alm_perm[], int n, int j){
	for (int i = 0; i < n; i++){
		if (i == n-j-1){
			int temp = alm_perm[i];
			alm_perm[i] = alm_perm[i+1];
			alm_perm[i+1] = temp;
		}
	}

}

int *sort_Ost(int a[], int n, int j){
	int k = 0;
	int *sort_ost = new int[j];
	for(int i = 0; i < n; i++){
		if(i >= n-j){
			sort_ost[k] = a[i];
			k++;
		}
	}
	sort_int(sort_ost, sort_ost+j);
	return sort_ost;
}

int *Perm(int alm_perm[], int sort_ost[], int n, int j){
	int l = 0;
	int *perm = new int[n];	
	for (int i = 0; i < n; i++){
		if (i < n-j){
			perm[i] = alm_perm[i];
		}else{
			perm[i] = sort_ost[l];
			l++;
		}
	}
	return perm;
}

void delete_all(int ost[], int ost_1[], int ost_2[], int res[], int alm_perm[], int sort_ost[], int perm[]){
	delete [] ost;
	delete [] ost_1;
	delete [] ost_2;
	delete [] res;
	delete [] alm_perm;
	delete [] sort_ost;
	delete [] perm;
}

int perms_int(int a[], int n){
	int j = 0;
	int min = 0;
	
	int *ost = new int[n-1];
	ost = Ost(a, n, j);
	
	if (j == n) return 0;
	
	int k = 0;
	int m = 0;
	
	int *ost_1 = new int[j];
	int *ost_2 = new int[j];
	for (int i = 0; i < j; i++){
		if(ost[i] > a[n-j-1]){
			ost_1[k] = ost[i];
			k++;
		}else{
			ost_2[m] = ost[i];
			m++;
		}
	}
	
	int *res = new int[j];
	res = Res(ost_1, ost_2, k, j);
	
	int *alm_perm = new int[n];
	alm_perm = Alm_perm(a, res, n, j);
	
	swap_int(alm_perm, n, j);
	
	int *sort_ost = new int[j];
	sort_ost = sort_Ost(alm_perm, n, j);
	
	int *perm = new int[n];
	perm = Perm(alm_perm, sort_ost, n, j);
	
	print_int(perm, n);
	
	perms_int(perm, n);
	
	delete_all(ost, ost_1 ,ost_2, res, alm_perm, sort_ost, perm);
	
	return 1;
}

void sort_symb(char a[], int n){
	char temp = a[0];
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if (tolower(a[i]) < tolower(a[j])){
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
		
}

void print_symb(char a[], int n){
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

char *Ost_symb(char a[], int n, int &j){
	char *ost = new char[j];
	for(int i = n-1; i >= 0; i--){
		if(a[i] > a[i-1]){
			ost[n-1-i]=a[i];
			j++;
			break;
		}else{
			ost[n-1-i]=a[i];
			j++;
		}
	}
	return ost;
}

char *Res_symb(char ost_1[], char ost_2[], int k, int j){
	int p = 0;
	int t = 0;
	char *res = new char[j];
	for (int i = 0; i < j; i++){
		if (i < k){
			res[i] = ost_1[p];
			p++;
		}else{
			res[i] = ost_2[t];
			t++;
		}
	}
	return res;
}

char *Alm_perm_symb(char a[], char res[], int n, int j){
	int r = 0;
	char *alm_perm = new char[n];
	for (int i = 0; i < n; i++){
		if(i < n-j){
			alm_perm[i] = a[i];
		}else{
			alm_perm[i] = res[r];
			r++;
		}
	}
	return alm_perm;
}

void swap_symb(char alm_perm[], int n, int j){
	for (int i = 0; i < n; i++){
		if (i == n-j-1){
			char temp = alm_perm[i];
			alm_perm[i] = alm_perm[i+1];
			alm_perm[i+1] = temp;
		}
	}

}

char *sort_Ost_symb(char a[], int n, int j){
	char *sort_ost = new char[j];
	int k = 0;
	for(int i = 0; i < n; i++){
		if(i >= n-j){
			sort_ost[k] = a[i];
			k++;
		}
	}
	sort_symb(sort_ost, j);
	return sort_ost;
}

char *Perm_symb(char alm_perm[], char sort_ost[], int n, int j){
	int l = 0;
	char *perm = new char[n];	
	for (int i = 0; i < n; i++){
		if (i < n-j){
			perm[i] = alm_perm[i];
		}else{
			perm[i] = sort_ost[l];
			l++;
		}
	}
	return perm;
}

void delete_all_symb(char ost[], char ost_1[], char ost_2[], char res[], char alm_perm[], char sort_ost[], char perm[]){
	delete [] ost;
	delete [] ost_1;
	delete [] ost_2;
	delete [] res;
	delete [] alm_perm;
	delete [] sort_ost;
	delete [] perm;
}

int perms_symb(char a[], int n){
	int j = 0;
	int min = 0;
	char *ost = new char[n-1];
	ost = Ost_symb(a, n, j);
	
	if (j == n) return 0;
	
	int k = 0;
	int m = 0;
	
	char *ost_1 = new char[j];
	char *ost_2 = new char[j];
	for (int i = 0; i < j; i++){
		if(ost[i] > a[n-j-1]){
			ost_1[k] = ost[i];
			k++;
		}else{
			ost_2[m] = ost[i];
			m++;
		}
	}
	
	char *res = new char[j];
	res = Res_symb(ost_1, ost_2, k, j);
	
	char *alm_perm = new char[n];
	alm_perm = Alm_perm_symb(a, res, n, j);
	
	swap_symb(alm_perm, n, j);

	char *sort_ost = new char[j];
	sort_ost = sort_Ost_symb(alm_perm, n, j);
	
	char *perm = new char[n];
	perm = Perm_symb(alm_perm, sort_ost, n, j);
	
	print_symb(perm, n);
	
	perms_symb(perm, n);
	
	delete_all_symb(ost, ost_1 ,ost_2, res, alm_perm, sort_ost, perm);
	
	return 1;
}

void Error(short n){
	cout << "Error #" << n << ". ";
	switch (n){
		case 0: 
			cout << "Размер массива не задан." << endl; 
			break;
		case 1: 
			cout << "Тип массива не определён." << endl; 
			break;
		case 2: 
			cout << "Массив не состоит из натуральных чисел." << endl; 
			break;
		case 3: 
			cout << "Массив не состоит из символов." << endl; 
			break;
		case 4: 
			cout << "Массив состоит из повторяющихся значений." << endl; 
			break;
		default: 
			cout << "! ."; 
			break;
	}		
}

int main(){
	int n;
	cout << "Введите размер массива: n = ";
	cin >> n;
	
	if (!n){
		Error(0); 
		return 0; 
	}
	
	string type;
	cout << "Введите тип массива ('0' для числового массива, 'a' - для символьного): ";
	cin >> type;
	
	if (type == "0"){
		int a[n];
		cout << "Введите массив из чисел через пробел: a[n] = ";
		for (int i = 0; i < n; i++){
			cin >> a[i];
			if (a[i] > 0) continue;
			else{
				Error(2);
				return 0;
			}
		}

		sort_int(a, a+n);
		for (int i = 0; i < n; i++){
			if (a[i] == a[i+1]){
				Error(4);
				return 0;
			}
		}
		
		cout << "Перестановки данного массива: " << endl;		
		print_int(a, n);
		perms_int(a, n);
	}
	
	else if(type == "a" || type == "A"){
		char a[n];
		cout << "Введите массив из символов: a[n] = ";
		for (int i = 0; i < n; i++){
			cin >> a[i];
			if (isalpha(a[i])) continue;
			else{
				Error(3);
				return 0;
			}
		}
		
		sort_symb(a, n);
		
		for (int i = 0; i < n; i++){
			if (a[i] == a[i+1]){
				Error(4);
				return 0;
			}
		}
		
		cout << "Перестановки данного массива: " << endl;		
		print_symb(a, n);
		perms_symb(a, n);
	}
	
	else{
		Error(1);
		return 0;
	}
}
