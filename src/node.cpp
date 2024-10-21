#include "node.hpp"

Node::Node(long long state, int g, int h, int lastMove) {
    this->state = state;
    this->g = g;
    this->h = h;
    this->lastMove = lastMove;
}

long long Node::getNextState(long long state, int move) {
    long long newState = state;
    int zeroIndex = getZeroPos(state);
    int targetIndex = zeroIndex; // The index of the tile to swap with

    // Determine the index of the tile to swap with based on the move
    switch (move) {
        case UP:
            targetIndex -= 3;
            break;
        case LEFT:
            targetIndex -= 1;
            break;
        case RIGHT:
            targetIndex += 1;
            break;
        case DOWN:
            targetIndex += 3;
            break;
    }

    // Extract the value of the tile at the target index
    long long targetTile = (state >> (4 * targetIndex)) & 0xF;

    // Clear the bits at the current zero position
    newState &= ~(0xFLL << (4 * zeroIndex));

    // Set the target tile at the zero's original position
    newState |= (targetTile << (4 * zeroIndex));

    // Clear the bits at the target position
    newState &= ~(0xFLL << (4 * targetIndex));

    // Set zero (0) at the target position
    newState |= (0LL << (4 * targetIndex));

    return newState;
}

Node Node::makeNode(Node n, int move, long long state) {
    return Node(state, n.g + 1, getManhattanDistance8P(state), move);
}