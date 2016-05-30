#include "Node.h"
#include <iostream>
#include <cmath>

using namespace std;

int Node::manhattanDistance()const{
        int count = 0;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        int k = state[i][j];
                        if(k==0)
                                continue;
                        int p = k/3;
                        int q = k%3;
                        count += abs(i-p) + abs(j-q);
                }
        }
        return count;
}

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
Node::Node(){
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++)
                        state[i][j] = 3*i+j;
        }
        parentNode = NULL;
}

Node::Node(const Node& n){
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++)
                        state[i][j] = n.state[i][j];
        }
        parentNode = n.parentNode;
        beforeAction = n.beforeAction;
}

bool Node::isGoal()const{
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(state[i][j]!=3*i+j)
                                return false;
                }
        }
        return true;
}

//This is a kind of Hash fucntion for index
int Node::stateToInt()const{
        return state[0][0]*100000000 + 
               state[0][1]*10000000 +
               state[0][2]*1000000 + 
               state[1][0]*100000 + 
               state[1][1]*10000 + 
               state[1][2]*1000 +
               state[2][0]*100 + 
               state[2][1]*10 +
               state[2][2];
}

int Node::pathCost()const{
        if(parentNode == NULL)
                return 0;
        else
                return parentNode->pathCost()+1;
}

int Node::evalF()const{
        return pathCost() + manhattanDistance();
}


//Operator
Node& Node::operator=(const Node& x){
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++)
                        this->state[i][j] = x.state[i][j];
        }
        this->parentNode = x.parentNode;
        this->beforeAction = x.beforeAction;
        return *this;
}

bool Node::operator<(const Node& y)const{
        return this->evalF() < y.evalF();
}

bool Node::operator==(const Node& y)const{
        bool ans = true;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(this->state[i][j]!=y.state[i][j])
                                ans = false;
                }
        }
        return ans;
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
