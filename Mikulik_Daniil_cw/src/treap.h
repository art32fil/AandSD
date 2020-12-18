#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <fstream>
#include <stack>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

/* Mikulik D.P., Course work
 * Variant 14
 * Type of the task: current control (including and excluding elements for the Cartesian tree data structure).
 * December 2020.
 * All comments are written in English, because UTF-8 encoding is maintained not in all text editors or IDE's.
 */




/* Class Node
 * Node class is a basic class for each elem in the treap.
 * It contains key value, priority of the current elem, size of a treap, and pointers on left/right "sons" of the element.
 * Its constructor initializes new elem with random priority.
 * There were used smart pointers to avoid using complex destructor.
 */

class Node{
    public:
        int key;
        int prior;
        int size;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node(int key){
            this->key = key;
            left = right = nullptr;
            this->prior = rand()%100;
            size = 1;
        }
        Node(){}
};

/*
 * Pair defined here is a std::pair object, containing two Nodes.
 */

typedef pair<shared_ptr<Node>, shared_ptr<Node>> Pair;


/* Class Treap.
 * Class Treap is a base class used in the coursework.
 * It storages a pointer on root of the treap (data).
 * Also this class provides all basic methods to interact with the data structure.
 */
class Treap{
protected:
    shared_ptr<Node> data = nullptr;
public:
    int size;
    /* Merge method.
     * Merge method is one of the fundamental methods of the Cartesian tree data structure.
     * It merges two Cartesian trees.
     */
    shared_ptr<Node> merge(shared_ptr<Node> left, shared_ptr<Node> right);

    /*
     * Split method.
     * Split method is one of the fundamental methods of the Cartesian tree data structure.
     * It splits one Cartesian tree into two ones by the given x key value.
     */
    Pair split(shared_ptr<Node> p, int x);

    /* Insert method.
     * Is one of two methods required by the task of the course work.
     * Inserts a new element of the given x value into the treap .
     */
    void insert(int x);


    /* Remove method.
     * Is the second required method.
     * Removes an element of the given key value from the treap .
     */
    void remove(int key);


    /* Dispose method.
     * Deletes the node that was given and its "sons".
     */
    void dispose(shared_ptr<Node> node);



    /* Print method.
     * Is a wrapper of the PrintInOrderTraversal method.
     * Prints the tree to the console.
     */
    void PrintInOrderTraversal(shared_ptr<Node> node, int k);
    void print();

    /* PrintFile method.
     * Is a wrapper of the PrintFileTraversal method.
     * Prints the tree to the file "conditions.txt".
     */
    void PrintFileTraversal(shared_ptr<Node> node, int k, std::string& res);
    std::string printFile();

    /* Visualize method
     * The main method of the 5th lab, creates .txt file with some dependencies.
     * After creating a file a dot compiler is called to process a .png file containing the tree.
     */
    void visualize();


    /* Read method.
     * Reads data from the file of given name.
     * Creates a Cartesian tree using the given key values.
     */
    std::pair<int, int> read();

    /*
     *Find method
     *Finds an element in the tree
     */
    int findElem(int x);
    int find(shared_ptr<Node> node, int x);

    /*
     * correctAnswer method
     * Returns a string with correct answer
     */
    std::string correctAnswer();

};

#endif // TREAP_H
