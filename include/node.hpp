#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

class Node {
    public:
        Node(long long state, int g, int h, int lastMove);
        int getZeroIndex(std::vector<int> state);
        long long getNextState(long long state, int move);
        Node makeNode(Node n, int move, long long state);
        long long state;
        int g;
        int h;
        int lastMove;

};

#endif // NODE_HPP