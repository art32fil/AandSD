#include <iostream>
#include <fstream>
#include <set>
#include <ctime>

typedef struct Elem{
    int size;
    int x;
    struct Elem* left;
    struct Elem* rigth;
}Elem;

void my_qsort(int* arr, int start, int end, int& counter){
    if(end - start > 0){
        counter++;
        int num_base = end;
        int cur = start;
        int quanity_base = 1;
        int base = arr[num_base];
        int size = num_base - cur;
        for(int i = 0; i < size; i++){
            counter++;
            if (base > arr[cur]){
                cur += 1;
                counter++;
            }
            else if (base == arr[cur]){
                counter++;
                for(int j = 0; j < num_base - cur - 1; j++){
                    counter++;
                    int t = arr[cur + j];
                    arr[cur + j] = arr[cur + j + 1];
                    arr[cur + j + 1] = t;
                }
                num_base -= 1;
                counter++;
                quanity_base += 1;
                counter++;
            }
            else{
                int t = arr[cur];
                arr[cur] = arr[num_base - 1];
                arr[num_base - 1] = t;
                for(int k = 0; k < quanity_base; k++){
                    counter++;
                    t = arr[num_base - 1 + k];
                    arr[num_base - 1 + k] = arr[num_base + k];
                    arr[num_base + k] = t;
                }
                num_base -= 1;
                counter++;
            }
            counter++;
        }
        my_qsort(arr, start, num_base - 1, counter);
        my_qsort(arr, num_base + quanity_base, end, counter);
    }
}

template <typename T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

int leo(int x, int& counter){
    if(x == 1)
        return 1;
    else{
        if(x == 2)
            return 1;
        else{
            counter++;
            return leo(x - 2, counter) + leo(x - 1, counter) + 1;
        }
    }
}

void clearing(Elem* tree, int& counter){
    if(tree->left && tree->rigth){
        counter++;
        if(tree->x < tree->left->x && tree->left->x >= tree->rigth->x){
            counter++;
            swap(tree->x, tree->left->x);
            clearing(tree->left, counter);
        }
        else if(tree->x < tree->rigth->x && tree->left->x < tree->rigth->x){
            counter++;
            swap(tree->x, tree->rigth->x);
            clearing(tree->rigth, counter);
        }
    }
}

Elem* make_new(int x){
    Elem* new_elem = new Elem;
    new_elem->left = nullptr;
    new_elem->rigth = nullptr;
    new_elem->x = x;
    new_elem->size = 1;
    return new_elem;
}

Elem* union_elem(int x, Elem* left, Elem* rigth, int& counter){
    Elem* new_elem = new Elem;
    new_elem->left = left;
    new_elem->rigth = rigth;
    new_elem->x = x;
    new_elem->size = left->size + rigth->size + 1;
    counter++;
    return new_elem;
}

int make_and_sort(Elem** p, int* x, int n, int& num, std::set <int>& s){
    int counter = 0;
    Elem* new_elem = make_new(x[0]);
    p[0] = new_elem;
    for(int i = 1; i < n; i++){
        counter++;
        if(num == 1){
            counter++;
            num += 1;
            counter++;
            p = (Elem**)realloc(p, num * sizeof(Elem*));
            p[1] = make_new(x[i]);
        }
        else{
            if(s.find(p[num - 1]->size + p[num - 2]->size + 1) != s.end()){
                counter++;
                Elem* tmp = union_elem(x[i], p[num - 2], p[num - 1], counter);
                num -= 1;
                counter++;
                p[num] = nullptr;
                p = (Elem**)realloc(p, num * sizeof(Elem*));
                p[num - 1] = tmp;
                clearing(p[num - 1], counter);
            }
            else{
                num += 1;
                counter++;
                p = (Elem**)realloc(p, num * sizeof(Elem*));
                p[num - 1] = make_new(x[i]);
            }
        }
    }

    for(int i = 0; i < n; i++){
        int max = p[0]->x;
        int index = 0;
        if(n > 1 || p[0]->size != 1){
            int* tmp = new int[num];
            for(int j = 1; j < num; j++){
                counter++;
                tmp[j] = p[j]->x;
                if(tmp[j] > max){
                    max = tmp[j];
                    index = j;
                }
                counter++;
            }
            if(num != 1 && index != num - 1){
                swap(p[index]->x, p[num - 1]->x);
                clearing(p[index], counter);
            }
            counter += 2;
        }
        counter += 2;
        x[n - 1 - i] = max;

        if(p[num - 1]->size != 1){
            counter++;
            num += 1;
            counter++;
            p = (Elem**)realloc(p, num * sizeof(Elem*));
            p[num - 1] = p[num - 2]->rigth;
            p[num - 2] = p[num - 2]->left;
        }
        else{
            counter++;
            num -= 1;
            counter++;
            p = (Elem**)realloc(p, num * sizeof(Elem*));
        }
    }
    return counter;
}


void leo_chain(std::set<int>& s, int x, int& counter){
    int k = 1;
    int max = leo(1, counter);
    while(x >= max){
        counter++;
        s.insert(max);
        k += 1;
        counter++;
        max = leo(k, counter);
    }
}

void generate(int* arr, int* copy, int size, int a, int b){
    for(int i = 0; i < size; i++){
        arr[i] = rand() % (b - a + 1) + a;
        copy[i] = arr[i];
    }
}

