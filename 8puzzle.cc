#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <random>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

class Node{
public:
        Node(){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++)
                                state[i][j] = 3*i+j;
                }
                parentNode = NULL;
        }
        ~Node(){};
        Node(const Node& n){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++)
                                state[i][j] = n.state[i][j];
                }
                parentNode = n.parentNode;
                beforeAction = n.beforeAction;
        }
        int state[3][3];
        int pathCost()const{
                if(parentNode == NULL)
                        return 0;
                else
                        return parentNode->pathCost()+1;
        }
        Node* parentNode;
        char beforeAction;
        int heuristic()const;
        int evalF()const{
                return pathCost() + heuristic();
        }
        Node& operator=(const Node& x){
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++)
                                this->state[i][j] = x.state[i][j];
                }
                this->parentNode = x.parentNode;
                this->beforeAction = x.beforeAction;
                return *this;
        }
        bool operator>(const Node& y)const{
                return this->evalF() > y.evalF();
        }
        bool operator==(const Node& y)const{
                bool ans = true;
                for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                                if(this->state[i][j]!=y.state[i][j])
                                        ans = false;
                        }
                }
                return ans;
        }
};

int h1(Node n){
        int count = 0;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if((3*i+j != n.state[i][j]) && n.state[i][j]!=0)
                                count++;
                }
        }
        return count;
}

int h2(Node n){
        int count = 0;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        int k = n.state[i][j];
                        if(k==0)
                                continue;
                        int p = k/3;
                        int q = k%3;
                        count += abs(i-p) + abs(j-q);
                }
        }
        return count;
}

int Node::heuristic()const{
        return h2(*this);
}

pair<int,int> whereEmpty(const Node n){
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

priority_queue<Node, vector<Node>, greater<Node> > openList;
vector<Node*> closedList;

int findClosedList(Node n){
        for(int i=0;i<closedList.size();i++){
                if(n == *closedList[i])
                        return i;
        }
        return -1;
}

void pushToOpenList(Node n){
        int num;
        //the same state in openList
        if(false){
                return;
        }
        //the same state in closedList;
        else if((num = findClosedList(n)) != -1){
                if(closedList[num]->pathCost() > n.pathCost()){
                        closedList[num]->parentNode = n.parentNode;
                }
                return;
        }
        else{
                openList.push(n);
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
                        pushToOpenList(moveDown(n));
                        pushToOpenList(moveRight(n));
                }
                else if(emptyI==0 && emptyJ==2){
                        pushToOpenList(moveDown(n));
                        pushToOpenList(moveLeft(n));
                }
                else if(emptyI==2 && emptyJ==0){
                        pushToOpenList(moveUp(n));
                        pushToOpenList(moveRight(n));
                }
                else if(emptyI==2 && emptyJ==2){
                        pushToOpenList(moveUp(n));
                        pushToOpenList(moveLeft(n));
                }
        }
        //角を除く辺上
        else if((emptyI == 0 || emptyI == 2) || (emptyJ == 0 || emptyJ == 2)){
                if(emptyI==0){
                        pushToOpenList(moveDown(n));
                        pushToOpenList(moveLeft(n));
                        pushToOpenList(moveRight(n));
                }
                else if(emptyI==2){
                        pushToOpenList(moveUp(n));
                        pushToOpenList(moveLeft(n));
                        pushToOpenList(moveRight(n));
                }
                else if(emptyJ==0){
                        pushToOpenList(moveDown(n));
                        pushToOpenList(moveUp(n));
                        pushToOpenList(moveRight(n));
                }
                else if(emptyJ==2){
                        pushToOpenList(moveDown(n));
                        pushToOpenList(moveUp(n));
                        pushToOpenList(moveLeft(n));
                }
        }
        //それ以外
        else{
                        pushToOpenList(moveDown(n));
                        pushToOpenList(moveUp(n));
                        pushToOpenList(moveLeft(n));
                        pushToOpenList(moveRight(n));
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

vector<Node> problems;

void astar(Node& n){
        openList.push(n);
        Node* node;
        while(!openList.empty()){
                node = new Node(openList.top());
                openList.pop();
                closedList.push_back(node);
                if(isGoal(*node)){
                        printResult(*node);
                        return;
                }
                else{
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
                printTime(t0,t1);
                while(!openList.empty()){
                        openList.pop();
                }
                Node* nP;
                while(!closedList.empty()){
                        nP = closedList[closedList.size()-1];
                        if(nP != NULL){
                                delete nP;
                                nP = NULL;
                        }
                        closedList.pop_back();
                }
        }
}