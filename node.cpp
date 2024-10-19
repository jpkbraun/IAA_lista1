#include "node.hpp"

Node::Node(std::vector<int> state, int g, int h, int lastMove) {
    this->state = state;
    this->g = g;
    this->h = h;
    this->lastMove = lastMove;
}

int Node::getZeroIndex(std::vector<int> state) {
    int zeroIndex = -1;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) {
            return i;
        }
    }
}

std::vector<int> Node::getNextState(std::vector<int> state, int move) {
    std::vector<int> newState = state;
    int zeroIndex = getZeroIndex(state);
    switch (move) {
        case UP:
            newState[zeroIndex] = state[zeroIndex - 3];
            newState[zeroIndex - 3] = 0;
            break;
        case LEFT:
            newState[zeroIndex] = state[zeroIndex - 1];
            newState[zeroIndex - 1] = 0;
            break;
        case RIGHT:
            newState[zeroIndex] = state[zeroIndex + 1];
            newState[zeroIndex + 1] = 0;
            break;
        case DOWN:
            newState[zeroIndex] = state[zeroIndex + 3];
            newState[zeroIndex + 3] = 0;
            break;
    }
    return newState;
}

Node Node::makeNode(Node n, int move, std::vector<int> state) {
    return Node(state, n.g + 1, getManhattanDistance8P(state), move);
}