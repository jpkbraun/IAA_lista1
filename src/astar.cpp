#include "astar.hpp"

std::vector<Result> astar(const std::vector<long long>& input) {
    std::vector<Result> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(astar_solver(input[i]));
    }
    return result;
}

Result astar_solver(long long input) {
    auto start = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    int resultLength = 0;
    float timeElapsed = 0.0;
    float meanHeuristic = 0.0;
    int initialHeuristic = getManhattanDistance8P(input);
    int totalHeuristic = 0;
    int whenInserted = 0;

    std::priority_queue<Node, std::vector<Node>, CompareNodeAStar> open;
    if (initialHeuristic < INTMAX_MAX) {
        open.emplace(Node(input, 0, initialHeuristic, -1, 0));
    }
    std::unordered_set<long long> closed;

    while (!open.empty()) {
        Node n = open.top();
        open.pop();
        totalHeuristic += n.h;
        if (closed.find(n.state) == closed.end()) {
            closed.insert(n.state);
            if (isGoalState(n.state)) {
                resultLength = n.g;
                auto end = std::chrono::high_resolution_clock::now();
                timeElapsed = std::chrono::duration<float>(end - start).count();
                if (expandedNodes != 0) {
                    meanHeuristic = (float)totalHeuristic / (float)expandedNodes;
                }
                Result result = Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
                return result;
            }
            int possibleMoves = getPossibleMoves8P(n.state, n.lastMove);
            expandedNodes++;
            int movement = 1;
            while (possibleMoves != 0) {
                if (possibleMoves & 0x1){

                    long long nextState = getNextState(n.state, movement);
                    int h = getManhattanDistance8P(nextState);
                    if (h < INTMAX_MAX) {
                        open.emplace(nextState, n.g + 1, h, movement, whenInserted);
                        whenInserted++;
                    }
                }
                movement *= 2;
                possibleMoves = possibleMoves >> 1; 
            }
        }
    }
}