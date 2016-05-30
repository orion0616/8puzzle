#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
#include <unordered_map>
#include "Node.h"

template<class T>
class BinaryHeap {
public:
	int n;
	std::vector<T> a;
	virtual void bubbleUp(int i);
	virtual void trickleDown(int i);
	bool empty(){
		return n==0;
	}
	static int left(int i) {
		return 2*i + 1;
	}
	static int right(int i) {
		return 2*i + 2;
	}
	static int parent(int i) {
		return (i-1)/2;
	}
	std::unordered_map<int,int> index;
	BinaryHeap(){n=0;}
	virtual ~BinaryHeap(){;}
	virtual bool add(T x);
	virtual T remove();
	T findMin() {
		return a[0];
	}
	int size() {
		return n;
	}
};

template<class T>
void BinaryHeap<T>::bubbleUp(int i){
        int p = parent(i);
        while (i > 0 && (a[i] < a[p])) {
                T tmp = a[i];
                a[i] = a[p];
                a[p] = tmp;
                i = p;
                p = parent(i);
        }
}

template<class T>
void BinaryHeap<T>::trickleDown(int i) {
        do {
                int j = -1;
                int r = right(i);
                if (r < n && (a[r] < a[i])) {
                        int l = left(i);
                        if (a[l] < a[r]) {
                                j = l;
                        } else {
                                j = r;
                        }
                } else {
                        int l = left(i);
                        if (l < n && (a[l] < a[i])) {
                                j = l;
                        }
                }
                if (j >= 0){
                        T tmp = a[i];
                        a[i] = a[j];
                        a[j] = tmp;
                }
                i = j;
        } while (i >= 0);
}

template<class T>
bool BinaryHeap<T>::add(T x){
        a.push_back(x);
        n++;
        bubbleUp(n-1);
        return true;
}

template<class T>
T BinaryHeap<T>::remove(){
        T x = a[0];
        a[0] = a[--n];
        a.pop_back();
        trickleDown(0);
        return x;
}


#endif /* BINARYHEAP_H_ */
