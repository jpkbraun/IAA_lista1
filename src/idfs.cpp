#include "idfs.hpp"

std::vector<Result> idfs(const std::vector<long long>& input) {
    std::vector<Result> result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(idfs_solver(input[i]));
    }
    return result;
}

std::chrono::time_point<std::chrono::high_resolution_clock> IDFS_start;
int IDFS_expandedNodes;
int IDFS_resultLength;
float IDFS_timeElapsed;
float IDFS_meanHeuristic;
int IDFS_initialHeuristic;

#include <memory>
std::unique_ptr<Result> idfs_recursive(Node n, int depth){
    if (isGoalState(n.state)) {
        auto end = std::chrono::high_resolution_clock::now();
        IDFS_timeElapsed = std::chrono::duration<float>(end - IDFS_start).count();
        return std::make_unique<Result>(IDFS_expandedNodes, n.g, IDFS_timeElapsed, 0.0, IDFS_initialHeuristic);
    }

    if (depth > 0){
        int possibleMoves = getPossibleMoves8P(n.state, n.lastMove);
        IDFS_expandedNodes++;
        int movement = 1;
        while (possibleMoves != 0) {
            if (possibleMoves & 0x1){
                long long nextState = getNextState(n.state, movement);
                auto result = idfs_recursive(Node(nextState, n.g + 1, getManhattanDistance8P(nextState), movement, 0), depth - 1);
                if (result != nullptr){
                    return result;
                }
            }
            possibleMoves = possibleMoves >> 1;
            movement *= 2;
        }
    }
    return nullptr;
}

Result idfs_solver(long long input) {
    IDFS_start = std::chrono::high_resolution_clock::now();
    IDFS_expandedNodes = 0;
    IDFS_resultLength = 0;
    IDFS_timeElapsed = 0.0;
    IDFS_meanHeuristic = 0.0;
    IDFS_initialHeuristic = getManhattanDistance8P(input);

    if (isGoalState(input)) {
        auto end = std::chrono::high_resolution_clock::now();
        IDFS_timeElapsed = std::chrono::duration<float>(end - IDFS_start).count();
        return  Result(IDFS_expandedNodes, IDFS_resultLength, IDFS_timeElapsed, IDFS_meanHeuristic, IDFS_initialHeuristic);
    }
    for (int i = 0; i < INT16_MAX; i++){
        auto result = idfs_recursive(Node(input, 0, IDFS_initialHeuristic, -1, 0), i);
        if (result != nullptr){
            return Result(result->expandedNodes, result->resultLength, result->timeElapsed, result->meanHeuristic, result->initialHeuristic);
        }
    }
}

