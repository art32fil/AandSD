#ifndef NODE_H
#define NODE_H

#include <cinttypes>
#include <memory>

template<class T>
struct Node {
  using NodePtr = std::shared_ptr<Node<T>>;

  Node(T key);
  Node(T key, uint8_t h);
  ~Node() = default;

  T key;
  uint8_t height = 1;
  NodePtr left = nullptr;
  NodePtr right = nullptr;
};

template<class T>
Node<T>::Node(T key)
    : key(key) {}

template<class T>
Node<T>::Node(T key, uint8_t h)
    : key(key), height(h) {}

#endif // NODE_H
