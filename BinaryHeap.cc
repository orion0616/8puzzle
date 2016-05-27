#include "BinaryHeap.h"

using namespace std;

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