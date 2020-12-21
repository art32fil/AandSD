#include "HashMap.h"

int main() {
    int capacity = 512;
    auto *h = new HashMap<int, int>(capacity);
    unsigned int start_time;
    double used_time = 0;
    unsigned int bad_key;
    int r_value;
    int r_key;
    int operations_count = 0;
    for (int k = 0; k < 7; k++) {
        printf("Number of elements is %d\n", capacity);
        // Вставка случайных чисел со случайным ключом в хеш-таблицу (средний случай)
        for (int i = 0; i < capacity; i++) {
            srand((int) clock());
            r_key = rand() % 1000000; // Генерация ключа
            r_value = rand() % 1000000 + 1; // Генерация значения
            start_time = clock();
            operations_count += h->insertNode(r_key, r_value);
            used_time += ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
        }
        used_time *= 1000;
        used_time /= capacity;
        operations_count /= capacity;
        printf("Average insertion time and operations count in the average case is %lf ms and %d pieces\n", used_time, operations_count);
        used_time = 0;
        operations_count = 0;
        srand((int) clock());
        bad_key = rand() % 10000; // Генерация ключа для худшего случая
        h->resize(capacity);
        // Вставка случайных чисел с одним и тем же ключом в хеш-таблицу (худший случай)
        for (int i = 0; i < capacity; i++) {
            srand((int) clock());
            r_value = rand() % 1000000 + 1; // Генерация значения
            start_time = clock();
            operations_count += h->insertNode(bad_key, r_value); // Вызов функции для вставки в хеш-таблицу
            used_time += ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
        }
        used_time *= 1000;
        used_time /= capacity;
        operations_count /= capacity;
        printf("Average insertion time and operations count in the bad case is %lf ms and %d pieces\n", used_time, operations_count);
        printf("---------------------------------------------------------\n");
        capacity *= 2;
        h->resize(capacity);
        used_time = 0;
        operations_count = 0;
    }

    return 0;
}
