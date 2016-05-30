#ifndef NODE_H
#define NODE_H

#include <utility>

class Node{
public:
        Node();
        ~Node(){};
        Node(const Node& n);

        //Member
        int state[3][3];
        Node* parentNode;
        char beforeAction;

        //Function
        int stateToInt()const;
        int pathCost()const;
        int manhattanDistance()const;
        int evalF()const;
        bool isGoal()const;

        //Operator
        Node& operator=(const Node& x);
        bool operator<(const Node& y)const;
        bool operator==(const Node& y)const;
};

std::pair<int,int> whereEmpty(Node n);

Node moveDown(Node& n);
Node moveUp(Node& n);
Node moveLeft(Node& n);
Node moveRight(Node& n);

#endif
