#include "Node.h"
#include <iostream>
#include <cmath>

using namespace std;

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

int Node::stateToInt()const{
        return state[0][0]*100000000 + state[0][1]*10000000 + state[0][2]*1000000 + state[1][0]*100000 + state[1][1]*10000 + state[1][2]*1000 +state[2][0]*100 + state[2][1]*10 +state[2][2];
}

int Node::pathCost()const{
        if(parentNode == NULL)
                return 0;
        else
                return parentNode->pathCost()+1;
}

int Node::heuristic()const{
        return h2(*this);
}

int Node::evalF()const{
        return pathCost() + heuristic();
}

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