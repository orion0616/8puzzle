#ifndef NODE_H
#define NODE_H

class Node{
public:
        Node();
        ~Node(){};
        Node(const Node& n);
        int state[3][3];
        int stateToInt()const;
        int pathCost()const;
        Node* parentNode;
        char beforeAction;
        int heuristic()const;
        int evalF()const;
        Node& operator=(const Node& x);
        bool operator<(const Node& y)const;
        bool operator==(const Node& y)const;
};
#endif