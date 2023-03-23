#include "MinHeap.h"

MinHeap::MinHeap()
{
    for (int i=0; i<256; i++)
        this->heap[i] = NULL;

    this->heapSize = 0;
}

void MinHeap::heapify()
{
    if (this->heapSize == 0)
        return;

    HeapifyProcess:

        int currentNode = this->heapSize/2;
        int swapCount = 0;
        while(currentNode >= 0)
        {
            if( (2*currentNode + 2 < 256) && this->heap[2*currentNode+2] != NULL )
            {
                if (this->heap[currentNode]->node->frequency > this->heap[2*currentNode + 2]->node->frequency)
                {
                    heapNode tempNode = *heap[currentNode];
                    *heap[currentNode] = *heap[2*currentNode + 2];
                    *heap[2*currentNode + 2] = tempNode;
                    swapCount++;
                }
            }

            if( (2*currentNode + 1 < 256) && this->heap[2*currentNode + 1] != NULL )
            {
                if (this->heap[currentNode]->node->frequency > this->heap[2*currentNode + 1]->node->frequency)
                {
                    heapNode tempNode = *heap[currentNode];
                    *heap[currentNode] = *heap[2*currentNode + 1];
                    *heap[2*currentNode + 1] = tempNode;
                    swapCount++;
                }
            }
            currentNode--;
        }

        if (swapCount != 0)
            goto HeapifyProcess;
}

void MinHeap::insertNode(Node* node)
{
    if (this->heapSize == 256)
        return;

    this->heap[ this->heapSize++ ] = new heapNode(node);
    this->heapify();
}

Node* MinHeap::extractNode()
{
    if (this->heapSize == 0)
        return NULL;

    Node* temp = this->heap[0]->node;
    this->heapSize--;

    for (int i=0; i<heapSize; i++)
        this->heap[i] = this->heap[i+1];

    this->heap[heapSize] = NULL;

    this->heapify();
    return temp;
}

void MinHeap::levelTraversal()
{
    if (this->heapSize == 0)
        return;

    for (int i=0; i<this->heapSize; i++)
        cout << this->heap[i]->node->symbol << '\t' << this->heap[i]->node->frequency << '\n';
}




