#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

class Node {
    public:
        Node(long long state, int g, int h, int lastMove, int whenInserted);
        long long state;
        int g;
        int h;
        int lastMove;
        int whenInserted;
};

struct CompareNode { // for gbfs algorithm
    bool operator()(const Node& n1, const Node& n2);
};

struct CompareNodeAStar { // for astar algorithm
    bool operator()(const Node& n1, const Node& n2);
};

#endif // NODE_HPP