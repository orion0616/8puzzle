#ifndef NODEBINARYHEAP_H_
#define NODEBINARYHEAP_H_

#include "Node.h"
#include "BinaryHeap.h"

class NodeBinaryHeap : public BinaryHeap<Node*>{
public:
        bool add(Node* x);
        void bubbleUp(int i);
        void trickleDown(int i);
        Node* remove();
        int find(int i);
};

#endif
