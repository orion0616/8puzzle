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

void addToOpenList(Node& n){
        int num;
        //the same state in closedList;
        auto it = closedList.find(n.stateToInt());
        if(it != closedList.end()){
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
        }
        return;
}

void moveandAdd(Node& n, string direction){
        Node* next = new Node();
        if(direction == "Down")
                *next = moveDown(n);
        if(direction == "Up")
                *next = moveUp(n);
        if(direction == "Left")
                *next = moveLeft(n);
        if(direction == "Right")
                *next = moveRight(n);
        addToOpenList(*next);
        return;
}

void addChild(Node& n){
        pair<int,int> empty = whereEmpty(n);
        int emptyI = empty.first;
        int emptyJ = empty.second;
        //角
        if((emptyI == 0 || emptyI == 2) && (emptyJ == 0 || emptyJ == 2)){
                if(emptyI== 0 && emptyJ==0){
                        moveandAdd(n,"Down");
                        moveandAdd(n,"Right");
                }
                else if(emptyI==0 && emptyJ==2){
                        moveandAdd(n,"Down");
                        moveandAdd(n,"Left");
                }
                else if(emptyI==2 && emptyJ==0){
                        moveandAdd(n,"Up");
                        moveandAdd(n,"Right");
                }
                else{
                        moveandAdd(n,"Up");
                        moveandAdd(n,"Left");
                }
        }
        //角を除く辺上
        else if(emptyI == 0 || emptyI == 2 || emptyJ == 0 || emptyJ == 2){
                if(emptyI==0){
                        moveandAdd(n,"Down");
                        moveandAdd(n,"Left");
                        moveandAdd(n,"Right");
                }
                else if(emptyI==2){
                        moveandAdd(n,"Up");
                        moveandAdd(n,"Left");
                        moveandAdd(n,"Right");
                }
                else if(emptyJ==0){
                        moveandAdd(n,"Down");
                        moveandAdd(n,"Up");
                        moveandAdd(n,"Right");
                }
                else{
                        moveandAdd(n,"Down");
                        moveandAdd(n,"Up");
                        moveandAdd(n,"Left");
                }
        }
        //それ以外
        else{
                moveandAdd(n,"Down");
                moveandAdd(n,"Up");
                moveandAdd(n,"Left");
                moveandAdd(n,"Right");
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


void createProblems(vector<Node>& problems, int num){
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
        vector<Node> problems;
        createProblems(problems,100);
        struct timeval t0, t1;

        //100問解く
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
