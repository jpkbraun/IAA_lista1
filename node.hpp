#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

class Node {
    public:
        Node(std::vector<int> state, int g, int h, int lastMove);
        int getZeroIndex(std::vector<int> state);
        std::vector<int> getNextState(std::vector<int> state, int move);
        Node makeNode(Node n, int move, std::vector<int> state);
        std::vector<int> state;
        int g;
        int h;
        int lastMove;

};

#endif // NODE_HPP