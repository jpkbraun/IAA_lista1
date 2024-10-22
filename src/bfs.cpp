#include "bfs.hpp"

std::vector<Result> bfs(const std::vector<long long>& input) {
    std::vector<Result> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(bfs_solver(input[i]));
    }
    return result;
}

Result bfs_solver(long long input) {
    auto start = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    int resultLength = 0;
    float timeElapsed = 0.0;
    float meanHeuristic = 0.0;
    int initialHeuristic = getManhattanDistance8P(input);

    if (isGoalState(input)) {
        auto end = std::chrono::high_resolution_clock::now();
        timeElapsed = std::chrono::duration<float>(end - start).count();
        return  Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
    }

    std::deque<Node> open;
    open.emplace_back(input, 0, initialHeuristic, -1, 0);
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
                long long nextState = getNextState(n.state, movement);
                if (isGoalState(nextState)) {
                    resultLength = n.g + 1;
                    auto end = std::chrono::high_resolution_clock::now();
                    timeElapsed = std::chrono::duration<float>(end - start).count();
                    return Result(expandedNodes, resultLength, timeElapsed, meanHeuristic, initialHeuristic);
                }
                if (closed.find(nextState) == closed.end()) {
                    open.emplace_back(nextState, n.g + 1, getManhattanDistance8P(nextState), movement, 0);
                    closed.insert(nextState);
                }
            }
            possibleMoves = possibleMoves >> 1; 
            movement *= 2; 
        }
    }
    throw std::runtime_error("Unsolvable state"); 
}