#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"
#include <algorithm>
#include <stack>

template<class>
class Iterator; 

template <typename T> 
class BSTree {
    Node<T> *root;
    size_t nodes;
    
    template<class>
    friend class Iterator; 

    public:
        BSTree() : root(nullptr), nodes(0) {};

        bool find(T data) { 
            Node<T> *current(this->root);
            while(current) {
                if(data < current->data) current = current->left;
                else if(data > current->data) current = current->right;
                else return true;
            }
            return false;
        }

        bool findNode(T data, Node<T>**& current) {
            current = this->root ? &this->root : nullptr;
            while(current) {
                if(data < (*current)->data) current = (*current)->left ? &(*current)->left : nullptr;
                else if(data > (*current)->data) current = (*current)->right ? &(*current)->right : nullptr;
                else return true;
            }
            return false;
        }

        void tracePath(Node<T>* node, stack<Node<T>* > &s) {
            Node<T> *current = this->root;
            while(node != current) {
                s.push(current);
                if(node->data <= current->data) current = current->left;
                else current = current->right;
            }
        }

        void insert(T data) {
            Node<T> *node = new Node<T>(data,this);
            Node<T> *x(this->root), *y(0);
            while(x) {
                y = x;
                if(node->data <= x->data) x = x->left;
                else x = x->right;
            }
            if(!y) this->root = node;
            else if(node->data <= y->data) y->left = node;
            else y->right = node;
            ++this->nodes;
        }

        bool remove(T data) {
            Node<T> **z(0), **y(0), *x(0);
            if(!this->findNode(data,z)) return false;
            if((*z)->left && (*z)->right) {
                this->treeMinimum((*z)->right,y);
                if((*y)->right) x = (*y)->right;
                (*z)->data = (*y)->data;
                if(x) {
                    (*y)->data = x->data;
                    (*y)->right = x->right;
                    (*y)->left = x->left;
                    delete x;
                    x = nullptr;
                } else {
                    delete *y;
                    *y = nullptr;
                }
                --this->nodes;
                return true;
            }
            if((*z)->left) x = (*z)->left;
            else if ((*z)->right) x = (*z)->right;
            else {
                delete *z;
                *z = nullptr;
            }
            if(x) {
                (*z)->left = x->left;
                (*z)->right = x->right;
                (*z)->data = x->data;
                delete x;
                x = nullptr;
            }
            --this->nodes;
            return true;
        }

        Node<T>* treeMinimum(Node<T> *x) {
            while(x && x->left) x = x->left;
            return x;
        }

        Node<T>* treeMinimum() {
            return treeMinimum(this->root);
        }

        void treeMinimum(Node<T> *&x, Node<T>**& node) {
            node = &x;
            while(node && (*node)->left) node = &(*node)->left;
        }

        void treeMinimum(Node<T> *&x, stack<Node<T>* > &s) {
            if(x && x->left) {
                x = x->left;
                if(x->left) s.push(x);
            }
        }

        void treeMaximum(Node<T> *&x, stack<Node<T>* > &s) {
            if(x && x->right) {
                x = x->right;
                if(x->right) s.push(x);
            }
        }

        Node<T>* treeMaximum(Node<T> *x) {
            while(x && x->right) x = x->right;
            return x;
        }

        size_t size() {
            return this->nodes;
        }

        size_t height() {
            // TODO
        }

        void traversePreOrder() {
            traversePreOrder(this->root);
        }

        void traversePreOrder(Node<T>* current) {
            if(current) {
                cout << current->data << endl;
                traversePreOrder(current->left);
                traversePreOrder(current->right);
            }
        }

        void traverseInOrder() {
            traverseInOrder(this->root);
        }

        void traverseInOrder(Node<T>* current) {
            if(current) {
                traverseInOrder(current->left);
                cout << current->data << endl;
                traverseInOrder(current->right);
            }
        }

        void traversePostOrder() {
            traversePostOrder(this->root);
        }

        void traversePostOrder(Node<T>* current) {
            if(current) {
                traversePostOrder(current->right);
                cout << current->data << endl;
                traversePostOrder(current->left);
            }
        }

        Iterator<T> begin() {
            Iterator<T> it(this->treeMinimum(this->root));
            return it;
        }

        Iterator<T> end() {
            Iterator<T> it(this->treeMaximum(this->root));
            return ++it;
        }

        ~BSTree() {
            // TODO
        }
};

#endif
