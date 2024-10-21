#include "node.hpp"

Node::Node(long long state, int g, int h, int lastMove, int whenInserted) {
    this->state = state;
    this->g = g;
    this->h = h;
    this->lastMove = lastMove;
    this->whenInserted = whenInserted;
}

Node Node::makeNode(Node n, int move, long long state, int whenInserted) {
    return Node(state, n.g + 1, getManhattanDistance8P(state), move, whenInserted);
}

bool CompareNode::operator()(const Node& n1, const Node& n2) {
    if (n1.h == n2.h) {
        if (n1.g == n2.g) {
            return n1.whenInserted < n2.whenInserted;
        }
        return n1.g < n2.g;
    }
    return n1.h > n2.h; // Min-heap: smallest heuristic first
}

bool CompareNodeAStar::operator()(const Node& n1, const Node& n2) {
    int f1 = n1.h + n1.g;
    int f2 = n2.h + n2.g;
    if (f1 == f2) {
        if (n1.h == n2.h) {
            return n1.whenInserted < n2.whenInserted;
        }
        return n1.h > n2.h;
    }
    return f1 > f2; // Min-heap: smallest heuristic first
}