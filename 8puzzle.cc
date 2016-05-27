#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <utility>
#include <random>
#include <sys/time.h>
#include <map>
#include <unordered_map>
#include "Node.h"
#include "BinaryHeap.h"
#include "NodeBinaryHeap.h"

using namespace std;


NodeBinaryHeap openList;
unordered_map<int,Node*> closedList;
unordered_map<int,Node*>::iterator it;

vector<Node> problems;

pair<int,int> whereEmpty(Node n){
        int emptyI,emptyJ;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(n.state[i][j]==0){
                                emptyI = i;
                                emptyJ = j;
                        }
                }
        }
        return make_pair(emptyI,emptyJ);
}

Node moveDown(Node& n){
        pair<int,int> empty = whereEmpty(n);
        int emptyI = empty.first;
        int emptyJ = empty.second;
        if(emptyI==2)
                return n;
        Node after = n;
        after.state[emptyI+1][emptyJ] = n.state[emptyI][emptyJ];
        after.state[emptyI][emptyJ] = n.state[emptyI+1][emptyJ];
        after.beforeAction = 'D';
        after.parentNode = &n;
        return after;
}

Node moveUp(Node& n){
        pair<int,int> empty = whereEmpty(n);
        int emptyI = empty.first;
        int emptyJ = empty.second;
        if(emptyI==0)
                return n;
        Node after = n;
        after.state[emptyI-1][emptyJ] = n.state[emptyI][emptyJ];
        after.state[emptyI][emptyJ] = n.state[emptyI-1][emptyJ];
        after.beforeAction = 'U';
        after.parentNode = &n;
        return after;
}

Node moveLeft(Node& n){
        pair<int,int> empty = whereEmpty(n);
        int emptyI = empty.first;
        int emptyJ = empty.second;
        if(emptyJ==0)
                return n;
        Node after = n;
        after.state[emptyI][emptyJ-1] = n.state[emptyI][emptyJ];
        after.state[emptyI][emptyJ] = n.state[emptyI][emptyJ-1];
        after.beforeAction = 'L';
        after.parentNode = &n;
        return after;
}

Node moveRight(Node& n){
        pair<int,int> empty = whereEmpty(n);
        int emptyI = empty.first;
        int emptyJ = empty.second;
        if(emptyJ==2)
                return n;
        Node after = n;
        after.state[emptyI][emptyJ+1] = n.state[emptyI][emptyJ];
        after.state[emptyI][emptyJ] = n.state[emptyI][emptyJ+1];

        after.beforeAction = 'R';
        after.parentNode = &n;
        return after;
}

Node randomize(Node& n){
        random_device rnd;
        int num = rnd()%4;
        Node moved;
        switch(num){
                case 0:
                        moved = moveDown(n);
                        break;
                case 1:
                        moved = moveUp(n);
                        break;
                case 2:
                        moved = moveRight(n);
                        break;
                case 3:
                        moved = moveLeft(n);
        }
        return moved;
}

bool isGoal(Node n){
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(n.state[i][j]!=3*i+j)
                                return false;
                }
        }
        return true;
}

void printstate(Node& n){
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        cout << n.state[i][j];
                }
                cout << endl;
        }
        cout << endl;
}

void addToOpenList(Node& n){
        int num;
        //the same state in closedList;
        if((it = closedList.find(n.stateToInt())) != closedList.end()){
                if((*it).second->pathCost() > n.pathCost()){
                        (*it).second->parentNode = n.parentNode;
                }
                return;
        }
        // the same state in openList
        else if((num = openList.find(n.stateToInt())) != -1){
                if(openList.a[num]->pathCost() > n.pathCost()){
                        openList.a[num]->parentNode = n.parentNode;
                        openList.bubbleUp(num);
                }
                return;
        }

        else{
                openList.add(&n);
                // printstate(n);
        }
        return;
}