int main() {
    srand(time(0));
    float t_q = 0, t_s = 0;
    int counter = 0;
    int num;
    std::cout << "Enter the number of sets: ";
    std::cin >> num;

    if (num < 1) {
        std::cout << "Error! Sets < 1!!\n";
        return 0;
    }

    int size;
    std::cout << "Enter the number of numbers in the set: ";
    std::cin >> size;

    if (size < 1) {
        std::cout << "Error! Size < 1!!\n";
        return 0;
    }
    int a, b;
    std::cout << "Enter the boundaries of random numbers: ";
    std::cin >> a >> b;

    if (b - a <= 0) {
        std::cout << "Error! Wrong boundaries!!\n";
        return 0;
    }
    std::cout << '\n';

    int* worst1 = new int[1000];
    int* worst1_copy = new int[1000];
    int* worst2 = new int[800];
    int* worst2_copy = new int[800];

    Elem** p = new Elem*[1];
    int n = 1;
    std::set <int> chain;
    clock_t time;

    std::fstream file;
    file.open("stats.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    for(int i = 1000; i > 0; i--){
        worst1[1000 - i - 1] = i;
        worst1_copy[1000 - i - 1] = i;
    }

    for(int i = 800; i > 0; i--){
        worst2[800 - i - 1] = i;
        worst2_copy[800 - i - 1] = i;
    }

    std::cout << "Generated array: ";
    for (int i = 0; i < 1000; i++)
        std::cout << worst1[i] << ' ';
    std::cout << '\n';

    time = clock();
    my_qsort(worst1, 0, 1000 - 1, counter);
    time = clock() - time;
    std::cout << "Sorting time with my_qsort: " << (float)time/CLOCKS_PER_SEC << "s, base operation = " << counter << '\n';
    std::cout << "Array after my_qsort: ";
    for (int i = 0; i < 1000; i++)
        std::cout << worst1[i] << ' ';
    std::cout << '\n';

    counter = 0;
    time = clock();
    leo_chain(chain, 1000, counter);
    counter += make_and_sort(p, worst1_copy, 1000, n, chain);
    time = clock() - time;
    std::cout << "Sorting time with smoothsort: " << (float)time/CLOCKS_PER_SEC << "s, base operation = " << counter << '\n';
    std::cout << "Array after smoothsort: ";
    for (int i = 0; i < 1000; i++)
        std::cout << worst1_copy[i] << ' ';
    std::cout << '\n';
    std::cout << '\n';

    std::cout << "Generated array: ";
    for (int i = 0; i < 800; i++)
        std::cout << worst2[i] << ' ';
    std::cout << '\n';

    n = 1;
    counter = 0;
    time = clock();
    my_qsort(worst2, 0, 800 - 1, counter);
    time = clock() - time;
    std::cout << "Sorting time with my_qsort: " << (float)time/CLOCKS_PER_SEC << "s, base operation = " << counter << '\n';
    std::cout << "Array after my_qsort: ";
    for (int i = 0; i < 800; i++)
        std::cout << worst2[i] << ' ';
    std::cout << '\n';

    counter = 0;
    time = clock();
    leo_chain(chain, 800, counter);
    counter += make_and_sort(p, worst2_copy, 800, n, chain);
    time = clock() - time;
    std::cout << "Sorting time with smoothsort: " << (float)time/CLOCKS_PER_SEC << "s, base operation = " << counter << '\n';
    std::cout << "Array after smoothsort: ";
    for (int i = 0; i < 800; i++)
        std::cout << worst2_copy[i] << ' ';
    std::cout << '\n';
    std::cout << '\n';

    for(int i = 0; i < num; i++){
        n = 1;
        counter = 0;
        int *arr = new int[size];
        int *copy = new int[size];
        generate(arr, copy, size, a, b);
        std::cout << "Generated array: ";
        for (int j = 0; j < size; j++)
            std::cout << arr[j] << ' ';
        std::cout << '\n';

        time = clock();
        my_qsort(arr, 0, size - 1, counter);
        time = clock() - time;
        t_q += (float)time/CLOCKS_PER_SEC;
        std::cout << "Sorting time with my_qsort: " << (float)time/CLOCKS_PER_SEC << "s, base operation = " << counter << '\n';
        std::cout << "Array after my_qsort: ";
        for (int j = 0; j < size; j++)
            std::cout << arr[j] << ' ';
        std::cout << '\n';

        counter = 0;
        time = clock();
        leo_chain(chain, b, counter);
        counter += make_and_sort(p, copy, size, n, chain);
        time = clock() - time;
        t_s += (float)time/CLOCKS_PER_SEC;
        std::cout << "Sorting time with smoothsort: " << (float)time/CLOCKS_PER_SEC << "s, base operation = " << counter << '\n';
        std::cout << "Array after smoothsort: ";
        for (int j = 0; j < size; j++)
            std::cout << copy[j] << ' ';
        std::cout << '\n';
        std::cout << '\n';
        delete[] arr;
        delete[] copy;
    }
    file << "New data !!\n";
    file << "size\ttime qsort\ttime smooth sorting\t\tsets\n";
    file << size << "\t\t" << t_q / (float)(num) << "\t\t" << t_s / (float)(num) << "\t\t\t" << num << '\n';
    file.close();
    return 0;
}