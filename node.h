#ifndef NODE_H
#define NODE_H

template <typename T>
class BSTree; 

template <typename T>
class Iterator; 

template <typename T>
class Node {
    T data;
    Node<T> *left;
    Node<T> *right;
    BSTree<T> *tree;

    template<class>
    friend class BSTree; 

    template<class>
    friend class Iterator; 

    Node(T data, BSTree<T> *tree): data(data), tree(tree), left(0), right(0) {}
};

#endif