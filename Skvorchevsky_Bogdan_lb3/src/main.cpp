#include "Tree.h"


int main(int argc, char** argv){
    Elem E;
    std::string tree, tmp;
    Tree bin_tree;
    std::ifstream in("input.txt");
    getline(in, tree);
    getline(in, tmp);
    E = tmp[0];
    std::cout << "Введено бинарное дерево: " << tree << std::endl;
    std::cout << "Введён элемент для поиска: " << E << std::endl;
    if (!bin_tree.brackets_check(tree)){
        std::cout << "Введённые данные некорректны." << std::endl;
        return 1;
    }
    bin_tree.SetElem(E);
    bin_tree.read_tree(tree);
    bin_tree.search_elem(bin_tree.get_root());

    if (bin_tree.get_elem_count()){
        std::cout << "Элемент " << E << " встречается в бинарном дереве " << bin_tree.get_elem_count() << " раз.\n";
        std::cout << "Длина кратчайшего пути равна " << bin_tree.get_min_path() << ".\n";
    }
    else{
        std::cout << "Элемент " << E <<" не найден.\n";
        std::cout << "Длина кратчайшего пути равна -1.\n";
    }

    return 0;
}