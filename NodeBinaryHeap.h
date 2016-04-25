#ifndef NODEBINARYHEAP_H_
#define NODEBINARYHEAP_H_

#include "BinaryHeap.h"
#include <vector>

using namespace std;

class NodeBinaryHeap : public BinaryHeap<Node*>{
public:
        bool add(Node* x);
        void bubbleUp(int i);
        void trickleDown(int i);
        Node* remove();
        int find(int i);
};

bool NodeBinaryHeap::add(Node* x){
        a.push_back(x);
        n++;
        index[x->stateToInt()] = n-1;
        bubbleUp(n-1);
        return true;
}

void NodeBinaryHeap::bubbleUp(int i){
        int p = parent(i);
        while(i>0 && (a[i]->evalF() < a[p]->evalF())){
                Node* tmp = a[i];
                a[i] = a[p];
                a[p] = tmp;
                i = p;
                index[a[i]->stateToInt()] = i;
                index[a[p]->stateToInt()] = p;
                p = parent(i);
        }
}

void NodeBinaryHeap::trickleDown(int i){
        do{
                int j = -1;
                int r = right(i);
                if(r < n && (a[r]->evalF() < a[i]->evalF())){
                        int l = left(i);
                        if(a[l]->evalF() < a[r]->evalF()){
                                j = l;
                        }else{
                                j = r;
                        }
                } else{
                        int l = left(i);
                        if(l < n && (a[l]->evalF() < a[i]->evalF())){
                                j = l;
                        }
                }
                if(j >= 0){
                        Node* tmp = a[i];
                        a[i] = a[j];
                        a[j] = tmp;
                        index[a[i]->stateToInt()] = i;
                        index[a[j]->stateToInt()] = j;
                }
                i = j;
        }while(i>=0);
}

Node* NodeBinaryHeap::remove(){
        Node* x = a[0];
        a[0] = a[--n];
        a.pop_back();
        index[a[0]->stateToInt()] = 0;
        index.erase(x->stateToInt());
        trickleDown(0);
        return  x;
}

int NodeBinaryHeap::find(int i){
        int num;
        unordered_map<int,int>::iterator it;
        it = index.find(i);
        if(it != index.end()){
                num = (*it).second;
                return num;
        }
        else{
                return -1;
        }
}

#endif
