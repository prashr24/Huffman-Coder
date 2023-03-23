#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
using namespace std;

class Node
{
public:
    int frequency;
    char symbol;
    Node *left,*right;
    Node(char symbol, int frequency)
    {
        this->symbol = symbol;
        this->frequency = frequency;
        this->left = this->right = NULL;
    }
};

class heapNode
{
public:
    Node* node;
    heapNode *left, *right;
    heapNode(Node* node)
    {
        this->node = node;
        this->left = this->right = NULL;
    }
};

class MinHeap
{
private:
    heapNode* heap[256];
    int heapSize;
public:
    MinHeap();
    void insertNode(Node*);
    Node* extractNode();
    void heapify();
    int getSize() { return this->heapSize; }
    void levelTraversal();
};

#endif // MINHEAP_H
