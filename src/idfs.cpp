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

bool idfs_recursive(long long state, int path, int move, int depth){
    if (isGoalState(state)) {
        auto end = std::chrono::high_resolution_clock::now();
        IDFS_timeElapsed = std::chrono::duration<float>(end - IDFS_start).count();
        IDFS_resultLength = path;
        return true; 
    }

    if (depth > 0){
        int possibleMoves = getPossibleMoves8P(state, move);
        IDFS_expandedNodes++;
        int movement = 1;
        while (possibleMoves != 0) {
            if (possibleMoves & 0x1){
                long long nextState = getNextState(state, movement);
                auto result = idfs_recursive(nextState, path + 1, movement, depth - 1);
                if (result){
                    return result;
                }
            }
            possibleMoves = possibleMoves >> 1;
            movement *= 2;
        }
    }
    return false;
}

Result idfs_solver(long long input) {
    IDFS_start = std::chrono::high_resolution_clock::now();
    IDFS_expandedNodes = 0;
    IDFS_resultLength = 0;
    IDFS_timeElapsed = 0.0;
    IDFS_meanHeuristic = 0.0;
    IDFS_initialHeuristic = getManhattanDistance8P(input);

    for (int i = 0; i < INT16_MAX; i++){
        auto result = idfs_recursive(input, 0, -1, i);
        if (result){
            return Result(IDFS_expandedNodes, IDFS_resultLength, IDFS_timeElapsed, 0.0, IDFS_initialHeuristic);
        }
    }
    throw std::runtime_error("Unsolvable state"); 
}

