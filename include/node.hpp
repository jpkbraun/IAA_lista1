#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

class Node {
    public:
        Node(long long state, int g, int h, int lastMove);
        long long getNextState(long long state, int move);
        long long state;
        int g;
        int h;
        int lastMove;

};

#endif // NODE_HPP