#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <cstring>
#include <vector>

using namespace std;

template<class T>
class BinaryHeap {
public:
	int n;
	void bubbleUp(int i);
	void trickleDown(int i);
	void resize();
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
	vector<T> a;
	BinaryHeap();
	BinaryHeap(vector<T>& b);
	virtual ~BinaryHeap();
	bool add(T x);
	T findMin() {
		return a[0];
	}
	T remove();
	int size() {
		return n;
	}
	int find(T x);
};

template<class T>
void BinaryHeap<T>::resize() {
	vector<T> b(max(2*n, 1));
	std::copy(a.begin(), a.end(), back_inserter(b));
	a = b;
}

template<class T>
bool BinaryHeap<T>::add(T x) {
	a.push_back(x);
	n++;
	bubbleUp(n-1);
	return true;
}

template<class T>
void BinaryHeap<T>::bubbleUp(int i) {
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
T BinaryHeap<T>::remove() {
	T x = a[0];
	a[0] = a[--n];
	a.pop_back();
	trickleDown(0);
	return x;
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
BinaryHeap<T>::BinaryHeap() {
	n = 0;
}

template<class T>
BinaryHeap<T>::BinaryHeap(vector<T> &b) : a(0) {
	a = b;
	n = a.size();
	for (int i = n/2-1; i >= 0; i--) {
		trickleDown(i);
	}
}

template<class T>
BinaryHeap<T>::~BinaryHeap() {
	// nothing to do
}

template<class T>
int BinaryHeap<T>::find(T x){
	for(int i=0;i<a.size();i++){
		if(a[i] == x)
			return i;
	}
	return -1;
}

#endif /* BINARYHEAP_H_ */
