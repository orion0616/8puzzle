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
	virtual void bubbleUp(int i)= 0;
	virtual void trickleDown(int i)=0;
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
	virtual bool add(T x)=0;
	virtual T remove()=0;
	T findMin() {
		return a[0];
	}
	int size() {
		return n;
	}
};


#endif /* BINARYHEAP_H_ */
