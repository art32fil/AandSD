#include "iostream"
#include "tree.h" 
template <typename T>
Tree <T>*  Create(T& key,Tree<T>left, Tree<T>right)
{
   Tree <T>*  New  = new Tree<T> (key, left, right);
    return New;
    
}














