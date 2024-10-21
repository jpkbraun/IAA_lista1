#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

class Node {
    public:
        Node(long long state, int g, int h, int lastMove, int whenInserted);
        int getZeroIndex(std::vector<int> state);
        Node makeNode(Node n, int move, long long state, int whenInserted);
        long long state;
        int g;
        int h;
        int lastMove;
        int whenInserted;
};

struct CompareNode {
    bool operator()(const Node& n1, const Node& n2);
};

#endif // NODE_HPP