void addChild(Node& n){
        pair<int,int> empty = whereEmpty(n);
        int emptyI = empty.first;
        int emptyJ = empty.second;
        //角
        if((emptyI == 0 || emptyI == 2) && (emptyJ == 0 || emptyJ == 2)){
                if(emptyI== 0 && emptyJ==0){
                        Node* a = new Node();
                        Node* b = new Node();
                        *a = moveDown(n);
                        *b = moveRight(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                }
                else if(emptyI==0 && emptyJ==2){
                        Node* a = new Node();
                        Node* b = new Node();
                        *a = moveDown(n);
                        *b = moveLeft(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                }
                else if(emptyI==2 && emptyJ==0){
                        Node* a = new Node();
                        Node* b = new Node();
                        *a = moveUp(n);
                        *b = moveRight(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                }
                else{
                        Node* a = new Node();
                        Node* b = new Node();
                        *a = moveUp(n);
                        *b = moveLeft(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                }
        }
        //角を除く辺上
        else if(emptyI == 0 || emptyI == 2 || emptyJ == 0 || emptyJ == 2){
                if(emptyI==0){
                        Node* a = new Node();
                        Node* b = new Node();
                        Node* c = new Node();
                        *a = moveDown(n);
                        *b = moveLeft(n);
                        *c = moveRight(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                        addToOpenList(*c);
                }
                else if(emptyI==2){
                        Node* a = new Node();
                        Node* b = new Node();
                        Node* c = new Node();
                        *a = moveUp(n);
                        *b = moveLeft(n);
                        *c = moveRight(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                        addToOpenList(*c);
                }
                else if(emptyJ==0){
                        Node* a = new Node();
                        Node* b = new Node();
                        Node* c = new Node();
                        *a = moveDown(n);
                        *b = moveUp(n);
                        *c = moveRight(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                        addToOpenList(*c);
                }
                else{
                        Node* a = new Node();
                        Node* b = new Node();
                        Node* c = new Node();
                        *a = moveDown(n);
                        *b = moveUp(n);
                        *c = moveLeft(n);
                        addToOpenList(*a);
                        addToOpenList(*b);
                        addToOpenList(*c);
                }
        }
        //それ以外
        else{
                Node* a = new Node();
                Node* b = new Node();
                Node* c = new Node();
                Node* d = new Node();
                *a = moveDown(n);
                *b = moveUp(n);
                *c = moveLeft(n);
                *d = moveRight(n);
                addToOpenList(*a);
                addToOpenList(*b);
                addToOpenList(*c);
                addToOpenList(*d);
        }
        return;
}

void printResult(Node& n){
        vector<char> actions;
        int pathCost = n.pathCost();
        while(n.parentNode != NULL){
                actions.push_back(n.beforeAction);
                n = *(n.parentNode);
        }
        cout << pathCost << "steps: ";
        reverse(actions.begin(), actions.end());
        for(vector<char>::iterator it =actions.begin();it!=actions.end();it++){
                cout << *it;
        }
        cout << endl;
        return;
}

void astar(Node& n){
        openList.add(&n);
        Node* node;
        while(!openList.empty()){
                node = openList.findMin();
                openList.remove();
                if(isGoal(*node)){
                        printResult(*node);
                        return;
                }
                else{
                        closedList[node->stateToInt()] = node;
                        addChild(*node);
                }
        }
        return;
}

void printTime(timeval t0, timeval t1){
        t1.tv_sec -= t0.tv_sec;
        if (t1.tv_usec < t0.tv_usec) {
                t1.tv_sec -= 1;
                t1.tv_usec += 1000000 - t0.tv_usec;
        } else {
                t1.tv_usec -= t0.tv_usec;
        }
        printf("%ld.%06d sec\n\n", t1.tv_sec, t1.tv_usec);
}


void createProblems(int num){
        for(int i=0;i<num;i++){
                Node n;
                for(int j=0;j<100;j++){
                        n = randomize(n);
                }
                n.beforeAction = '\0';
                n.parentNode = NULL;
                problems.push_back(n);
        }
        return;
}

int main(){
        createProblems(100);
        struct timeval t0, t1;
        for(int i=0;i<100;i++){
                gettimeofday(&t0, NULL);
                astar(problems[i]);
                gettimeofday(&t1, NULL);
                cout << openList.n + closedList.size() << endl;
                printTime(t0,t1);
                while(!openList.empty()){
                        Node* node = openList.findMin();
                        openList.remove();
                        if(node != NULL){
                                delete node;
                                node = NULL;
                        }
                }
                closedList.clear();
        }
}
