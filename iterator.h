#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include "bstree.h"
#include <stack>

template <typename T>
class Iterator {
    private:
        Node<T> *current;
        BSTree<T> *tree;
        stack<Node<T>* > s;
    public:
        Iterator(): current(0), tree(0) {}

        Iterator(Node<T> *node): current(node) {
            if(!this->current) return;
            else {
                this->tree = current->tree;
                this->tree->tracePath(node,s);
            }
        }

        Iterator<T>& operator=(const Iterator<T> &other) {          
            this->current = other.current;
            this->clearStack();
            this->tree->tracePath();
            this->tree = this->current->tree;
            return *this;
        }

        void clearStack() {
            while(!this->s.empty()) this->s.pop();
        }

        bool operator!=(Iterator<T> other) {
            return this->current != other.current;
        }

        void printStack() {
            cout << "printing stack" << endl;
            stack<Node<T>*> tmp = this->s;
            while(!tmp.empty()) {
                cout << tmp.top() << " " << tmp.top()->data << " ";
                tmp.pop();
            }
            cout << endl;
        }

        Iterator<T>& operator++() {
            if(!this->current) throw runtime_error(string("Trying to access invalid address."));
            if(this->current->right) {
                this->s.push(this->current);
                this->current = this->current->right;
                this->tree->treeMinimum(this->current,this->s);
            }
            else {
                if(this->s.empty()) {
                    this->s.push(this->current);
                    this->current = nullptr;
                }
                else {
                    Node<T>* tmp(this->current);
                    while(!this->s.empty() && this->s.top()->left != this->current) {
                        this->current = this->s.top();
                        this->s.pop();
                    }
                    if(this->s.empty()) {
                        this->current = tmp;
                        this->tree->tracePath(this->current,s);
                        this->s.push(this->current);
                        this->current = nullptr;
                    }
                    else {
                        this->current = this->s.top();
                        this->s.pop();
                    }
                }
            }
            return *this;
        }

        Iterator<T>& operator--() {
            if(!this->current) {
                if(this->s.empty()) throw runtime_error(string("Trying to access invalid address."));
                else {
                    this->current = this->s.top();
                    this->s.pop();
                }
            }
            else if(this->current->left) {
                this->s.push(this->current);
                this->current = this->current->left;
                this->tree->treeMaximum(this->current,this->s);
            }
            else {
                Node<T>* tmp(this->current);
                while(!this->s.empty() && this->s.top()->right != this->current) {
                    this->current = this->s.top();
                    this->s.pop();
                }
                if(this->s.empty()) {
                    this->current = tmp;
                    throw runtime_error(string("Trying to access invalid address."));
                }
                else {
                    this->current = this->s.top();
                    this->s.pop();
                }
            }
            return *this;
        }

        T operator*() {
            if(!this->current) throw runtime_error(string("Trying to access invalid address."));
            return this->current->data;
        }
};

#endif
