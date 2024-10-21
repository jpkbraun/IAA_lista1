#include "bfs.hpp"

std::vector<std::vector<float>> bfs(const std::vector<long long>& input) {
    std::vector<std::vector<float>> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(bfs_solver(input[i]));
    }
    return result;
}

std::vector<float> bfs_solver(long long input) {
    auto start = std::chrono::high_resolution_clock::now();
    float expandedNodes = 0;
    float resultLength = 0;
    float timeElapsed = 0.0;
    float meanHeuristic = 0.0;
    float initialHeuristic = (float)getManhattanDistance8P(input);

    if (isGoalState(input)) {
        auto end = std::chrono::high_resolution_clock::now();
        timeElapsed = std::chrono::duration<float>(end - start).count();
        return populateResult(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
    }

    std::deque<Node> open;
    open.push_back(Node(input, 0, initialHeuristic, -1));
    std::unordered_set<long long> closed;
    closed.insert(input);

    while (!open.empty()) {
        Node n = open.front();
        open.pop_front();
        int possibleMoves = getPossibleMoves8P(n.state, n.lastMove);
        expandedNodes++;
        int movement = 1; 
        while (possibleMoves != 0) {
            if (possibleMoves & 0x1){
                long long nextState = n.getNextState(n.state, movement);
                Node newNode = n.makeNode(n, movement, nextState);
                if (isGoalState(newNode.state)) {
                    resultLength = newNode.g;
                    auto end = std::chrono::high_resolution_clock::now();
                    timeElapsed = std::chrono::duration<float>(end - start).count();
                    return populateResult(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
                }
                if (closed.find(nextState) == closed.end()) {
                    open.push_back(newNode);
                    closed.insert(nextState);
                }
            }
            possibleMoves = possibleMoves >> 1; 
            movement *= 2; 
        }
    }
}