#include "bfs.hpp"

std::vector<std::vector<float>> bfs(const std::vector<std::vector<int>>& input) {
    std::vector<std::vector<float>> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(bfs_solver(input[i]));
    }
    return result;
}

std::vector<float> bfs_solver(const std::vector<int>& input) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<float> result;
    float expandedNodes = 0;
    float resultLength = 0;
    float timeElapsed = 0.0;
    float meanHeuristic = 0.0;
    float initialHeuristic = (float)getManhattanDistance8P(input);
    float totalHeuristic = initialHeuristic;

    if (isGoalState(input)) {
        auto end = std::chrono::high_resolution_clock::now();
        timeElapsed = std::chrono::duration<float>(end - start).count();
        populateResult(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
        return result;
    }

    std::deque<Node> open;
    open.push_back(Node(input, 0, initialHeuristic, -1));
    std::unordered_set<std::vector<int>, VectorHash, VectorEqual> closed;
    closed.insert(input);

    while (!open.empty()) {
        Node n = open.front();
        open.pop_front();
        std::vector<int> possibleMoves = getPossibleMoves8P(n.state, n.lastMove);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            std::vector<int> nextState = n.getNextState(n.state, possibleMoves[i]);
            Node newNode = n.makeNode(n, possibleMoves[i], nextState);
            if (isGoalState(newNode.state)) {
                resultLength = newNode.g;
                auto end = std::chrono::high_resolution_clock::now();
                timeElapsed = std::chrono::duration<float>(end - start).count();
                meanHeuristic = totalHeuristic / expandedNodes;
                result = populateResult(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
                return result;
            }
            if (closed.find(nextState) == closed.end()) {
                totalHeuristic += newNode.h;
                open.push_back(newNode);
                closed.insert(nextState);
                expandedNodes++;
            }
        }
    }
}